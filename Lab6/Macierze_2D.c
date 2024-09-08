
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {
    int index = row * cols + col;
    return A[index];
}

void set(int cols, int row, int col, int *A, int value) {
    int index = row * cols + col;
    A[index] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int s = 0;
            for (int k = 0; k < colsA; ++k) {
                s += get(colsA , i , k , A) * get(colsB , k , j , B);
            }
            set(colsB, i , j , AB , s);
        }
    }
}

void read_mat(int rows, int cols, int *t) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            scanf("%d" , &t[i * cols + j]);
        }
    }
}

void print_mat(int rows, int cols, int *t) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d" , t[i * cols + j]);
        }
        printf("\n");
    }
}

int read_char_lines(char *array[]) {
    int line_count = 0;
    char buffer[BUF_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int length = strlen(buffer);
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        int size = strlen(buffer) + 1;
        char *line = (char *)malloc(size * sizeof(char));

        strncpy(line, buffer, size);

        array[line_count] = line;

        line_count++;
    }

    return line_count;
}

void write_char_line(char *array[], int n) {
    printf("%s" , array[n]);
}

void delete_lines(char *array[]) {
    int index = 0;

    while (array[index] != NULL){
        free(array[index]);
        index++;
    }
}

int read_int_lines_cont(int *ptr_array[]){
    int index = 0;
    int ctr = 0;
    char *char_tmp;
    const char del[] = " ";
    char buff_tmp[BUF_SIZE];

    while (fgets(buff_tmp, BUF_SIZE , stdin) != NULL){
        char_tmp = strtok(buff_tmp , del);
        ptr_array[ctr][index] = atoi(char_tmp);

        while (char_tmp != NULL){
            index++;
            char_tmp = strtok(NULL , del);
            if(char_tmp != NULL){
                ptr_array[ctr][index] = atoi(char_tmp);
            }
        }
        ctr++;
        ptr_array[ctr] = &ptr_array[ctr - 1][index];
        index = 0;
    }
    return ctr;
}

void write_int_line_cont(int *ptr_array[], int n) {
    int index = 0;

    while (&ptr_array[n][index] != &ptr_array[n + 1][0]){
        printf("%d" , ptr_array[n][index]);
        index++;
    }
}

typedef struct {
    int *values;
    int len;
    double average;
} line_type;

void sort_by_average(line_type lines_array[], int line_count);

int read_int_lines(line_type lines_array[]) {
    int line_count = 0;

    while (1) {
        char line[100];
        if (fgets(line, sizeof(line), stdin) == NULL || line[0] == '\n') {
            break;
        }

        int value_count = 0;
        int *values = malloc(sizeof(int));

        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            int value = atoi(token);
            values[value_count] = value;
            value_count++;

            int *tmp = realloc(values, (value_count + 1) * sizeof(int));
            if (tmp == NULL) {
                free(values);
                return line_count;
            }
            values = tmp;

            token = strtok(NULL, " \t\n");
        }

        double sum = 0.0;
        for (int i = 0; i < value_count; i++) {
            sum += values[i];
        }
        double average = sum / value_count;

        lines_array[line_count].values = values;
        lines_array[line_count].len = value_count;
        lines_array[line_count].average = average;

        line_count++;
    }

    return line_count;
}

void write_int_line(line_type lines_array[], int n) {
    for (int i = 0; i < lines_array[n].len; ++i) {
        printf("%d" , lines_array[n].values[i]);
    }
    printf("\n%.2f" , lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
    int index = 0;

    while (index < line_count){
        free(array[index].values);
        index++;
    }
}

int cmp (const void *a, const void *b) {
    const line_type *firstA = (const line_type *) a;
    const line_type *secondB = (const line_type *) b;

    return (int) (firstA->average - secondB->average);
}

void sort_by_average(line_type lines_array[], int line_count) {
    qsort(lines_array , line_count , sizeof(line_type) , &cmp);
}

typedef struct {
    int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
    for (int i = 0; i < n_triplets; ++i) {
        scanf("%d %d %d" , &triplet_array[i].r , &triplet_array[i].c , &triplet_array[i].v);
    }
    return n_triplets;
}

int cmp_triplets(const void *t1, const void *t2) {
    const triplet *firstA = (const triplet *) t1;
    const triplet *secondB = (const triplet *) t2;

    return firstA->r != secondB->r ? firstA->r - secondB->r : firstA->c - secondB->c;
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
    int j = 0;
    int ctr = 0;
    int tmp = 0;

    qsort(triplet_array, n_triplets, sizeof(triplet) , &cmp_triplets);

    for (int i = 0; i < n_triplets; ++i) {
        V[i] = triplet_array[i].v;
        C[i] = triplet_array[i].c;
    }

    for (int i = 0; i < rows; ++i) {
        R[i] = ctr;

        while (i == triplet_array[j].r){
            tmp++;
            j++;
        }
        ctr = tmp;
    }
    R[rows] = n_triplets;
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
    for (int i = 0; i < rows; ++i) {
        y[i] = 0;
        for (int j = R[i]; j < R[i+1]; ++j) {
            y[i] += V[j] * x[C[j]];
        }
    }
}

void read_vector(int *v, int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d" , &v[i]);
    }
}

void write_vector(int *v, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d" , v[i]);
    }
    printf("\n");
}

int read_int() {
    char c_buf[BUF_SIZE];
    fgets(c_buf, BUF_SIZE, stdin);
    return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
    int to_do = read_int();

    int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
    int n, lines_counter, rowsA, colsA, rowsB, colsB;
    int rows, cols, n_triplets;
    char *char_lines_array[TAB_SIZE] = { NULL };
    int continuous_array[TAB_SIZE];
    int *ptr_array[TAB_SIZE];
    triplet triplet_array[TAB_SIZE];
    int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
    int x[TAB_SIZE], y[TAB_SIZE];
    line_type int_lines_array[TAB_SIZE];

    switch (to_do) {
        case 1:
            scanf("%d %d", &rowsA, &colsA);
            read_mat(rowsA, colsA, A);
            scanf("%d %d", &rowsB, &colsB);
            read_mat(rowsB, colsB, B);
            prod_mat(rowsA, colsA, colsB, A, B, AB);
            print_mat(rowsA, colsB, AB);
            break;
        case 2:
            n = read_int() - 1; // we count from 1 :)
            ptr_array[0] = continuous_array;
            read_int_lines_cont(ptr_array);
            write_int_line_cont(ptr_array, n);
            break;
        case 3:
            n = read_int() - 1;
            read_char_lines(char_lines_array);
            write_char_line(char_lines_array, n);
            delete_lines(char_lines_array);
            break;
        case 4:
            n = read_int() - 1;
            lines_counter = read_int_lines(int_lines_array);
            sort_by_average(int_lines_array, lines_counter);
            write_int_line(int_lines_array, n);
            delete_int_lines(int_lines_array, lines_counter);
            break;
        case 5:
            scanf("%d %d %d", &rows, &cols, &n_triplets);
            n_triplets = read_sparse(triplet_array, n_triplets);
            read_vector(x, cols);
            make_CSR(triplet_array, n_triplets, rows, V, C, R);
            multiply_by_vector(rows, V, C, R, x, y);
            write_vector(V, n_triplets);
            write_vector(C, n_triplets);
            write_vector(R, rows + 1);
            write_vector(y, rows);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}
