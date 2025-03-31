# Programmers View of CUDA Memory

Each thread can:

| Read/Write |    Location     |   Cycles    |
| :--------: | :-------------: | :---------: |
|     RW     |    Registers    |  ~1 cycle   |
|     RW     |  Shared memory  |  ~5 cycles  |
|     RW     |  Global memory  | ~500 cycles |
|     R      | Constant memory |  ~5 cycles  |

In a cuda function, we can use:

- `__device__`: for device memory 
- `__shared__`: for shared memory 
- `__constant__`: for constant memory 

Normal variables just sit in a register, except pre thread arrays, which sit in 
global memory by default.

# MatMul Example

```cpp
// Serial
void MatMul(const float* M, const float* N, float* P, int Size)
{
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            float sum = 0;
            for (int k = 0; k < Size; k++) {
                float a = M[i * Size + k];
                float b = N[k * Size + j];
                sum += a * b;
            }
            P[i * Size + j] = sum;
        }
    }
}
```

```cuda
// Parallel w/ Tiling and global memory
__global__ void MatMulKernel_naive(const float* M, const float* N, float* P, int Size)
{
    auto row = blockIdx.y * blockDim.y + threadIdx.y;
    auto col = blockIdx.x * blockDim.x + threadIdx.x;

    // Bounds check
    if ((row >= Size) or (col >= Size) {
        return;
    }

    // Caculate value
    float Pvalue = 0;
    for (int k = 0; k < size) {
        float a = M[row * Size + k];
        float b = N[k * Size + col];
        Pvalue += a * b;
    }
    P[row * Size + col] = Pvalue;
}
```

```cuda 
// Parallel w/ tiling and shared memory
// Goal is to use shared memory as a cache between global memory 
// and our operation.
// The trick is doing partial sums for each tile and then adding it to 
// the pre-existing sum in P
template<size_t TILE_SIZE>
__global__ void MatMulKernel_naive(const float* M, const float* N, float* P, const int Size)
{
    // creates shared memory (faster than global memory)
    // `__shared__` indicates that this variable is shared across a block. Every 
    // thread in the block share this variable.
    __shared__ float subTileM[TILE_SIZE][TILE_SIZE];
    __shared__ float subTileN[TILE_SIZE][TILE_SIZE];
   
    const auto [bx, by, tx, ty] = {blockIdk.x, blockIdx.y, threadIdx.x, threadIdx.y};

    auto row = by * TILE_WIDTH + ty;
    auto col = bx * TILE_WIDTH + tx;

    float pvalue = 0;

    // No bounds checking here :(

    for (int q = 0; q < Width / TILE_WIDTH; q++)
    {
        // Read into the subtiles
        subTileM[ty][tx] = M[Row*Size + q*TILE_WIDTH+tx];
        subTileN[tx][ty] = N[(q*TILE_WIDTH+ty) * Size + col];

        __syncthreads();

        for (int k = 0; k < TILE_WIDTH; k++)
            pvalue += subTileM[ty][k] * subTileN[k][tx];

        __syncthreads();
    }

    P[row * Size + col] = pvalue;
}
```
