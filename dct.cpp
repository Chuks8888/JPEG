#include "dct.h"

// Instead of using the integers, we will use their reciprocals
// So that we can multiply instead of dividng, saving some time
const float quantizationMatrix[] = { // FOR LUMINANCE
    0.0625f,   0.090909f, 0.1f,      0.0625f,   0.041667f, 0.025f,    0.019608f, 0.016393f,
    0.083333f, 0.083333f, 0.071429f, 0.052632f, 0.038462f, 0.017241f, 0.016667f, 0.018182f,
    0.071429f, 0.076923f, 0.045455f, 0.041667f, 0.025f,    0.017544f, 0.014493f, 0.017857f,
    0.071429f, 0.058824f, 0.045455f, 0.034483f, 0.019608f, 0.011494f, 0.0125f,   0.016129f,
    0.055556f, 0.045455f, 0.027027f, 0.017857f, 0.014706f, 0.009174f, 0.009709f, 0.012987f,
    0.041667f, 0.028571f, 0.018182f, 0.015625f, 0.012346f, 0.009615f, 0.00885f,  0.01087f,
    0.020408f, 0.015625f, 0.012821f, 0.011494f, 0.009709f, 0.008264f, 0.008333f, 0.009901f,
    0.013889f, 0.01087f,  0.010526f, 0.010204f, 0.008929f, 0.01f,     0.009709f, 0.010101f
};

// Definitions of DCT class

float dct::cosines[64] = {0};
float dct::coefficients[8] = {0};
bool dct::init = 0;

float dct::getSum(int u, int v, int block[])
{
    float sum = 0.0;
    int *blockPtr = block;

    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            sum += ((float)*(blockPtr++) * cosines[u * 8 + x] * cosines[v * 8 + y]);

    return sum;
}

void dct::quantizize(float arr[], int qualityFactor)
{
    for(int i = 0; i < 64; i++)
        arr[i] = round(arr[i] * quantizationMatrix[i]);
}

dct::dct()
{
    if(!init)
    {
        // Calculating the frequency matrix
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

void dct::transform(int block[])
{
    float *dependency = new float[64];
    float *ptr = dependency;

    for(int u = 0; u < 8; u++)
        for(int v = 0; v < 8; v++)
            *(ptr++) = (getSum(u, v, block) * coefficients[u] * coefficients[v] * 0.25);

    quantizize(dependency, 0);

    for(int i = 0; i < 64; i++)
        block[i] = dependency[i];
    //std::cout << " " << dependency[i];

    delete[] dependency;
}

// int main()
// {
//     int test[] = {
//         -76, -73, -67, -62, -58, -67, -64, -55,
//         -65, -69, -73, -38, -19, -43, -59, -56,
//         -66, -69, -60, -15, 16, -24, -62, -55,
//         -65, -70, -57, -6, 26, -22, -58, -59,
//         -61, -67, -60, -24, -2, -40, -60, -58,
//         -49, -63, -68, -58, -51, -60, -70, -53,
//         -43, -57, -64, -69, -73, -67, -63, -45,
//         -41, -49, -59, -60, -63, -52, -50, -34
//     };

//     dct terts;
//     terts.transform(test);
//     for(int i = 0; i < 8; i++)
//     {
//         for (int j = 0 ; j < 8; j++)
//         {
//             std::cout << " " <<test[i * 8 + j];
//         }
//         std::cout << std::endl;
//     }
// }
