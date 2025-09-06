#ifndef STACK_H 
#define STACK_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct my_stack
{

    int stack_error;

    const char *name_stack;
    size_t capacity;
    size_t size;
    int *array_for_elements;
    
} STACK;

/**
 * @brief конструктор для стека
 * @param my_stack указатель на структуру
 * @param capacity некая емкость стека(максимальное кол-во элементов)
 */
void StackCtor(STACK *my_stack, size_t );

/**
 * @brief деструктор для стека
 * @param my_stack указатель на структуру
 */
void StackDtor(STACK *my_stack);

/**
 * @brief функция добавляющая элемент в стек
 * @param my_stack указатель на структуру
 */
void push_b(STACK *my_stack, int value);

void pop_a(STACK *my_stack);


#endif //STACK_H 