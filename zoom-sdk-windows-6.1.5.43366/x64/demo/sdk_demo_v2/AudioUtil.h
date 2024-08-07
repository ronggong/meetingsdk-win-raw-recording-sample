#pragma once

#include <vector>
#include <algorithm>
#include <soxr.h>


struct AudioData
{
    std::vector<char> data_;
    unsigned int sampleRate_;
    unsigned int channels_;

    AudioData(const char* data, unsigned int length, unsigned int sampleRate, unsigned int channels)
        : sampleRate_(sampleRate), channels_(channels)
        {
            data_.resize(length);
            std::copy ( data, data + length, data_.begin() );
        }
};

class AudioUtil
{
public:
    static void convertPCM16ToFloat(const std::vector<char>& pcmData, std::vector<float>& floatData);
};

class Resampler
{
public:
    Resampler(const double irate, const double orate, unsigned channels);
    ~Resampler();

    void process(const float* ibuf, const size_t ilen, float* obuf, const size_t olen);

    double getRatio() const { return ratio_; }

private:
    soxr_t soxr_;
    double ratio_;
};