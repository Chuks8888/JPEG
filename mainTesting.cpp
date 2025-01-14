#include <iostream>
#include <fstream>

int main()
{
    std::ifstream picture;
    picture.open("C:/git/JPEG/Sony-a7c-Shotkit-2.bmp");
    if(!picture)
    {
        std::cerr << "Error reading picture";
    }
    return 0;
}