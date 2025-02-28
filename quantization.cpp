#include "BMP.h"
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

// TO DO: 
// Add the quality factor feature
void quantizize(float arr[], int qualityFactor)
{
    for(int i = 0; i < 64; i++)
        arr[i] = round(arr[i] * quantizationMatrix[i]);
}