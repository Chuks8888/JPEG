#include "dct.h"
// Definitions of DCT class

float dct::cosines[64] = {0};
float dct::coefficients[8] = {0};
bool dct::init = 0;

float dct::getSum(int u, int v, float block[])
{
    float sum = 0.0;
    float *blockPtr = block;

    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            sum += (*(blockPtr++) * cosines[u * 8 + x] * cosines[v * 8 + y]);

    return sum;
}

dct::dct()
{
    if(!init)
    {
        float* ptr = cosines;
        for(int x = 0; x < 8; x++)
            for(int y = 0; y < 8; y++)
                *(ptr++) = cos(((2 * y + 1) * x * M_PI)/16);

        coefficients[0] = 1/sqrt(2);
        for(int i = 1; i < 8; i++)
            coefficients[i] = 1.0;

        init = 1;
    }
}

dct::~dct()
{
    // DESTRUCTOR
    std::cout << "dct testing ended\n";
}

void dct::transform(float block[])
{
    float *dependency = new float[64];
    float *ptr = dependency;

    for(int u = 0; u < 7; u++)
        for(int v = 0; v < 7; v++)
            *(ptr++) = (getSum(u, v, block) * coefficients[u] * coefficients[v] * 0.25);

    for(int i = 0; i < 64; i++)
        block[i] = dependency[i];

    delete[] dependency;
}
