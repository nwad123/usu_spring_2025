/*
 * Histogram generator with OpenMPI
 * Nick Waddoups | CS 6300
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

// A wrapper type for a simple vector
typedef struct {
    float* data;
    size_t length;
} FloatVector;

// Randomize every value in `vec` to a value between `min` and `max`
static inline void set_random(FloatVector vec, const float min, const float max)
{
    srand(100);
    
    const float range = max - min;
    const float scaling_factor = (float)RAND_MAX / range;

    // for each element get a random value between `min` and `max`
    for (float* ptr = vec.data; ptr < (vec.data + vec.length); ptr++)
    {
        *ptr = (rand() / scaling_factor) + min;
    }
}

// Generate a random vector of floats between `min` and `max` of length `count`
// NOTE: allocates memory pointed to by `generate_values().data`
static inline FloatVector generate_values(const float min, const float max, const size_t count)
{
    FloatVector vec = {
        .data = malloc(count * sizeof(float)),
        .length = count,
    };

    set_random(vec, min, max);

    return vec;
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank = 0, num_processes = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    // If the command line arguments are not correct we need to exit the program.
    // This is not the most graceful way to do so, but it's effective and ultimately
    // shouldn't be an area that slows down execution.
    if (argc != 5) {
        if (rank == 0) 
            printf("Correct usage: <bin count> <min meas> <max meas> <data count>\n"); 
        MPI_Finalize();
        return 1;
    }

    // local vars for all our parameters
    int bin_count = 0;
    float min = 0.0;
    float max = 0.0;
    int size = 0;

    // Have process 0 parse all the arguments.
    if (rank == 0) {
        bin_count = atoi(argv[1]);
        min = atof(argv[2]);
        max = atof(argv[3]);
        size = atoi(argv[4]);
    }

    // Everyone gets the parsed values via the classic, `bcast`
    // The `0` indicates process 0 is doing the broadcasting
    MPI_Bcast(&bin_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&min, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&max, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // calculate the number of max elements per process 
    // if we are the last process this may be too many, but better to have 
    // too many rather than too little!
    const int max_elements_per_process = size / num_processes;

    // Have process 0 generate the data for the histogram and partition it out 
    // to the other processes
    FloatVector my_data;

    // Allocate my_data vector based on which process we are
    if (rank == 0) { 
        // generate values
        my_data = generate_values(min, max, size); 
        my_data.length = max_elements_per_process;
    } else {
        // allocate empty space
        my_data = (FloatVector){
            .data = malloc(max_elements_per_process * sizeof(float)),
            .length = max_elements_per_process,
        };

        // shorten the length if necessary
        if (rank == num_processes - 1) {
            const int access_offset = rank * max_elements_per_process;
            my_data.length = size - access_offset;
        }
    };

    MPI_Scatter(
        my_data.data, // start from the address we generated
        size / num_processes, // each thread should get N / p elements
        MPI_FLOAT,
        my_data.data,
        size / num_processes, // each thread receives the same amount of elements
        MPI_FLOAT,
        0,
        MPI_COMM_WORLD);

    // set up the local bin 
    int* my_bin_counts = calloc(bin_count, sizeof(int));
    float* my_bin_maxes = calloc(bin_count, sizeof(float));

    // calculate the step between bins 
    const float step = (max - min) / bin_count;

    // calculate the bin counts
    for (int i = 0; i < (int)my_data.length; i++)
    {
        for (int bin = 0; bin < bin_count; bin++) 
        {
            if (my_data.data[i] <= min + step * (bin + 1)) {
                my_bin_counts[bin] += 1;
                my_bin_maxes[bin] = my_bin_maxes[bin] < my_data.data[i] ? my_data.data[i] : my_bin_maxes[bin];
                break;
            }
        }
    }

    // set up the global bin 
    int* glob_bin_counts = rank == 0 ? calloc(bin_count, sizeof(int)) : NULL;
    float* glob_bin_maxes = rank == 0 ? calloc(bin_count, sizeof(float)) : NULL;

    // reduce over the values for the counts
    MPI_Reduce(
        my_bin_counts,
        glob_bin_counts,
        bin_count,
        MPI_INT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD);

    // reduce over the values for the maxes 
    MPI_Reduce(
        my_bin_maxes,
        glob_bin_maxes,
        bin_count,
        MPI_FLOAT,
        MPI_MAX,
        0,
        MPI_COMM_WORLD);

    // print the results
    if (rank == 0) {
        printf("Bin maxes: ");
        for (int i = 0; i < bin_count; i++) {
            printf("%f ", glob_bin_maxes[i]);
        }
        printf("\n");

        printf("Bin counts: ");
        for (int i = 0; i < bin_count; i++) {
            printf("%d ", glob_bin_counts[i]);
        }
        printf("\n");
    }

    // Free up our data blocks
    free(my_data.data);
    free(my_bin_counts);
    free(my_bin_maxes);
    if (rank == 0) free(glob_bin_counts);
    if (rank == 0) free(glob_bin_maxes);

    // I don't know if we need this, but without it I sometimes get segfaults
    MPI_Finalize();

    return 0;
}
