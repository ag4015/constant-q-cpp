
#ifndef NAN_INF_H
#define NAN_INF_H

#include "ConstantQConfig.h"

#define ISNAN(x) (sizeof(x) == sizeof(cq_float) ? ISNANd(x) : ISNANf(x))
static inline int ISNANf(cq_float x) { return x != x; }
static inline int ISNANd(cq_float x) { return x != x; }
          
#define ISINF(x) (sizeof(x) == sizeof(cq_float) ? ISINFd(x) : ISINFf(x))
static inline int ISINFf(cq_float x) { return !ISNANf(x) && ISNANf(x - x); }
static inline int ISINFd(cq_float x) { return !ISNANd(x) && ISNANd(x - x); }

#endif
