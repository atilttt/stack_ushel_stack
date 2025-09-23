#ifndef STACK_SECURITY_FROM_MIIT_H
#define STACK_SECURITY_FROM_MIIT_H

#define DEBUG_MOD

//#define NORMAL_MOD


#include "stack.h"

static unsigned long long CANARY_VALUE = 0xDEADCAFEDEADCAFEULL;
static unsigned long long MASK = 0xFFFFFFFF;

typedef enum    
{ 
    SIZE_IS_NEGATIV = 544,
    STACK_OVERFLOW = 1488,
    CRITICAL_ERROR = 111,
    CAPACITY_IS_NEGATIVE = 200, 
    NAME_INDEFINITE = 934,
    MEMORY_ALLOCATED = 505,
    CHIVO = 403,
    STACK_DTOR_ERROR = 401, //я решил особо не распинаться почему неправильно отработал деструктор, сразу просто ошибка и понятно где она

    CANARY_RIGHT_DEAD = 303, 
    CANARY_LEFT_DEAD = 301, // эти ошибки говорят, что канарейка в структуре умерла

    CANARY_LEFT_IN_BUFFER_DEAD = 201, //эти говорят, что канарейка в массиве умерла
    CANARY_RIGHT_IN_BUFFER_DEAD = 202,

    GOOD = 0 
} ERORRS;


/**
 * @brief функция тихой верификации
 * @param my_stack указатель на структуру
 */
ERORRS StackOk(STACK *my_stack);

/**
 * @brief функция проверяющая указатель на структуру
 * @param my_stack указатель на структуру
 */
void CheckPointer(STACK *my_stack);

/**
 * @brief функция для проверки деструктора
 * @param STACK *my_stack указатель на структуру
 */
ERORRS CheckStackDtor(STACK *my_stack);

/**
 * @brief функция дампа(ЭТО ВОТ ТАКОЕ ВОТ БОЛЬШОЕ ОПИСАНИПЕ СТЕКА)
 * @param *my_stack указатель на стек
 * @param const int line_call строка, которая вызвала дамп
 * @param const char *name_function_call функция, которая заколила зайти в дамп
 */
void StackDump(STACK *my_stack, const int line_call, const char *name_function_call);

#else


#endif //STACK_SECURITY_FROM_MIIT_H