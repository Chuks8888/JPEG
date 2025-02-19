#ifndef DCT_H
#define DCT_H

#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


class dct
{
    private:
        static float cosines[64];
        static float coefficients[8];
        static bool init;

        float getSum(int u, int v, float arr[]);

    public:
        dct();
        ~dct();

        // This should be an inner class, to make this method private
        // so that this function is not called
        // on an array of a different size (i.e. not 64 elements)
        void transform(float arr[]);   
};

#endif