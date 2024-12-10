#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define MAXx 20
#define MAXy 35
#define MAXz 30
#define INF 1000000

typedef struct {
    int x, y, z;
} Tochka;

int vnutri(int x, int y, int z, int maxix, int maxiy, int maxiz) {
    return x >= 0 && x <= maxix && y >= 0 && y <= maxiy && z >= 0 && z <= maxiz;
}

void otladka(Tochka start, Tochka end, int par[MAXx + 1][MAXy + 1][MAXz + 1], int maxix, int maxiy, int maxiz) {
   
    Tochka dam[(MAXx + 1) * (MAXy + 1) * (MAXz + 1)];
    int nachalo = 0, conec = 0;

   
    int smash[6][3] = { {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };

    
    dam[conec++] = start;
    par[start.x][start.y][start.z] = 0;

    while (nachalo < conec) {
        Tochka current = dam[nachalo++];
        int curr_dist = par[current.x][current.y][current.z];

        for (int i = 0; i < 6; i++) {
            int nx = current.x + smash[i][0];
            int ny = current.y + smash[i][1];
            int nz = current.z + smash[i][2];

            if (vnutri(nx, ny, nz, maxix, maxiy, maxiz) && par[nx][ny][nz] == -1) {
                par[nx][ny][nz] = curr_dist + 1;
                dam[conec++] = Tochka { nx, ny, nz };
            }
        }
    }

    
    if (par[end.x][end.y][end.z] == -1) {
        par[end.x][end.y][end.z] = 0; 
    }
}

void printPar(int par[MAXx + 1][MAXy + 1][MAXz + 1], int maxix, int maxiy, int maxiz) {
 
    for (int z = 0; z <= maxiz; z++) {
        printf("\nz = %d:\n", z);
        for (int y = 0; y <= maxiy; y++) {
            for (int x = 0; x <= maxix; x++) {
                if (par[x][y][z] == -1) {
                    printf("  . "); 
                }
                else {
                    printf("%3d ", par[x][y][z]);
                }
            }
            printf("\n");
        }
    }
    printf("Вывод массива завершен.\n");
}

int main() {
    setlocale(LC_ALL, "Russian");

    int maxix, maxiy, maxiz;
    printf("Введите значения x, y, z: ");
    scanf_s("%d %d %d", &maxix, &maxiy, &maxiz);

    if (maxix > MAXx || maxiy > MAXy || maxiz > MAXz) {
        printf("Ошибка! Превышены максимальные размеры параллелепипеда.\n");
        return 1;
    }

    Tochka vvod1, vvod2;
    printf("Введите значения x1, y1, z1: ");
    scanf_s("%d %d %d", &vvod1.x, &vvod1.y, &vvod1.z);

    printf("Введите значения x2, y2, z2: ");
    scanf_s("%d %d %d", &vvod2.x, &vvod2.y, &vvod2.z);

    if (!vnutri(vvod1.x, vvod1.y, vvod1.z, maxix, maxiy, maxiz) ||
        !vnutri(vvod2.x, vvod2.y, vvod2.z, maxix, maxiy, maxiz)) {
        printf("Ошибка! Точки вне параллелепипеда.\n");
        return 1;
    }

    
    int par[MAXx + 1][MAXy + 1][MAXz + 1];
    for (int x = 0; x <= maxix; x++) {
        for (int y = 0; y <= maxiy; y++) {
            for (int z = 0; z <= maxiz; z++) {
                par[x][y][z] = -1; 
            }
        }
    }



   
    otladka(vvod1, vvod2, par, maxix, maxiy, maxiz);

   
    printPar(par, maxix, maxiy, maxiz);

    return 0;
}