#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#define TWO_DICE_SUM 11

// Fill vector with random numbers from [a, b]
void fill_with_randoms(int i_vector[], int n, int a, int b){
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        i_vector[i] = rand() % (b - a + 1) + a;
    }
}

// Calculates arithmetic mean and variance of numbers from n-element array v[]
// for n = 0: mean = variance = 0
void mean_variance(const int v[], int n, double *mean, double *variance) {
    *mean = 0;
    *variance = 0;
    if(n == 0){
        return;
    }
    for (int i = 0; i < n; ++i) {
        *mean += v[i];
    }
    *mean /= n;

    for (int i = 0; i < n; ++i) {
        *variance += pow(v[i] - *mean, 2);
    }

    *variance /= n;

}

// Fill n-element array v[] with Bernoulli sample (binary values)
void bernoulli_gen(int v[], int n, double probability) {
    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        double r = (double)rand() / RAND_MAX;
        v[i] = r <= probability ? 1 : 0;
    }
}

// Calculate pmf (probability mass function) of discrete random variable.
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void pmf(double v[], int trials) {
    srand(time(NULL));

    for (int i = 0; i < 11; ++i) {
        v[i] = 0;
    }

    for (int i = 0; i < trials; ++i) {
        int roll_1 = rand() % 6 + 1;
        int roll_2 = rand() % 6 + 1;
        int sum = roll_1 + roll_2;
        v[sum - 2] += 1.0 / trials;
    }
}

// Calculates the cumulative distribution function (v) for 'trials' numbers
// Two dice are thrown simultaneously The random variable is the sum of the
// numbers shown (the result is from [2, 12]).
// trials - number of trials
void cdf(double v[], int trials) {
    srand(time(NULL));

    for (int i = 0; i < 11; i++){
        v[i] = 0.0;
    }

    for (int i = 0; i < trials; i++) {
        int roll_1 = rand() % 6 + 1;
        int roll_2 = rand() % 6 + 1;
        v[roll_1 + roll_2 - 2] += 1.0;
    }

    v[0] = (double) v[0] / trials;
    for (int i = 1; i < 11; i++) {
        v[i] = v[i-1] + (double) v[i] / trials;
    }
}

// Histogram - bar chart for the values from v[] array of length n
// x_start - the first value on the abscissa (x increment is 1),
// y_scale - y value corresponding to single char of the histogram
void print_histogram(const double v[], int n, int x_start, double y_scale, char mark) {
    double max_val = v[0];
    for (int i = 0; i < n; ++i) {
        if(v[i] > max_val){
            max_val = v[i];
        }
    }

    for (int i = 0; i < n; i++) {
        // print x value
        printf("%2d| ", x_start + i);

        // print bars
        int num_bars = (int)(v[i] / y_scale + 0.5);
        for (int j = 0; j < num_bars; j++) {
            printf("%c", mark);
        }

        // print y value
        printf(" %.3f\n", v[i]);
    }
}

// Simulate Monty-Hall problem
// input: n - number of trials
// output: wins - number od wins if door switched
// output: win_probability - probability of win if door switched

// This function calls rand() exactly 2 times:
// the first one returns winning door number,
// the second one returns door number that the player has chosen the first time,
void monty_hall(int n, int *p_switch_wins) {
    srand(time(NULL));
    //eee

    int win_door, player_choice, open_door, switch_choice;

    *p_switch_wins = 0;

    for (int i = 0; i < n; i++) {
        win_door = rand() % 3 + 1;
        player_choice = rand() % 3 + 1;

        if (player_choice == win_door) {
            do {
                open_door = rand() % 3 + 1;
            } while (open_door == player_choice);
        } else {
            open_door = 6 - player_choice - win_door;
        }

        switch_choice = 6 - player_choice - open_door;

        if (switch_choice == win_door) {
            (*p_switch_wins)++;
        }
    }
}

// print double vector of size n (with 2 figures after the decimal point)
//void print_vector(const double v[], int n) {
//	for (int i = 0; i < n; ++i) {
//		printf("%.2f ", v[i]);
//	}
//	printf("\n");
//}

// print integer vector
void print_int_vector(const int v[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    char mark;
    int to_do, n, seed, m_h_wins, a, b, i_vector[100];
    double arithmetic_mean, variance, probability, d_vector[100];
    scanf("%d", &to_do);
    scanf("%d",&seed);
    scanf("%d",&n);
    srand((unsigned)seed);

    switch (to_do) {
        case 1: // mean_variance
            scanf("%d %d", &a, &b);
            fill_with_randoms(i_vector, n, a, b);
            mean_variance(i_vector, n, &arithmetic_mean, &variance);
            printf("%.2f %.2f\n", arithmetic_mean, variance);
            break;
        case 2: // bernoulli_gen
            scanf("%lf", &probability);
            bernoulli_gen(i_vector, n, probability);
            print_int_vector(i_vector, n);
            break;
        case 3: // pmf
            scanf(" %c", &mark);
            pmf(d_vector, n);
            print_histogram(d_vector, TWO_DICE_SUM, 2, 0.005, mark);
            break;
        case 4: // cdf
            scanf(" %c", &mark);
            cdf(d_vector, n);
            print_histogram(d_vector, TWO_DICE_SUM, 2, 0.02, mark);
            break;
        case 5: // monty_hall
            monty_hall(n, &m_h_wins);
            printf("%d %d\n", m_h_wins, n - m_h_wins);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}
