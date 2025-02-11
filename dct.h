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
    public:
        dct();
        ~dct();

        void transform(float *);   
};

#endif