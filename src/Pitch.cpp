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

#include "Pitch.h"

#include <math.h>

#ifdef USE_DOUBLE
#define LOG(x) log(x)
#else
#define LOG(x) logf(x)
#endif

cq_float
Pitch::getFrequencyForPitch(int midiPitch,
			    cq_float centsOffset,
			    cq_float concertA)
{
    cq_float p = cq_float(midiPitch) + (centsOffset / 100);
    return concertA * POW(2.0f, (p - 69.0f) / 12.0f);
}

int
Pitch::getPitchForFrequency(cq_float frequency,
			    cq_float *centsOffsetReturn,
			    cq_float concertA)
{
    cq_float p = 12.0f * 
        (LOG(frequency / (concertA / 2.0f))) / LOG(2.0f) + 57.0f;

    int midiPitch = int(p + 0.00001f);
    cq_float centsOffset = (p - midiPitch) * 100.0f;

    if (centsOffset >= 50.0f) {
	midiPitch = midiPitch + 1;
	centsOffset = -(100.0f - centsOffset);
    }
    
    if (centsOffsetReturn) *centsOffsetReturn = centsOffset;
    return midiPitch;
}

