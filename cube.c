#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float A, B, C;
float cubeWidth = 10;
float width = 160, height = 44;
float zBuffer[160 * 44];
char buffer[160 * 44];
int *background = " ";
int distance = 60;
float incrementSpeed = 0.6, K1 = 40;
float x, y, z, ooz;
int xp, yp, idx;

float calculateX(int i, int j, int k){
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C)+
           j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k){
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) +
           i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k){
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch){
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distance;
    ooz = 1 / z;
    xp = (int)(width / 2 + (K1 * 2 * x * ooz));
    yp = (int)(height / 2 + (K1 * y * ooz));

    idx = xp + yp * width;
    if (idx >= 0 && idx <= width * height && zBuffer[idx] < ooz) {
        zBuffer[idx] = ooz;
        buffer[idx] = ch;
    }
}

int main (){
    printf("\x1b[2J");

    while (1){
        memset(buffer, *background, width * height);
        memset(zBuffer, 0, width * height * 4);
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, *"#");
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < width * height; ++k) {
            putchar((int) k % width ? buffer[k] : 10);
        }
        A += 0.005;
        B += 0.005;
    }
    return 0;
}
// https://youtu.be/p09i_hoFdd0?t=811