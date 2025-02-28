#include "BMP.h"
#include "dct.h"

void BGRtoYCbCr(uint8_t b, uint8_t g, uint8_t r, uint8_t &y, uint8_t &cb, uint8_t &cr)
{
    y  = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
    cb = (uint8_t)(-0.1687 * r - 0.3313 * g + 0.5 * b + 128);
    cr = (uint8_t)(0.5 * r - 0.4187 * g - 0.0813 * b + 128);
}

void getColorChannels(uint8_t *data, uint8_t *Y, uint8_t *Cb, uint8_t *Cr)
{
    uint8_t y, cb, cr;
    for(int i = 0; i < BMP::info.Height; i++)
    {
        for(int j = 0; j < BMP::info.Width; j+=3)
        {
            BGRtoYCbCr(*(data++), *(data++), *(data++), y, cb, cr);
            *(Y++) = y;
            *(Cb++) = cb;
            *(Cr++) = cr;
        }
        for(int j = BMP::pixelRowSize; j < BMP::rowSize; j++)
            data++;
    }
    std::cout << "No memory leaks ?\n";
}

int main()
{

    std::ifstream picture;
    picture.open("C:/git/JPEG/Sony-a7c-Shotkit-2.bmp", std::ios::binary);
    if(!picture)
    {
        std::cerr << "Error reading picture\n";
        exit(1);
    }

    std::ofstream output;
    //output.open("C:/git/JPEG/Testing.bmp", std::ios::binary);
    output.open("Testing.bmp", std::ios::binary);
    if(!output)
    {
        std::cerr << "Error opening picture\n";
        exit(1);
    }

    BMP::readBMP(picture);    
    BMP::printBMP();

    // Go to pixel data
    picture.clear();
    picture.seekg((int)BMP::header.offset);

    // Do it only when original values are no longer necessary
    //BMP::info.bdiSize = 0x28;
    //BMP::header.offset = 0x36;
    //output.write(reinterpret_cast<char*>(&BMP::header), 0x0e);
    //output.write(reinterpret_cast<char*>(&BMP::info), 0x28);

    // Row size 
    //int rowSize = (int)ceil((BMP::info.BitCount * BMP::info.Width) / 32) * 4;
    //int pixelRowSize = (int)(BMP::info.Width * BMP::info.BitCount / 8);
    //int paddingBytes = rowSize - pixelRowSize;

    uint8_t *pixelData = new uint8_t[BMP::rowSize * BMP::info.Height];
    picture.read(reinterpret_cast<char*>(pixelData), BMP::rowSize * BMP::info.Height);

    uint8_t *Y = new uint8_t[(BMP::info.Width * BMP::info.Height)];
    uint8_t *Cb = new uint8_t[(BMP::info.Width * BMP::info.Height)];
    uint8_t *Cr = new uint8_t[(BMP::info.Width * BMP::info.Height)];

    getColorChannels(pixelData, Y, Cb, Cr);

    delete[] pixelData;
    delete[] Y;
    delete[] Cb;
    delete[] Cr;

    picture.close();
    output.close();
    return 0;
}