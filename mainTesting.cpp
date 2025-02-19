#include "BMP.h"
#include "dct.h"

void BGRtoYCbCr(uint8_t b, uint8_t g, uint8_t r, uint8_t &y, uint8_t &cb, uint8_t &cr)
{
    y  = (uint8_t)(0.299 * r + 0.587 * g + 0.114 * b);
    cb = (uint8_t)(-0.1687 * r - 0.3313 * g + 0.5 * b + 128);
    cr = (uint8_t)(0.5 * r - 0.4187 * g - 0.0813 * b + 128);
}

// Instead of using the integers, we will use their reciprocals
// So that we can multiply instead of dividng, saving some time
const float quantizationMatrix[] = { 
    0.0625f,   0.090909f, 0.1f,      0.0625f,   0.041667f, 0.025f,    0.019608f, 0.016393f,
    0.083333f, 0.083333f, 0.071429f, 0.052632f, 0.038462f, 0.017241f, 0.016667f, 0.018182f,
    0.071429f, 0.076923f, 0.045455f, 0.041667f, 0.025f,    0.017544f, 0.014493f, 0.017857f,
    0.071429f, 0.058824f, 0.045455f, 0.034483f, 0.019608f, 0.011494f, 0.0125f,   0.016129f,
    0.055556f, 0.045455f, 0.027027f, 0.017857f, 0.014706f, 0.009174f, 0.009709f, 0.012987f,
    0.041667f, 0.028571f, 0.018182f, 0.015625f, 0.012346f, 0.009615f, 0.00885f,  0.01087f,
    0.020408f, 0.015625f, 0.012821f, 0.011494f, 0.009709f, 0.008264f, 0.008333f, 0.009901f,
    0.013889f, 0.01087f,  0.010526f, 0.010204f, 0.008929f, 0.01f,     0.009709f, 0.010101f
};

// TO DO: 
// Add the quality factor feature
void quantizize(float arr[], int qualityFactor)
{
    for(int i = 0; i < 64; i++)
        arr[i] = round(arr[i] * quantizationMatrix[i]);
}

int main()
{

    std::ifstream picture;
    picture.open("C:/Users/Hugo/git/JPEG/Canon-5DMarkII-Shotkit-4.bmp", std::ios::binary);
    if(!picture)
    {
        std::cerr << "Error reading picture\n";
        exit(1);
    }

    std::ofstream output;
    //output.open("C:/git/JPEG/Testing.bmp", std::ios::binary);
    output.open("C:/Users/Hugo/git/JPEG/Testing.bmp", std::ios::binary);
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
    BMP::info.bdiSize = 0x28;
    BMP::header.offset = 0x36;

    output.write(reinterpret_cast<char*>(&BMP::header), 0x0e);
    output.write(reinterpret_cast<char*>(&BMP::info), 0x28);

    // Row size 
    int rowSize = (int)ceil((BMP::info.BitCount * BMP::info.Width) / 32) * 4;
    int pixelRowSize = (int)(BMP::info.Width * BMP::info.BitCount / 8);
    int paddingBytes = rowSize - pixelRowSize;

    uint8_t *row = new uint8_t[rowSize];
    uint8_t *ptr;

    std::vector<uint8_t> Y, Cb, Cr;

    uint8_t y, cb, cr;
    for(int i = 0; i < BMP::info.Height; i++)
    {
        picture.read(reinterpret_cast<char*>(row), rowSize);
        ptr = row;

        for(int j = 0; j < pixelRowSize; j+=3)
        {
            uint8_t *temp = ptr;
            BGRtoYCbCr(*(ptr++), *(ptr++), *(ptr++), y, cb, cr);
            
            // NOT CORRECT
            *temp = y;
            *(++temp) = y;
            *(++temp) = y;
            // NOT CORRECT
        }

        output.write(reinterpret_cast<char*>(row), rowSize);
    }

    picture.close();
    output.close();
    delete[] row;
    return 0;
}