# Projects 

Projects are due April 14th. They will include presentations and a group of 2-3 people.

Project proposal is due March 17th if we aren't doing the basic ideas. If we want to do 
something different, we need to approve it with Dr. Petruzza.

Requirements:

1. Code / build instructions 
2. The following implementations:
   - Serial 
   - CPU shared mem impl (threads or OpenMP)
   - GPU impl 
   - CPU distributed mem impl 
   - GPU distributed mem impl 
3. Scaling studies 
   - Shared memory (serial vs. parallel vs. gpu)
   - Distributed memory (cpu vs. gpu w/ dist mem)
4. Results validation
5. Good coding concepts including shared library functions across all impls 
   - Implement something like a `utility.h` header file.
6. Output visualization (Chat GPT + matplotlib time?)

# MPI Scatter 

If you have a buffer of data and you want to split up the chunk among processes to do 
something with each chunk, you can use `MPI_Scatter`. See slide examples for code.

If the chunking of data is not evenly partitioned, then you can use `MPI_Scatterv` to 
unevenly scatter data.

# MPI Gather 

To fetch distributed data together, we'll use `MPI_Gather`, which is basically the 
opposite of `MPI_Scatter`.

# Midterm 

Things not on the midterm:
- MPI
- Networking 
- CHPC 

Thing on the midterm:
- Pipelining 
- Caching 
- Flynn's taxonomy 
- Performance scaling 

Threads and OpenMP 
- Critical sections 
- Synch mechanisms 
- OpenMP Directives 
- Scope of variables 
- Thread scheduling 
