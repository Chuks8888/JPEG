#include "BMP.h"

namespace BMP {
    fileHeader header;
    bdiInfo info;
}

void BMP::readBMP(std::ifstream& pic)
{
    pic.clear();
    pic.seekg(0);

    pic.read(reinterpret_cast<char*>(&header), sizeof(fileHeader));

    if(header.identity != 0x4D42)
    {
        std::cerr << "Not a BMP format\n";
        exit(2);
    }

    pic.read(reinterpret_cast<char*>(&info), 0x28);
    
    if(info.bdiSize < 0x0028)
    {
        std::cerr << "non compatible DIB format\n";
        exit(3);
    }

    if(info.BitCount != 0x18)
    {
        std::cerr << "bit count is not 24bpp";
        exit(4);
    }

    if(info.Width % 0x8 || info.Height % 0x8)
    {
        std::cerr << "Image widht or height is not divisible by 8";
        exit(5);
    }
}

void BMP::printBMP()
{
    std::cout << "File Header:" << std::endl;
    std::cout << "Identity: " << std::hex << header.identity << std::dec << std::endl;
    std::cout << "Size: " << header.size << " bytes" << std::endl;
    std::cout << "Reserved1: " << header.reserved1 << std::endl;
    std::cout << "Reserved2: " << header.reserved2 << std::endl;
    std::cout << "Offset to Pixel Data: " << header.offset << " bytes" << std::endl;
    std::cout << std::endl;
    std::cout << "BDI Size: " << info.bdiSize << " bytes" << std::endl;
    std::cout << "Bitmap Info Header:" << std::endl;
    std::cout << "Width: " << info.Width << " pixels" << std::endl;
    std::cout << "Height: " << info.Height << " pixels" << std::endl;
    std::cout << "Planes: " << info.Planes << std::endl;
    std::cout << "Bit Count: " << info.BitCount << " bpp" << std::endl;
    std::cout << "Compression: " << info.Compression << std::endl;
    std::cout << "Image Size: " << info.SizeImage << " bytes" << std::endl;
    std::cout << "X Pixels per Meter: " << info.XPelsPerMeter << std::endl;
    std::cout << "Y Pixels per Meter: " << info.YPelsPerMeter << std::endl;
    std::cout << "Colors Used: " << info.ClrUsed << std::endl;
    std::cout << "Important Colors: " << info.ClrImportant << std::endl;
    std::cout << std::endl;
}
