#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>  // 構造体tmsを使うために必要．
#include <time.h>
#include <unistd.h>

// Yuto Uematsu 1910098
// Jacobi 法

#ifndef SIZE
#define SIZE (1024)
#endif
#ifndef LIMIT
#define LIMIT (200)
#endif

double matA[SIZE][SIZE], vecB[SIZE], vecX[SIZE], vecT[SIZE];
int n, verbose;

int j_min[SIZE];
int j_max[SIZE];

void Simal_Read(double a[SIZE][SIZE], double b[SIZE]) { /* 連立方程式の読み込み */
    for (int i = 0; i < n; i++) {
        int flag = 1;
        for (int j = 0; j < n; j++) {
            scanf("%lf", &(a[i][j]));
            if (a[i][j] == 0) {
                j_max[i]++;
                if (flag) j_min[i]++;
            } else {
                flag = 0;
                j_max[i] = 0;
            }
        }
        scanf("%lf", &(b[i]));
        printf("i:%.2d min:%.3d  max:%.3d\n", i, j_min[i], j_max[i]);
    }
        printf("\n");
}

void Simal_Write(double a[SIZE][SIZE], double b[SIZE]) { /* 連立方程式の書き出し */
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%11.3le ", a[i][j]);
        }
        printf("  %11.3le\n", b[i]);
    }
}

void V_Write(double a[SIZE]) { /* ベクトルの書き出し */
    int i;
    for (i = 0; i < n; i++) {
        printf(" %15.8le", a[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    int i, j, k, cont, cc, dig, map;
    double C, Sum, prec, p;
    struct tms tfrom, tto;
    char ch, *ptr;

    n = 0;
    verbose = 0;
    map = 0;
    C = 0;
    prec = 1e-5;

    // オプション処理 開始
    while ((ch = getopt(argc, argv, "vms:i:p:")) != -1) {
        if (ch == 'v') verbose = 1 /* おしゃべり */;
        if (ch == 'm') map = 1 /* マップ表示選択 */;
        if (ch == 's') n = atoi(optarg) /* 連立元数 Size */;
        if (ch == 'i') C = atof(optarg) /* 初期値 */;
        if (ch == 'p') { /* 要求精度 (桁数) */
            j = atoi(optarg);
            prec = 1.0;
            for (i = 0; i < j; i++) prec *= 10.0;
            prec = 1.0 / prec;
        }
    }
    // オプション処理終了

    if (n == 0) {  // nが0の時の処理
        printf("Size: ");
        scanf("%d", &n);
        printf("%d\n",n);
        printf("\n");
    }
    if (n > SIZE) { /* エラー処理 (n > SIZE) */
        printf("error: Size should be less than or equal to %d.\n", SIZE);
        return 1;
    }

    for (i = 0; i < n; i++) vecX[i] = C; /* 初期値代入 */

    Simal_Read(matA, vecB); /* 問題の読み込み */
    if (verbose) {
        Simal_Write(matA, vecB); /* 清書 */
    }

    for (j = 0; j < n; j++) { /* 係数マトリクスの下準備 */
        C = matA[j][j];
        for (k = 0; k < n; k++) {
            if (j != k) {
                matA[j][k] = -matA[j][k] / C; /* 負号の存在に注意 */
            }
        }
        vecB[j] = vecB[j] / C;
    }

    times(&tfrom); /* 計算時間計測開始 */

    cc = 0;
    cont = 1;
    while (cont && (cc < LIMIT)) {
        if (!map) {
            printf("%03d: ", cc);
            V_Write(vecX); /* 暫定解の書き出し */
        }

        for (j = 0; j < n; j++) {
            Sum = vecB[j];
            for (k = 0; k < n; k++) {
                if (j != k) {
                    Sum += matA[j][k] * vecX[k]; /* 積和計算 */
                }
            }
            vecT[j] = Sum;
        }
        cc++;

        if (map) {
            printf("%03d: ", cc);
        }
        cont = 0;
        for (i = 0; i < n; i++) { /* 収束状況の確認 */
            p = 999;
            if (vecT[i] != 0 && (p = fabs((vecT[i] - vecX[i]) / vecT[i])) > prec) {
                cont = 1;
            }
            if (map) { /* 有効桁数マップの作成 */
                dig = (long)(-log(p) / log(10.0) + 0.5);
                if (dig > 35) {
                    dig = 35;
                }
                if (dig < 0) {
                    dig = 0;
                }
                printf("%c", (dig <= 0) ? '.' : ((dig < 10) ? '0' + dig : 'A' + dig - 10));
                if (i % 100 == 99) {
                    printf("\n");
                }
            }
            vecX[i] = vecT[i];
        }
        if (map) {
            printf("\n");
        }
    }

    times(&tto); /* 計算時間計測終了 */
    printf("%03d: ", cc);
    V_Write(vecX); /* 最終解の書き出し */
    printf("    user cpu time: %.2lf [sec]\n\n", (double)(tto.tms_utime - tfrom.tms_utime) / sysconf(_SC_CLK_TCK));

    return 0;
}