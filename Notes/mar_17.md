# GPUs Party Time

Most computing power in modern supercomputers is provided by GPUs.

Usage in supercomputers is well divided between Intel, AMD, and Nvidia GPUs.

Kronos CYCL 
: A DSL that can run across multiple GPUs, as opposed to CUDA which can only run 
  on Nvidia GPUs.

Main difference between CPU and GPU cores is that the CPU has _latency_ oriented 
cores while the GPU has _throughput_ oriented cores. A CPU core will be very fast 
for a serial program, while a GPU will typically have many more (100x, 1000x) 
more cores than the CPU that are not as good as the CPU cores.

GPUs typically have much smaller caches than a CPU, and typically do not have control 
structures like branch predication or data forwarding.

GPU ALUs are heavily pipelined for high throughput.

## Parallel Programming Tips 

- Aim to approach the memory bandwidth with algorithm implementations. Typically bandwidth 
  will be the biggest bottleneck.

## Cuda / OpenCL Execution Model 

Program _starts_ on the CPU, then data is moved to the GPU, then a _kernel_ (a section of 
code that executes on the GPU) runs on the data, then the final result is put back in 
memory.

Host
: CPU 

Device 
: GPU

GPU execution is executed as a _grid_ of threads. All threads run the same kernel (which is a 
single program, multiple data, AKA SPMD, model). Each thread has a unique index that it uses 
to compute correct memory addresses and make control decisions.

Each _grid_ is made up of _thread blocks_, which are in turn made up by individual _threads_.
Each block and each thread have their own ids. This means that to specifically identify a 
particular thread, you need _both_ the block id and thread id, as thread id's can be shared 
across different blocks.

Typically, the GPU itself will do the block scheduling itself.

When accessing ids in the code, you do it by coordinate. For example, for a 1D block you would 
access the thread id as `threadIdx.x`.

```cuda
// Cuda example of calculating the index for a binary op kernel

auto i = blockIdx.x * // 'x' coordinate of the block index 
         blockDim.x + // 'x' size of the block 
         threadIdx.x; // 'x' id of the thread

C[i] = op(A[i], B[i]); // access correct memory for this thread
```

This is really similar to how to index a 2D array that is implemented as a 1D array.

```c
auto DIM = 10;

int a[DIM][10] = {0};

int* a_ptr = a;

// Access data value at (5,5)
a[5][5] = 5;
assert(a[5][5] == 5);

// Access (5,5) another way
a_ptr[5 * DIM + 5] = 4;
assert(a[5][5] == 4);
```

Deciding the size of the block impacts performance.

## Vector Sum Example

```cuda 
// Typical C 
void vecAdd(float* A, float* B, float* C, int n) 
{
    for (auto i = 0; i < n; i++)
        C[i] = A[i] + B[i]
}

// Typical main 
int main()
{
    // ... setup ...
    vecAdd(A_h, B_h, C_h, N); // _h indicates host
}

// Cuda C 
#include <cuda.h>

__global__
void vecAddKernal(const float* A_d, const float* B_d, float* C_d, const int n)
{
    // Calculate this thread index
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    // Check bounds and perform operation
    if (i < n) 
        C_d[i] = A_d[i] + B_d[i];
}


void vecAddCuda(/*in*/ const float* A_h, 
                /*in*/ const float* B_h, 
                /*out*/ float* C_h, 
                /*in*/ const int n)
{
    const auto size = sizeof(float) * n;

    const float* A_d, B_d;
    float* C_d;

    // 1. Allocate Device code 
    // (return statement of `cudaMalloc` is error code, which is why we pass the address 
    //  of the device pointer on the stack)
    cudaMalloc((void**) &A_d, size);
    cudaMalloc((void**) &A_d, size);
    cudaMalloc((void**) &C_d, size);

    // 2. Transfer host memory to device memory (don't need C as we don't care about the 
    // initial values of C_h)
    cudaMemcpy(A_d, A_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B_h, size, cudaMemcpyHostToDevice);
   
    // 3.0 Launch kernel 
    vecAddKernel<<<ceil(n/256.0), 256>>>(A_d, B_d, C_d, n);

    // 3.1 Alternate way of launching the kernel 
    const dim3 DimGrid(ceil(n/256), 1, 1);
    const dim3 DimBlock(256, 1, 1);
    vecAddKernel<<<DimGrid, DimBlock>>>(A_d, B_d, C_d, n);

    // 3.2 Wait for kernel to finish 
    cudaSynchronize();

    // 4. Transfer back to host memory (don't need A, B, as they are not modified)
    cudaMemcpy(C_h, C_d, size, cudaMemcpyDeviceToHost);

    // 5. Free memory
    cudaFree(A_d);
    cudaFree(B_d);
    cudaFree(C_d);
}
```
