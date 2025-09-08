#ifndef STACK_USHEL_STACK_H 
#define STACK_USHEL_STACK_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define CHOOSE(symbol)  (symbol) == 'y' ? printf("Okay, stack name: PISYA\n") : printf("Okay, enter the name you like.\n")  

//=====================================//

typedef struct my_stack
{

    int stack_error;

    const char *name_stack; // имя в стеке не должно меняться
    int capacity;
    int size;
    int *array_for_elements;
    
} STACK;

//======================================//

/**
 * @brief функция позволяющая пользователю ввести собственное имя стека
 * @param *my_stack указатель на структуру
 */
char* UserInputNameStack(STACK *my_stack);

/**
 * @brief функция, описывающая программу
 */
void Instruction();

/**
 * @brief конструктор для стека
 * @param my_stack указатель на структуру
 * @param doublecap некая емкость стека(максимальное кол-во элементов)
 * @param symbol_for_macros символ для макроса, который позволяет пользователю
 *                          а)ввести имя стека руками
 *                          б)поставить имя по дефолту
 */
void StackCtor(STACK *my_stack, size_t doublecap, const char symbol_for_macros);

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


#endif //STACK_USHEL_STACK_H 