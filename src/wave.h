#ifndef WAVE_H
#define WAVE_H

#include "stdint.h"
#include <vector>

struct WaveHeader {
    // Container chunk
    unsigned char mainChunkID[4];
    unsigned int mainChunkSize;
    unsigned char mainChunkFormat[4];

    // Format chunk
    unsigned char formatChunkID[4];
    unsigned int formatChunkSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;

    // Data chunk
    unsigned char dataChunkID[4];
    unsigned int dataChunkSize;
};

class Wave {
    public:
        // Class methods
        Wave(char* filename, uint32_t sampleRate);
        ~Wave();
        bool write();

    private:
        char* filename;
        std::vector<int> data;
        WaveHeader header;
};

#endif