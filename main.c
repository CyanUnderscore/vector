#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
    void (*push)(struct Vector*, int value);
    void (*pop)(struct Vector*, int value);
    void (*read)(struct Vector*);
    int (*get)(struct Vector*, int value);
}Vector;

void vector_init(Vector* vec , size_t initial_capacity){
    vec->data = (int*) malloc(initial_capacity * sizeof(int));
    vec->size = 0;
    vec->capacity = initial_capacity;
    vec->push = &push;
    vec->pop = &pop;
    vec->read = &read;
    vec->get = &get;
}

void push(Vector* vec, int value){
    if(vec->size >= vec->capacity){
        vec->capacity += vec->size - vec->capacity + 1;
        vec->data = (int*) realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size] = value;
    vec->size++;
}

void read(Vector* vec){
    for(int i = 0 ;i < vec->size;i++){
        printf("%d\n", vec->data[i]);
    }
    printf("%d elements in the array\n", vec->size + 1);
}

int get(Vector* vec, int index){
    if(index <= vec->size){
        return vec->data[index];
    }
    fprintf(stderr, "index out of bounds\n");
    exit(1);
}

void pop(Vector* vec, int index){
    for (int i = index; i < vec->size; i++){ 
          vec->data[i] = vec->data[i+1]; 
    }
    vec->size -= 1;
    vec->capacity -= 1;
    vec->data = (int*) realloc(vec->data, vec->capacity * sizeof(int));
}

int main(){ // testing the functions
    Vector vec;
    vector_init(&vec, 0);
    for(int i = 0; i < 10; i++){
        push(&vec, i);
    }
    read(&vec);
    printf("%d\n", get(&vec, 2));
    pop(&vec, 2);
    read(&vec);
    return 0;
}
