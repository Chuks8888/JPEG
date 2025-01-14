#include "BMP.h"


int main()
{
    std::ifstream picture;
    picture.open("C:/git/JPEG/Sony-a7c-Shotkit-2.bmp", std::ios::binary);
    if(!picture)
    {
        std::cerr << "Error reading picture";
        exit(1);
    }

    BMP::readBMP(picture);    
    BMP::printBMP();

    picture.close();
    std::cerr << "over\n";
    return 0;
}