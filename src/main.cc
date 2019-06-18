#include <iostream>
#include "wave.h"

using namespace std;

int main(int argc, char const *argv[]) {
    cout << "Welcome to Skelesynth!" << endl;
    Wave wavFile = Wave("hello.wav", 50000);
    wavFile.generateSine(100, 1);
    // wavFile.generateSine(100, 2);
    // wavFile.generateSine(100, 3);
    // wavFile.generateSine(100, 4);
    // wavFile.generateSine(100, 5);
    // wavFile.generateSine(100, 6);
    if (wavFile.write()) {
        printf("Successfully wrote wave file!\n");
    } else {
        printf("Error writing wave file! Perhaps you called write without any data?\n");
    }

    return 0;
}