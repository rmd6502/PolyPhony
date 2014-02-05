#include <math.h>
#include <stdio.h>
#include <unistd.h>


#define RATE 250000

class Voice
{
    public:
        Voice(unsigned int frequency) : frequency(frequency), counter(0), index(0), counts(RATE/frequency), amplitude(255), dir(1), sign(1) {}
        int nextValue();
        static void initCosTable();
        static unsigned char cosTable[256];
    private:
        // Counts calculated from frequency
        unsigned int frequency;
        // How many counts we've done
        unsigned char counter;
        // current index into the cosTable
        unsigned char index;
        // How many counts before inc/decrementing index
        unsigned char counts;
        // amplitude from 0-255
        unsigned char amplitude;
        // direction in cos table, 1/-1
        char dir;
        // sign in cos table, 1/-1
        char sign;
};

Voice voices[] = { Voice(10000), Voice(12000) };
unsigned char Voice::cosTable[256] = {0};

int main(int argc, char **argv)
{
    Voice::initCosTable();
    long totalCounts = 100000;
    int numVoices = sizeof(voices)/sizeof(voices[0]);
    while (--totalCounts) {
        long sum = 0;
        for (int i=0; i < numVoices; ++i) {
            sum += voices[i].nextValue();
        }
        printf("%ld\n", sum);
    }
}

int Voice::nextValue()
{
    int ret = cosTable[index] * sign * amplitude/255;
    if (counter-- == 0) {
        counter = counts;
        index += dir;
        if (index == 0 || index == 255) {
            dir = -dir;
            if (index == 255) {
                sign = -sign;
            }
        }
    }
    return ret;
}

void Voice::initCosTable()
{
    short index;
    double angle;
    for (index = 0, angle=0.0f; index < 256; angle += M_PI_2/255.0f, ++index) {
        cosTable[index] = (unsigned char)(255.0f * cos(angle));
    }
}
