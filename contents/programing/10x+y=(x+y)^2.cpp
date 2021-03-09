#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/times.h> // 構造体tmsを使うために必要.
#include <time.h>
#include <unistd.h>
using namespace std;
// #include <gmpxx.h>

// コンパイル時に
// -lgmpxx -lgmp
// int => mpz_class

// printf("%d\n", x); =>
// std::cout << x << "\n";
// scanf("%d", &x); =>
// std::cin >> x;

int main(int argc, char **argv) {
	for (int x = 1; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			cout << x << y << " " << (x + y) * (x + y);
			if (10 * x + y == (x + y) * (x + y)) {
				cout << " true";
			}
			cout << "\n";
		}
	}

	return 0;
}
