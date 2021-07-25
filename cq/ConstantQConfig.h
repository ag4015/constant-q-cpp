#ifndef CONSTANTQ_CONFIG_H
#define CONSTANTQ_CONFIG_H


#ifndef USE_DOUBLE
typedef float cq_float;
#define POW(x,y) powf(static_cast<cq_float>(x),static_cast<cq_float>(y))
#else
typedef double cq_float;
#define POW(x,y) pow(static_cast<cq_float>(x),static_cast<cq_float>(y))
#endif


#endif // CONSTANTQ_CONFIG_H
