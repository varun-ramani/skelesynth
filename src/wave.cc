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
    this->numSamples = 0;
}

void Wave::generateSine(int ms, double frequency) {
    int samples = ((float)ms / 1000.0 ) * header.sampleRate;
    double period = 2*M_PI / header.sampleRate;
    printf("Period: %f seconds\n", period);
    for (int i = 0; i < samples; i++) {
        data.push_back(sin(frequency*i / (header.sampleRate / 3000)));
    }
    this->numSamples += samples;
}

void Wave::generateSaw(int ms) {

}

bool Wave::write() {
    if (data.size() == 0) {
        return false;
    }

    printf("Number of samples: %d\n", this->numSamples);

    std::cout << filename << std::endl;
    FILE *fp = fopen(filename, "w+b");

    memcpy(header.mainChunkID, "RIFF", 4);
    header.mainChunkSize = (this->numSamples * sizeof(int)) + 36;
    memcpy(header.mainChunkFormat, "WAVE", 4);
    memcpy(header.formatChunkID, "fmt ", 4);
    header.formatChunkSize = 16;
    header.audioFormat = 1;
    header.numChannels = 1;
    header.bitsPerSample = sizeof(int) * 8;
    header.byteRate = header.sampleRate * header.numChannels * (header.bitsPerSample / 8);
    header.blockAlign = header.numChannels * (header.bitsPerSample / 8);
    memcpy(header.dataChunkID, "data", 4);
    header.dataChunkSize = this->numSamples * header.numChannels * (header.bitsPerSample / 8);

    fwrite(&(this->header), sizeof(this->header), 1, fp);
    fwrite(this->data.data(), header.dataChunkSize, 1, fp);

    return true;
}



Wave::~Wave() {}