#include <iostream>
#include "wave.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "Welcome to Skelesynth!" << endl;
    Wave wavFile = Wave("hello.wav", 10000);
    wavFile.write();

    return 0;
}
