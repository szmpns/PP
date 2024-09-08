#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
    int first;
    int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair* relation, int size, pair newPair){
    for (int i = 0; i < size; ++i) {
        if(relation[i].first == newPair.first && relation[i].second == newPair.second){
            return size;
        }

    }

    relation[size] = newPair;
    return size + 1;
}

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* arr, int n){
    for (int i = 0; i < n; ++i) {
        if(arr[i].first != arr[i].second){
            return 0;
        }
    }
    return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* arr, int n){
    for (int i = 0; i < n; ++i) {
        if(arr[i].first == arr[i].second){
            return 0;
        }
    }
    return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* arr, int n){
    for (int i = 0; i < n; ++i) {
        int is_sym = 0;
        for (int j = 0; j < n; ++j) {
            if(arr[i].first == arr[j].second && arr[i].second == arr[j].first){
                is_sym += 1;
                break;
            }
            if(!is_sym){
                return 0;
            }
        }
    }
    return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* arr, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(arr[i].first == arr[j].second && arr[i].second == arr[j].first && arr[i].first != arr[i].second){
                return 0;
            }
        }
    }
    return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* arr, int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if((arr[i].first == arr[j].second && arr[i].second == arr[j].first) && (arr[i].first != arr[i].second)){
                return 0;
            }
        }
    }
    return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* arr, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i].second == arr[j].first) {
                int found_transitive = 0;
                for (int k = 0; k < n; k++) {
                    if (arr[i].first == arr[k].first && arr[j].second == arr[k].second) {
                        found_transitive = 1;
                        break;
                    }
                }
                if (!found_transitive) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* arr, int n){
    for (int i = 0; i < n; i++) {
        if (arr[i].first != arr[i].second) {
            return 0;
        }
        for (int j = 0; j < n; j++) {
            if (arr[i].second == arr[j].first) {
                int found_transitive = 0;
                for (int k = 0; k < n; k++) {
                    if (arr[i].first == arr[k].first && arr[j].second == arr[k].second) {
                        found_transitive = 1;
                        break;
                    }
                }
                if (!found_transitive) {
                    return 0;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i].first == arr[j].first && arr[i].second == arr[j].second) {
                return 0;
            }
        }
    }
    return 1;
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair* arr, int n){
    int has_smallest = 0;
    int has_largest = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].first != arr[i].second) {
            return 0;
        }
        for (int j = 0; j < n; j++) {
            if (arr[i].second == arr[j].first) {
                int found_transitive = 0;
                for (int k = 0; k < n; k++) {
                    if (arr[i].first == arr[k].first && arr[j].second == arr[k].second) {
                        found_transitive = 1;
                        break;
                    }
                }
                if (!found_transitive) {
                    return 0;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i].first == arr[j].first && arr[i].second == arr[j].second) {
                return 0;
            }
        }
        int current_x = arr[i].first;
        int current_y = arr[i].second;
        int found_smaller = 0;
        int found_larger = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j].first == current_y) {
                found_smaller = 1;
            }
            if (arr[j].second == current_x) {
                found_larger = 1;
            }
        }
        if (!found_smaller) {
            has_smallest = 1;
        }
        if (!found_larger) {
            has_largest = 1;
        }
    }

    return has_smallest && has_largest;
}


// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* arr, int n){
    for (int i = 0; i < n; i++) {
        int found_connection = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i].first == arr[j].second || arr[i].second == arr[j].first) {
                found_connection = 1;
                break;
            }
        }
        if (!found_connection) {
            return 0;
        }
    }
    return 1;
}


int find_max_elements(pair* arr, int n, int* max_elements){
    int max_count = 0;

    for (int i = 0; i < n; i++) {
        int is_max = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i].second >= arr[j].second) {
                is_max = 0;
                break;
            }
        }
        if (is_max) {
            max_elements[max_count] = arr[i].second;
            max_count++;
        }
    }

    return max_count;
}

int find_min_elements(pair* arr, int n , int* min_elements){
    int min_count = 0;

    for (int i = 0; i < n; i++) {
        int is_min = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i].second <= arr[j].second) {
                is_min = 0;
                break;
            }
        }
        if (is_min) {
            min_elements[min_count] = arr[i].second;
            min_count++;
        }
    }

    return min_count;
}

int get_domain(pair* arr, int n, int* domain){
    int domain_count = 0;

    for (int i = 0; i < n; i++) {
        int is_unique = 1;
        for (int j = 0; j < domain_count; j++) {
            if (arr[i].first == domain[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            domain[domain_count] = arr[i].first;
            domain_count++;
        }
    }

    return domain_count;
}

// Case 3:

int composition(pair* R, int n1, pair* S, int n2, pair* result) {
    int result_count = 0;

    for (int i = 0; i < n1 - 1; i++) {
        for (int j = 0; j < n2 - 1 ; j++) {
            if (R[i].second == S[j].first) {
                result[result_count].first = R[i].first;
                result[result_count].second = S[j].second;
                result_count++;
                break;
            }
        }
    }

    return result_count;
}


// Comparator for pair
int cmp_pair (const void *a, const void *b) {
}

int insert_int (int *tab, int n, int new_element) {
    int i;

    for (i = 0; i < n; i++) {
        if (tab[i] > new_element)
            break;
    }

    for (int j = n; j > i; j--) {
        tab[j] = tab[j - 1];
    }

    tab[i] = new_element;

    return n + 1;
}

// Add pair to existing relation if not already there
//int add_relation (pair *tab, int n, pair new_pair) {
//}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
    int n;
    printf("Enter number of pairs: ");
    scanf("%d" , &n);

    printf("Enter %d pairs of integers: \n" , n);
    for (int i = 0; i < n; ++i) {
        pair newPair;
        scanf("%d %d" , &newPair.first , &newPair.second);
        relation[i] = newPair;
    }

    return n;
}

void print_int_array(int *array, int n) {
    printf("Length of the array: %d\n" , n);
    printf("Values of array: \n");

    for (int i = 0; i < n; ++i) {
        printf("%d" , array[i]);
    }
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];
    int max_elements[MAX_REL_SIZE];
    int min_elements[MAX_REL_SIZE];

    scanf("%d",&to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;
        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered) break;
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;
        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}