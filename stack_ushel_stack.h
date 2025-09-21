#ifndef STACK_USHEL_STACK_H 
#define STACK_USHEL_STACK_H


#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


//=====================================//

typedef struct my_stack
{

    int stack_error;
    
    const char *name_stack;  
    int capacity;
    int size;
    int *array_for_elements; //основной массив куда будем сохранять наши элементы
    char *temporary_array; //временный массив, под который будет выделяться память и туда будут засунуты канарейки, его dtor и будет чистить

    long long canary_r;
    long long canary_l; 
} STACK;

//======================================//

/**
 * @brief функция, описывающая программу
 */
void Instruction();

/**
 * @brief функция для подсчета общего количества бит для выделения памяти
 * @param int capacity наша так называемая мощность стека
 */
static size_t TotalBytes(int capacity);

/**
 * @brief функция для реалокации памяти
 * @param STACK *my_stack указатель на структуру
 * @param int new_capacity новый размер capacity
 */
static void ResizeArray(STACK *my_stack, int new_capacity);

/**
 * @brief конструктор для стека
 * @param my_stack указатель на структуру
 * @param doublecap некая емкость стека(максимальное кол-во элементов) (кидаем как константу, обещая, что здесь они не изменится)
 * @param symbol_for_macros символ для макроса, который позволяет пользователю
 *                          а)ввести имя стека руками
 *                          б)поставить имя по дефолту
 */
void StackCtor(STACK *my_stack, const int doublecap);

/**
 * @brief деструктор для стека
 * @param my_stack указатель на структуру
 */
void StackDtor(STACK *my_stack);

/**
 * @brief функция добавляющая элемент в стек
 * @param my_stack указатель на структуру
 * @param value значение, которое надо добавить в стек
 */
void PushB(STACK *my_stack, int value);

/**
  * @brief функция, удаляющая элемент из стека
  * @param *my_stack указатель на структуру
*/
void PopA(STACK *my_stack);

/**
 * @brief функция вывода стека
 * @param STACK *my_stack - указатель на структуру
 */
void PrintStack(STACK *my_stack);


#endif //STACK_USHEL_STACK_H 