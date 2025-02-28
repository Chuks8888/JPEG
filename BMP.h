#ifndef BMPh
#define BMPh

#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

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
    };

    struct bdiInfo {
        uint32_t bdiSize;
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

    extern int rowSize;
    extern int pixelRowSize;
    extern int paddingBytes;
    
    void readBMP(std::ifstream& pic);
    void printBMP();
}
#pragma pack(pop)

#endif