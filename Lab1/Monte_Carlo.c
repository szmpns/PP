#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void monte_carlo(double a, double b, int N) {
    double c = (b - a) / N;
    double wynik = 0;
    for (int i = 0; i < N; i++) {
        double x = a + ((double) rand() / RAND_MAX) * (b - a);
        double y = ((double) rand() / RAND_MAX);
        if (y <= sin(x)) {
            wynik += c;
        }
    }
    printf("Pole powierzchni ograniczone osia Ox i wykresem funkcji sin(x) w przedziale [%g, %g] wynosi: %g\n", a, b, wynik);
}

int main() {
    srand(time(NULL));
    monte_carlo(0, 2, 1000000);
    return 0;
}