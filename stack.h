#ifndef STACK_USHEL_STACK_H 
#define STACK_USHEL_STACK_H


//#include <cstddef>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>



//=====================================//

typedef struct my_stack
{
    unsigned long long canary_l; 

    int stack_error;
    
    const char *name_stack;  
    int capacity;
    int size;
    int *array_for_elements; //основной массив куда будем сохранять наши элементы
    
    unsigned long long hash;

    unsigned long long canary_r;
} STACK;


//======================================//

/**
 * @brief функция, описывающая программу
 */
void Instruction(void);

/**
 * @brief функция для деления побитово канарейки
 * @param canary_d1, canary_d2 указатели типа инт, а именно два указателя которые будут хранить страшие 32 бита и младшие 32 бита канарейки (левой и правой)
 */
void CanaryDivision(unsigned int *canary_older, unsigned int *canary_junior);


/**
 * функция для восстановления канарейки (в массиве)
 * @param canary_e1, canary_e2 тоже страшие и младшие разряды по 32 бита, но эта функция склеивающая эти два разряда 
          Потому что нам надо организовать проверку нашей канарейки, как в структуре, так и в массиве 
*/
unsigned long long CanaryRestoring(unsigned int canary_older, unsigned int canary_junior);

/**
 * @brief функция для подсчета общего количества бит для выделения памяти
 * @param int capacity наша так называемая мощность стека
 */
size_t TotalBytes(int capacity);

/**
 * @brief функция для реалокации памяти
 * @param STACK *my_stack указатель на структуру
 * @param int new_capacity новый размер capacity
 */
void ResizeArray(STACK *my_stack, int new_capacity);

/**
 * @brief конструктор для стека
 * @param my_stack указатель на структуру
 * @param doublecap некая емкость стека(максимальное кол-во элементов) (кидаем как константу, обещая, что здесь они не изменится)
 * @param const char *name_stack
 */
void StackCtor(STACK *my_stack, const int doublecap, const char *name_stack);

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