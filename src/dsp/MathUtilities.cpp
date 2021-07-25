/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    Constant-Q library
    Copyright (c) 2013-2014 Queen Mary, University of London

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the names of the Centre for
    Digital Music; Queen Mary, University of London; and Chris Cannam
    shall not be used in advertising or otherwise to promote the sale,
    use or other dealings in this Software without prior written
    authorization.
*/

#include "MathUtilities.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>


cq_float MathUtilities::mod(cq_float x, cq_float y)
{
    cq_float a = floor( x / y );

    cq_float b = x - ( y * a );
    return b;
}

cq_float MathUtilities::princarg(cq_float ang)
{
    cq_float ValOut;

    ValOut = mod( ang + M_PI, -2 * M_PI ) + M_PI;

    return ValOut;
}

void MathUtilities::getAlphaNorm(const cq_float *data, unsigned int len, unsigned int alpha, cq_float* ANorm)
{
    unsigned int i;
    cq_float temp = 0.0;
    cq_float a=0.0;
	
    for( i = 0; i < len; i++)
    {
	temp = data[ i ];
		
	a  += ::pow( fabs(temp), cq_float(alpha) );
    }
    a /= ( cq_float )len;
    a = ::pow( a, ( 1.0f / (cq_float) alpha ) );

    *ANorm = a;
}

cq_float MathUtilities::getAlphaNorm( const std::vector <cq_float> &data, unsigned int alpha )
{
    unsigned int i;
    unsigned int len = static_cast<unsigned int>(data.size());
    cq_float temp = 0.0f;
    cq_float a=0.0f;
	
    for( i = 0; i < len; i++)
    {
	temp = data[ i ];
		
	a  += ::pow( fabs(temp), cq_float(alpha) );
    }
    a /= ( cq_float )len;
    a = ::pow( a, ( 1.0f / (cq_float) alpha ) );

    return a;
}

cq_float MathUtilities::round(cq_float x)
{
    if (x < 0) {
        return -floor(-x + 0.5f);
    } else {
        return floor(x + 0.5f);
    }
}

cq_float MathUtilities::median(const cq_float *src, unsigned int len)
{
    if (len == 0) return 0;
    
    std::vector<cq_float> scratch;
    for (int i = 0; i < (int)len; ++i) scratch.push_back(src[i]);
    std::sort(scratch.begin(), scratch.end());

    uint64_t middle = len/2;
    if (len % 2 == 0) {
        return (scratch[middle] + scratch[middle - 1]) / 2;
    } else {
        return scratch[middle];
    }
}

cq_float MathUtilities::sum(const cq_float *src, unsigned int len)
{
    unsigned int i ;
    cq_float retVal =0.0;

    for(  i = 0; i < len; i++)
    {
	retVal += src[ i ];
    }

    return retVal;
}

cq_float MathUtilities::mean(const cq_float *src, unsigned int len)
{
    cq_float retVal =0.0;

    if (len == 0) return 0;

    cq_float s = sum( src, len );
	
    retVal =  s  / (cq_float)len;

    return retVal;
}

cq_float MathUtilities::mean(const std::vector<cq_float> &src,
                           unsigned int start,
                           unsigned int count)
{
    cq_float sum = 0.;
	
    if (count == 0) return 0;
    
    for (uint64_t i = 0; i < (int)count; ++i)
    {
        sum += src[start + i];
    }

    return sum / count;
}

void MathUtilities::getFrameMinMax(const cq_float *data, unsigned int len, cq_float *min, cq_float *max)
{
    unsigned int i;
    cq_float temp = 0.0;

    if (len == 0) {
        *min = *max = 0;
        return;
    }
	
    *min = data[0];
    *max = data[0];

    for( i = 0; i < len; i++)
    {
	temp = data[ i ];

	if( temp < *min )
	{
	    *min =  temp ;
	}
	if( temp > *max )
	{
	    *max =  temp ;
	}
		
    }
}

int MathUtilities::getMax( cq_float* pData, unsigned int Length, cq_float* pMax )
{
	unsigned int index = 0;
	unsigned int i;
	cq_float temp = 0.0;
	
	cq_float max = pData[0];

	for( i = 0; i < Length; i++)
	{
		temp = pData[ i ];

		if( temp > max )
		{
			max =  temp ;
			index = i;
		}
		
   	}

	if (pMax) *pMax = max;


	return index;
}

int MathUtilities::getMax( const std::vector<cq_float> & data, cq_float* pMax )
{
	unsigned int index = 0;
	unsigned int i;
	cq_float temp = 0.0;
	
	cq_float max = data[0];

	for( i = 0; i < data.size(); i++)
	{
		temp = data[ i ];

		if( temp > max )
		{
			max =  temp ;
			index = i;
		}
		
   	}

	if (pMax) *pMax = max;


	return index;
}

void MathUtilities::circShift( cq_float* pData, int length, int shift)
{
	shift = shift % length;
	cq_float temp;
	int i,n;

	for( i = 0; i < shift; i++)
	{
		temp=*(pData + length - 1);

		for( n = length-2; n >= 0; n--)
		{
			*(pData+n+1)=*(pData+n);
		}

        *pData = temp;
    }
}

int MathUtilities::compareInt (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void MathUtilities::normalise(cq_float *data, int length, NormaliseType type)
{
    switch (type) {

    case NormaliseType::NormaliseNone: return;

    case NormaliseType::NormaliseUnitSum:
    {
        cq_float sum = 0.0;
        for (int i = 0; i < length; ++i) {
            sum += data[i];
        }
        if (sum != 0.0) {
            for (int i = 0; i < length; ++i) {
                data[i] /= sum;
            }
        }
    }
    break;

    case NormaliseType::NormaliseUnitMax:
    {
        cq_float max = 0.0;
        for (int i = 0; i < length; ++i) {
            if (fabs(data[i]) > max) {
                max = fabs(data[i]);
            }
        }
        if (max != 0.0) {
            for (int i = 0; i < length; ++i) {
                data[i] /= max;
            }
        }
    }
    break;

    }
}

void MathUtilities::normalise(std::vector<cq_float> &data, NormaliseType type)
{
    switch (type) {

    case NormaliseType::NormaliseNone: return;

    case NormaliseType::NormaliseUnitSum:
    {
        cq_float sum = 0.0;
        for (int i = 0; i < (int)data.size(); ++i) sum += data[i];
        if (sum != 0.0) {
            for (int i = 0; i < (int)data.size(); ++i) data[i] /= sum;
        }
    }
    break;

    case NormaliseType::NormaliseUnitMax:
    {
        cq_float max = 0.0;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (fabs(data[i]) > max) max = fabs(data[i]);
        }
        if (max != 0.0) {
            for (int i = 0; i < (int)data.size(); ++i) data[i] /= max;
        }
    }
    break;

    }
}

void MathUtilities::adaptiveThreshold(std::vector<cq_float> &data)
{
    int sz = int(data.size());
    if (sz == 0) return;

    std::vector<cq_float> smoothed(sz);
	
    int p_pre = 8;
    int p_post = 7;

    for (int i = 0; i < sz; ++i) {

        int first = std::max(0,      i - p_pre);
        int last  = std::min(sz - 1, i + p_post);

        smoothed[i] = mean(data, first, last - first + 1);
    }

    for (int i = 0; i < sz; i++) {
        data[i] -= smoothed[i];
        if (data[i] < 0.0) data[i] = 0.0;
    }
}

bool
MathUtilities::isPowerOfTwo(int x)
{
    if (x < 1) return false;
    if (x & (x-1)) return false;
    return true;
}

int
MathUtilities::nextPowerOfTwo(int x)
{
    if (isPowerOfTwo(x)) return x;
    if (x < 1) return 1;
    int n = 1;
    while (x) { x >>= 1; n <<= 1; }
    return n;
}

int
MathUtilities::previousPowerOfTwo(int x)
{
    if (isPowerOfTwo(x)) return x;
    if (x < 1) return 1;
    int n = 1;
    x >>= 1;
    while (x) { x >>= 1; n <<= 1; }
    return n;
}

int
MathUtilities::nearestPowerOfTwo(int x)
{
    if (isPowerOfTwo(x)) return x;
    int n0 = previousPowerOfTwo(x), n1 = nextPowerOfTwo(x);
    if (x - n0 < n1 - x) return n0;
    else return n1;
}

cq_float
MathUtilities::factorial(int x)
{
    if (x < 0) return 0;
    cq_float f = 1;
    for (int i = 1; i <= x; ++i) {
	f = f * i;
    }
    return f;
}

int
MathUtilities::gcd(int a, int b)
{
    int c = a % b;
    if (c == 0) {
        return b;
    } else {
        return gcd(b, c);
    }
}

