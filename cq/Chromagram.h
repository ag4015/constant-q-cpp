/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    Constant-Q library
    Copyright (c) 2013-2015 Queen Mary, University of London

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

#ifndef CQCHROMAGRAM_H
#define CQCHROMAGRAM_H

#include "CQBase.h"
#include "CQParameters.h"

class CQSpectrogram;

class Chromagram
{
public:
    struct Parameters {
	Parameters(cq_float sr) :
	    sampleRate(sr),
	    lowestOctave(0),
	    octaveCount(7),
	    binsPerOctave(36),
	    tuningFrequency(static_cast<cq_float>(440.0f)),
            q(1.0f),                    // Q scaling factor
            atomHopFactor(0.25f),       // hop size of shortest temporal atom
            threshold(0.0005f),         // sparsity threshold for resulting kernel
            window(CQParameters::WindowType::SqrtBlackmanHarris) // window shape
        { }

        /**
         * Sampling rate of input signal.
         */
	cq_float sampleRate;

        /**
         * Octave number of lowest octave to include in the
         * chromagram. Numbering is per ASA standard with -1 as the
         * first octave in the MIDI range and middle-C being C4. The
         * octave starts at C.
         */
	int lowestOctave;

        /**
         * Number of source constant-Q octaves to wrap around into the
         * single-octave chroma output.
         */
	int octaveCount;

        /**
         * Number of constant-Q transform bins per octave and the
         * number of bins in the chroma output.
         */
	int binsPerOctave;

        /**
         * Frequency of concert A, used when mapping the note-based
         * octave extents into frequency extents for the constant-Q
         * transform.
         */
	cq_float tuningFrequency;

        /**
         * Spectral atom bandwidth scaling factor.
         */
        cq_float q;
        
        /**
         * Hop size between temporal atoms, where 1 == no overlap and
         * smaller values indicate overlapping atoms.
         */
        cq_float atomHopFactor;
        
        /**
         * Sparsity threshold for Constant-Q kernel: values with
         * magnitude smaller than this are truncated to zero.
         */
        cq_float threshold;

        /**
         * Window shape to use for the Constant-Q kernel atoms.
         */
        CQParameters::WindowType window;
    };

    Chromagram(Parameters params);
    virtual ~Chromagram();

    CQBase::RealBlock process(const CQBase::RealSequence &);
    CQBase::RealBlock getRemainingOutput();

    cq_float getMinFrequency() const { return m_minFrequency; }
    cq_float getMaxFrequency() const { return m_maxFrequency; }

    std::string getBinName(int bin) const;
    
    bool isValid() const;
    int getColumnHop() const;
    int getLatency() const;
    
private:
    Parameters m_params;
    CQSpectrogram *m_cq;
    cq_float m_minFrequency;
    cq_float m_maxFrequency;
    CQBase::RealBlock convert(const CQBase::RealBlock &);
};

#endif


    
