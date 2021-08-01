#ifndef CONSTANTQ_CONFIG_H
#define CONSTANTQ_CONFIG_H

#define USE_DOUBLE // Use double as floating point
#define MSVC // Compiled using Microsoft Visual Studio

#ifndef USE_DOUBLE
typedef float cq_float;
#define POW(x,y) powf(x,y)
#else
typedef double cq_float;
#define POW(x,y) pow(x,y)
#endif


#endif // CONSTANTQ_CONFIG_H
