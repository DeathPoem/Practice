#include <stdio.h>
#include <stdlib.h>
// bin is the PROJECT_BINARY_PATH
#include "./bin/config.h"
//#ifdef USE_MYMATH
#ifdef HAVE_POW
#include "math/MathFunctions.h"
#else
#include <math.h>
#endif
/*
 * power - calculate the power of number
 * @param base: base value
 * @param exponent: exponent value
 * @return base raised to the power exponent
 */

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("usage %s base exponent \n give me more args \n", argv[0]);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
//#ifdef USE_MYMATH
#if defined (HAVE_POW)
    printf("Now we use our own Math library. \n");
    double result = power(base, exponent);
#else
    printf("New we use the standard library. \n");
    double result = pow(base, exponent);
#endif
    printf("%g ^ %d is %g\n", base, exponent, result);
    return 0;
}

