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

#ifndef CQVAMP_H
#define CQVAMP_H

#include <vamp-sdk/Plugin.h>

#include "cq/CQSpectrogram.h"

class ConstantQ;

class CQVamp : public Vamp::Plugin
{
public:
    CQVamp(cq_float inputSampleRate, bool midiPitchParameters);
    virtual ~CQVamp();

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    InputDomain getInputDomain() const { return TimeDomain; }

    std::string getIdentifier() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getMaker() const;
    int getPluginVersion() const;
    std::string getCopyright() const;

    ParameterList getParameterDescriptors() const;
    cq_float getParameter(std::string) const;
    void setParameter(std::string, cq_float);

    size_t getPreferredStepSize() const;
    size_t getPreferredBlockSize() const;

    OutputList getOutputDescriptors() const;

    FeatureSet process(const cq_float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    bool m_midiPitchParameters;
    int m_minMIDIPitch;
    int m_maxMIDIPitch;
    cq_float m_tuningFrequency;
    int m_bpo;
    int m_atomOverlap;
    bool m_useDraftDecimator;
    CQSpectrogram::Interpolation m_interpolation;

    CQSpectrogram *m_cq;
    cq_float m_maxFrequency;
    cq_float m_minFrequency;
    int m_stepSize;
    int m_blockSize;

    Vamp::RealTime m_startTime;
    bool m_haveStartTime;
    int m_columnCount;

    std::string noteName(int i) const;

    std::vector<cq_float> m_prevFeature;
    FeatureSet convertToFeatures(const std::vector<std::vector<cq_float> > &);
};


#endif
