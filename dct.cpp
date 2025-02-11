#include "dct.h"
// Definitions of DCT class

float dct::cosines[64] = {0};
float dct::coefficients[8] = {1};

dct::dct()
{
    float* ptr = cosines;
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            *(ptr++) = cos(((2 * y + 1) * x * M_PI)/16);

    coefficients[0] = 1/sqrt(2);
}

dct::~dct()
{
    // DESTRUCTOR
}

void dct::transform(float *block)
{
    float *dependency = new float[64];
    float *ptr = block;

    // Try to make a not so nested transformation max 2 for loops

    delete[] dependency;
}

// testing
int main()
{
    dct test;
}