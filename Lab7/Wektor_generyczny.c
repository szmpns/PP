#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 64

typedef struct Vector {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} Vector;

typedef struct Person {
    int age;
    char first_name[MAX_STR_LEN];
    char last_name[MAX_STR_LEN];
} Person;

typedef int(*cmp_ptr)(const void*, const void*);
typedef int(*predicate_ptr)(void*);
typedef void(*read_ptr)(void*);
typedef void(*print_ptr)(const void*);

// Allocate vector to initial capacity (block_size elements),
// Set element_size, size (to 0), capacity
void init_vector(Vector *vector, size_t block_size, size_t element_size) {
    vector -> data = malloc(block_size * element_size);

    vector->element_size = element_size;
    vector->size = 0;
    vector->capacity = block_size;
}

// If new_capacity is greater than the current capacity,
// new storage is allocated, otherwise the function does nothing.
void reserve(Vector *vector, size_t new_capacity) {
    if(new_capacity > vector->capacity){
        size_t new_s = new_capacity * vector->element_size;

        void *new_data = malloc(new_s);

        memcpy(new_data , vector->data , vector->size * vector->element_size);

        free(vector->data);

        vector->data = new_data;
        vector->capacity = new_capacity;
    }
}

// Resizes the vector to contain new_size elements.
// If the current size is greater than new_size, the container is
// reduced to its first new_size elements.

// If the current size is less than new_size,
// additional zero-initialized elements are appended
void resize(Vector *vector, size_t new_size) {
    if(new_size > vector->size){
        size_t new_cap = new_size;
        size_t new_data_siz = new_cap * vector->element_size;

        void *new_data = malloc(new_data_siz);

        memcpy(new_data , vector->data , vector->size * vector->element_size);

        size_t add_ele = new_size - vector->size;
        size_t add_data_siz = add_ele * vector->element_size;

        memset(new_data + (vector->size * vector->element_size), 0, add_data_siz);

        free(vector->data);

        vector->data = new_data;
        vector->size = new_size;
        vector->capacity = new_cap;

    } else{
        vector->size = new_size;
    }
}

// Add element to the end of the vector
void push_back(Vector *vector, void *value) {
    if (vector->size == vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        size_t new_data_size = new_capacity * vector->element_size;

        void *new_data = malloc(new_data_size);

        memcpy(new_data, vector->data, vector->size * vector->element_size);

        free(vector->data);

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    void *destination = (char *)vector->data + (vector->size * vector->element_size);
    memcpy(destination, value, vector->element_size);

    vector->size++;
}

// Remove all elements from the vector
void clear(Vector *vector) {
    vector->size = 0;
}

// Insert new element at index (0 <= index <= size) position
void insert(Vector *vector, size_t index, void *value) {
    if (vector->size == vector->capacity) {
        size_t new_capacity = vector->capacity * 2;
        size_t new_data_size = new_capacity * vector->element_size;

        void *new_data = malloc(new_data_size);

        memcpy(new_data, vector->data, vector->size * vector->element_size);

        free(vector->data);

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    size_t shift_size = (vector->size - index) * vector->element_size;
    void *shift_destination = (char *)vector->data + ((index + 1) * vector->element_size);
    void *shift_source = (char *)vector->data + (index * vector->element_size);
    memmove(shift_destination, shift_source, shift_size);

    void *insertion_point = (char *)vector->data + (index * vector->element_size);
    memcpy(insertion_point, value, vector->element_size);

    vector->size++;
}

// Erase element at position index
void erase(Vector *vector, size_t index) {
    if (index >= vector->size) {
        return;
    }

    size_t shift_size = (vector->size - index - 1) * vector->element_size;
    void *shift_destination = (char *)vector->data + (index * vector->element_size);
    void *shift_source = (char *)vector->data + ((index + 1) * vector->element_size);
    memmove(shift_destination, shift_source, shift_size);

    vector->size--;
}

// Erase all elements that compare equal to value from the container
void erase_value(Vector *vector, void *value, cmp_ptr cmp) {
    size_t index = 0;
    while (index < vector->size) {
        void *element = (char *)vector->data + (index * vector->element_size);
        if (cmp(element, value) == 0) {
            size_t shift_size = (vector->size - index - 1) * vector->element_size;
            void *shift_destination = (char *)vector->data + (index * vector->element_size);
            void *shift_source = (char *)vector->data + ((index + 1) * vector->element_size);
            memmove(shift_destination, shift_source, shift_size);

            vector->size--;
        } else {
            index++;
        }
    }
}

// Erase all elements that satisfy the predicate from the vector
void erase_if(Vector *vector, int (*predicate)(void *)) {
    size_t index = 0;
    while (index < vector->size) {
        void *element = (char *)vector->data + (index * vector->element_size);

        if (predicate(element)) {
            size_t shift_size = (vector->size - index - 1) * vector->element_size;
            void *shift_destination = (char *)vector->data + (index * vector->element_size);
            void *shift_source = (char *)vector->data + ((index + 1) * vector->element_size);
            memmove(shift_destination, shift_source, shift_size);

            vector->size--;
        } else {
            index++;
        }
    }
}

// Request the removal of unused capacity
void shrink_to_fit(Vector *vector) {
    if (vector->capacity > vector->size) {
        size_t new_capacity = vector->size;
        size_t new_data_size = new_capacity * vector->element_size;

        void *new_data = malloc(new_data_size);

        memcpy(new_data, vector->data, vector->size * vector->element_size);

        free(vector->data);

        vector->data = new_data;
        vector->capacity = new_capacity;
    }
}

// integer comparator
int int_cmp(const void *v1, const void *v2) {
    const int *int1 = (const int *)v1;
    const int *int2 = (const int *)v2;

    if (*int1 < *int2) {
        return -1;
    } else if (*int1 > *int2) {
        return 1;
    } else {
        return 0;
    }
}

// char comparator
int char_cmp(const void *v1, const void *v2) {
    const char *char1 = (const char *)v1;
    const char *char2 = (const char *)v2;

    if (*char1 < *char2) {
        return -1;
    } else if (*char1 > *char2) {
        return 1;
    } else {
        return 0;
    }
}

// Person comparator:
// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int person_cmp(const void *p1, const void *p2) {
    const Person *person1 = (const Person *)p1;
    const Person *person2 = (const Person *)p2;

    if (person1->age > person2->age) {
        return -1;
    } else if (person1->age < person2->age) {
        return 1;
    } else {
        int name_cmp = strcmp(person1->first_name, person2->first_name);
        if (name_cmp != 0) {
            return name_cmp;
        } else {
            return strcmp(person1->last_name, person2->last_name);
        }
    }
}

// predicate: check if number is even
int is_even(void *value) {
    int *intValue = (int *)value;
    return (*intValue % 2 == 0);
}

// predicate: check if char is a vowel
int is_vowel(void *value) {
    char *charValue = (char *)value;
    char c = *charValue;

    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }

    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// predicate: check if person is older than 25
int is_older_than_25(void *person) {
    Person *p = (Person *)person;
    return (p->age > 25);
}

// print integer value
void print_int(const void *v) {
    const int *intValue = (const int *)v;
    printf("%d\n", *intValue);
}

// print char value
void print_char(const void *v) {
    const char *charValue = (const char *)v;
    printf("%c\n", *charValue);
}

// print structure Person
void print_person(const void *v) {
    const Person *person = (const Person *)v;

    printf("Age: %d\n", person->age);
    printf("First Name: %s\n", person->first_name);
    printf("Last Name: %s\n", person->last_name);
}

typedef void (*print_ptr)(const void *);
// print capacity of the vector and its elements
void print_vector(Vector *vector, print_ptr print) {
    printf("Vector Capacity: %zu\n", vector->capacity);

    printf("Vector Elements:\n");
    for (size_t i = 0; i < vector->size; i++) {
        void *element = (char *)vector->data + (i * vector->element_size);
        print(element);
    }
}

// read int value
void read_int(void* value) {
    int* intValue = (int*)value;
    scanf("%d", intValue);
}

// read char value
void read_char(void* value) {
    char* charValue = (char*)value;
    scanf(" %c", charValue);
}

// read struct Person
void read_person(void* value) {
    Person* person = (Person*)value;

    scanf("%d", &person->age);

    scanf("%s", person->first_name);

    scanf("%s", person->last_name);
}

void vector_test(Vector *vector, size_t block_size, size_t elem_size, int n, read_ptr read,
                 cmp_ptr cmp, predicate_ptr predicate, print_ptr print) {
    init_vector(vector, block_size, elem_size);
    void *v = malloc(vector->element_size);
    size_t index, size;
    for (int i = 0; i < n; ++i) {
        char op;
        scanf(" %c", &op);
        switch (op) {
            case 'p': // push_back
                read(v);
                push_back(vector, v);
                break;
            case 'i': // insert
                scanf("%zu", &index);
                read(v);
                insert(vector, index, v);
                break;
            case 'e': // erase
                scanf("%zu", &index);
                erase(vector, index);
                break;
            case 'v': // erase
                read(v);
                erase_value(vector, v, cmp);
                break;
            case 'd': // erase (predicate)
                erase_if(vector, predicate);
                break;
            case 'r': // resize
                scanf("%zu", &size);
                resize(vector, size);
                break;
            case 'c': // clear
                clear(vector);
                break;
            case 'f': // shrink
                shrink_to_fit(vector);
                break;
            case 's': // sort
                qsort(vector->data, vector->size,
                      vector->element_size, cmp);
                break;
            default:
                printf("No such operation: %c\n", op);
                break;
        }
    }
    print_vector(vector, print);
    free(vector->data);
    free(v);
}

int main(void) {
    int to_do, n;
    Vector vector_int, vector_char, vector_person;

    scanf("%d%d", &to_do, &n);

    switch (to_do) {
        case 1:
            vector_test(&vector_int, 4, sizeof(int), n, read_int, int_cmp,
                        is_even, print_int);
            break;
        case 2:
            vector_test(&vector_char, 2, sizeof(char), n, read_char, char_cmp,
                        is_vowel, print_char);
            break;
        case 3:
            vector_test(&vector_person, 2, sizeof(Person), n, read_person,
                        person_cmp, is_older_than_25, print_person);
            break;
        default:
            printf("Nothing to do for %d\n", to_do);
            break;
    }

    return 0;
}
