#include <math.h>
#include <stdio.h>
#include <unistd.h>

static unsigned char cosTable[256] = {0};
void initCosTable();

int main(int argc, char **argv)
{
    initCosTable();
    long totalCounts = 100000;
    int counts1=4, counts2 = 7;
    int counter1 = counts1;
    int counter2 = counts2;
    int index1 = 0;
    int index2 = 0;
    int dir1=1, dir2 = 1;
    int sign1=1,sign2=1;
    while (--totalCounts) {
        long sum = (sign1 * cosTable[index1] + sign2 * cosTable[index2]) / 2;
        if (counter1-- == 0) {
            counter1 = counts1;
            index1 += dir1;
            if (index1 == 0 || index1 == 255) {
                dir1 = -dir1;
                if (index1 == 255) {
                    sign1 = -sign1;
                }
            }
        }
        if (counter2-- == 0) {
            counter2 = counts2;
            index2 += dir2;
            if (index2 == 0 || index2 == 255) {
                dir2 = -dir2;
                if (index2 == 255) {
                    sign2 = -sign2;
                }
            }
        }
        printf("%ld\n", sum);
    }
}

void initCosTable()
{
    short index;
    double angle;
    for (index = 0, angle=0.0f; index < 256; angle += M_PI_2/255.0f, ++index) {
        cosTable[index] = (unsigned char)(255.0f * cos(angle));
    }
}
