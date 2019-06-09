#include "wave.h"
#include <iostream>
#include <string.h>
#include <cmath>

/**
 * @param filename Path to the wave file relative to the working directory
 * @param sampleRate Sample rate in kilohertz
 */
Wave::Wave(char* filename, uint32_t sampleRate) {
    // Set filename
    this->filename = filename;
    this->header.sampleRate = sampleRate;
}

bool Wave::write() {
    std::cout << filename << std::endl;
    FILE *fp = fopen(filename, "w+b");

    // Generate data
    int numSamples = 100000 * 1 * 1;
    int value = 0;
    double *pData = new double[numSamples];
    // for (int i = 0; i < numSamples; i++) {
    //     value += 10000000;
    //     pData[i] = value;
    // }
    for (int i = 0; i < numSamples; i++) {
        pData[i] = sin(i) * 10000;
    }

    WaveHeader header;

    memcpy(header.mainChunkID, "RIFF", 4);
    header.mainChunkSize = (numSamples * sizeof(int)) + 36;
    memcpy(header.mainChunkFormat, "WAVE", 4);
    memcpy(header.formatChunkID, "fmt ", 4);
    header.formatChunkSize = 16;
    header.audioFormat = 1;
    header.numChannels = 1;
    header.sampleRate = 100000;
    header.bitsPerSample = sizeof(int) * 8;
    header.byteRate = header.sampleRate * header.numChannels * (header.bitsPerSample / 8);
    header.blockAlign = header.numChannels * (header.bitsPerSample / 8);
    memcpy(header.dataChunkID, "data", 4);
    header.dataChunkSize = numSamples * header.numChannels * (header.bitsPerSample / 8);

    fwrite(&header, sizeof(header), 1, fp);
    fwrite(pData, header.dataChunkSize, 1, fp);

    return true;
}



Wave::~Wave() {}