#include "cuda.h"
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using byte = uint8_t;

__global__ void rgb_to_gray(const byte* rgb_d, byte* gray_d, const size_t num_pixels)
{
    const auto pixel_index = blockIdx.x * blockDim.x + threadIdx.x;

    if (pixel_index < num_pixels) {
        const byte red = 0.21f * rgb_d[pixel_index];
        const byte green = 0.71f * rgb_d[pixel_index + 1];
        const byte blue = 0.07f * rgb_d[pixel_index + 2];

        const auto gray = red+green+blue;

        gray_d[pixel_index] = gray;
        gray_d[pixel_index + 1] = gray;
        gray_d[pixel_index + 2] = gray;
    }
}

auto main() -> int
{
    const auto filename = "gc_conv_1024x1024.raw";
    auto raw_data = std::ifstream(filename, std::ios::binary);

    if (!raw_data.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<byte> data;
    while (raw_data) {
        byte r, g, b;
        raw_data >> r >> g >> b;
        if (raw_data) {
            data.push_back(r);
            data.push_back(g);
            data.push_back(b);
        }
    }
    raw_data.close();

    byte *rgb_d, *gray_d;
    cudaMalloc((void**) &rgb_d, data.size());
    cudaMalloc((void**) &gray_d, data.size());

    cudaMemcpy(rgb_d, data.data(), data.size(), cudaMemcpyHostToDevice);

    rgb_to_gray<<<ceil(data.size()/256),256>>>(rgb_d, gray_d, data.size());

    cudaDeviceSynchronize();

    cudaMemcpy(data.data(), gray_d, data.size(), cudaMemcpyDeviceToHost);

    cudaFree(rgb_d);
    cudaFree(gray_d);

    auto output = std::ofstream("output.raw", std::ios::binary);
    for (const auto x : data) {
        output << x;
    }
    output.close();
}
