#ifndef CONSTANTQ_CONFIG_H
#define CONSTANTQ_CONFIG_H

#define MSVC // Compiled using Microsoft Visual Studio

#ifndef USE_DOUBLE
typedef float cq_float;
#define POW(x,y) powf(x,static_cast<cq_float>(y))
#else
typedef double cq_float;
#define POW(x,y) pow(x,static_cast<cq_float>(y))
#endif


#endif // CONSTANTQ_CONFIG_H
