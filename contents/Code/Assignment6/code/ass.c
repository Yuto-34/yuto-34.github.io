#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>  // 構造体tmsを使うために必要．
#include <time.h>
#include <unistd.h>

// 1910098 Yuto Uematsu
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
        printf("%d\n", n);
        printf("\n");
    }
    if (n > SIZE) { /* エラー処理 (n > SIZE) */
        printf("error: Size should be less than or equal to %d.\n", SIZE);
        return 1;
    }

    for (i = 0; i < n; i++) vecX[i] = C; /* vecX準備；初期値代入 */

    Simal_Read(matA, vecB);      /* 問題の読み込み */
    if (verbose) {               // -vならば
        Simal_Write(matA, vecB); /* 清書 */
    }

    // 係数マトリクスの下準備：各行を対角成分で割る
    for (j = 0; j < n; j++) {
        int c = 0;
        C = matA[j][j];                              // 対角成分事態に操作は不要
        for (k = j_min[j]; k < n - j_max[j]; k++) {  // 範囲から0成分を除外
            c++;
            if (j != k) {                      //対角でない場合
                matA[j][k] = -matA[j][k] / C;  //後でmatA[j][k]を足すだけで良いようにしている
            }
        }
        vecB[j] = vecB[j] / C;
        // printf("j:%d c:%d\n",j,c);
    }

    times(&tfrom); /* 計算時間計測開始 */

    cc = 0;                         // ただの回数カウンタ
    cont = 1;                       // 収束判定用
    while (cont && (cc < LIMIT)) {  // 収束してない && カウンタが上限回数に達していない(200未満)
        if (!map) {                 // -m で無い場合の処理
            printf("%03d: ", cc);
            V_Write(vecX);  // 暫定解の書き出し
        }

        for (j = 0; j < n; j++) {                        // Jacobi 法による計算
            Sum = vecB[j];                               // 初期解(対角成分で除済み)
            for (k = j_min[j]; k < n - j_max[j]; k++) {  // 範囲から0成分を除外
                if (j != k) {
                    Sum += matA[j][k] * vecX[k];  // 積和計算, matA の符号は反転済み
                }
            }
            vecT[j] = Sum;  // 次の解として保存
        }
        cc++;

        if (map) {
            printf("%03d: ", cc);
        }
        cont = 0;
        for (i = 0; i < n; i++) {                                                    /* 収束状況の確認 */
            p = 999;                                                                 // p は精度，初期値999(めっちゃ精度悪い)
            if (vecT[i] != 0 && (p = fabs((vecT[i] - vecX[i]) / vecT[i])) > prec) {  // 次の解との相対誤差を計算
                cont = 1;
            }
            if (map) {                                                                       /* 有効桁数マップの作成 */
                dig = (long)(-log(p) / log(10.0) + 0.5);                                     // 少数以下の桁数を計算
                if (dig > 35) dig = 35;                                                      // 35よりも大きければ35に縮める
                if (dig < 0) dig = 0;                                                        // 0未満なら0に収める
                printf("%c", (dig <= 0) ? '.' : ((dig < 10) ? '0' + dig : 'A' + dig - 10));  // 有効桁を特殊な手法で表示
                if (i % 100 == 99) printf("\n");
            }
            vecX[i] = vecT[i];  // 次の解を暫定会に代入
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