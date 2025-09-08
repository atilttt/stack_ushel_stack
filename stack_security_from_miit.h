#ifndef STACK_SECURITY_FROM_MIIT_H
#define STACK_SECURITY_FROM_MIIT_H

#include "stack_ushel_stack.h"

enum SO_GOOD
{ 
    GOOD = 1
};
    

enum ERROR_STACK_CTOR
{ 
    ZERO_CAPACITY = 404,
    MEMORY_ALLOCATED = 403
};

enum ERROS_FOR_STACK_OK
{ 
    SIZE_IS_NEGATIV = 544,
    STACK_OVERFLOW = 1488,
    POINTER_NOLIK = 1997,
    CRITICAL_ERROR = 11111111,
    CAPACITY_IS_NEGATIVE = 200, 
    NAME_INDEFINITE = 934
};



/**
 * @brief функция тихой верификации
 * @param my_stack указатель на структуру
 */
int stack_ok(STACK *my_stack);

/**
 * @brief функция проверяющая указатель на структуру
 * @param my_stack указатель на структуру
 */
void check_pointer(STACK *my_stack);

/**
 * @brief функция дампа(ЭТО ВОТ ТАКОЕ ВОТ БОЛЬШОЕ ОПИСАНИПЕ СТЕКА)
 * @param *my_stack указатель на стек
 */
void stack_dump(STACK *my_stack);

/**
 * @brief функция-вывода стека
 * @param *my_stack указатель на стек
 */
int print_stack_eshkere(STACK *my_stack);

#endif //STACK_SECURITY_FROM_MIIT_H