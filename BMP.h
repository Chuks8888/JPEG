#ifndef BMPh
#define BMPh

#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <array>
#include <vector>
#include <algorithm>
#include <cstring>

#pragma pack(push, 1)
namespace BMP
{
    struct fileHeader
    {
        uint16_t identity;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
        uint32_t bdiSize;
    };

    struct bdiInfo {
        int32_t Width;
        int32_t Height;
        uint16_t Planes;
        uint16_t BitCount;
        uint32_t Compression;
        uint32_t SizeImage;
        int32_t XPelsPerMeter;
        int32_t YPelsPerMeter;
        uint32_t ClrUsed;
        uint32_t ClrImportant;
    };
    
    extern fileHeader header;
    extern bdiInfo info;

    
    void readBMP(std::ifstream& pic);
    void printBMP();

    // struct bdiCore {
    //     uint16_t Width;
    //     uint16_t Height;
    //     uint16_t Planes;
    //     uint16_t BitCount;
    // };
    //bdiCore *core = nullptr;
}
#pragma pack(pop)

#endif