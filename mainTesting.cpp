#include "BMP.h"

std::tuple<uint8_t, uint8_t, uint8_t> BGRtoYCbCr(std::tuple<uint8_t, uint8_t, uint8_t> bgr)
{
    uint8_t b = std::get<0>(bgr);
    uint8_t g = std::get<1>(bgr);
    uint8_t r = std::get<2>(bgr);

    uint8_t y  = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
    uint8_t cb = (uint8_t)(-0.1687 * r - 0.3313 * g + 0.5 * b + 128);
    uint8_t cr = (uint8_t)(0.5 * r - 0.4187 * g - 0.0813 * b + 128);

    return std::make_tuple(y, cb, cr);
}

int main()
{
    std::ifstream picture;
    picture.open("C:/git/JPEG/Sony-a7c-Shotkit-2.bmp", std::ios::binary);
    if(!picture)
    {
        std::cerr << "Error reading picture";
        exit(1);
    }

    std::ofstream output;
    output.open("C:/git/JPEG/Testing.bmp", std::ios::binary);
    if(!output)
    {
        std::cerr << "Error opening picture";
        exit(1);
    }

    BMP::readBMP(picture);    
    BMP::printBMP();

    // Go to pixel data
    picture.clear();
    picture.seekg((int)BMP::header.offset);

    // Do it only when original values are no longer necessary
    BMP::info.bdiSize = 0x28;
    BMP::header.offset = 0x36;

    output.write(reinterpret_cast<char*>(&BMP::header), 0x0e);
    output.write(reinterpret_cast<char*>(&BMP::info), 0x28);

    // Row size 
    int rowSize = (int)ceil(((int)BMP::info.BitCount * (int)BMP::info.Width) / 32) * 4;
    uint8_t *row = new uint8_t[rowSize];
    uint8_t *ptr;


    for(int i = 0; i < BMP::info.Height; i++)
    {
        picture.read(reinterpret_cast<char*>(row), rowSize);
        ptr = row;

        for(int j = 0; j < rowSize; j+=3)
        {
            uint8_t *temp = ptr;
            std::tuple<uint8_t, uint8_t, uint8_t> bgr = {*ptr, *(++ptr), *(++ptr)};
            std::tuple<uint8_t, uint8_t, uint8_t> ycbcr = BGRtoYCbCr(bgr);
            *temp = std::get<0>(ycbcr);
            *(++temp) = 0x0;
            *(++temp) = 0x0;
            ptr++;
        }

        output.write(reinterpret_cast<char*>(row), rowSize);
    }

    picture.close();
    output.close();
    delete[] row;
    return 0;
}