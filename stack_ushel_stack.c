#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"
#include <stddef.h>


static size_t TotalBytes(int capacity)
{

    return sizeof(long long) + sizeof(int) * capacity + sizeof(long long);
}

static void ResizeArray(STACK *my_stack, int new_capacity)
{
    CheckPointer(my_stack);

    size_t new_total = TotalBytes(new_capacity);

    char *new_temporary_array_for_realloc = (char *)realloc(my_stack->temporary_array, new_total);
    if (!new_temporary_array_for_realloc)
    { 
        my_stack->stack_error = MEMORY_ALLOCATED;
        StackDump(my_stack, __LINE__ , __func__);
    }

    my_stack->temporary_array = new_temporary_array_for_realloc;

    *((long long *)(my_stack->temporary_array)) = my_stack->canary_l;
    *((long long *)(my_stack->temporary_array + sizeof(long long) + new_capacity * sizeof(int))) = my_stack->canary_r;

    my_stack->array_for_elements = (int *)(my_stack->temporary_array + sizeof(long long));
    my_stack->capacity = new_capacity;

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    {
        StackDump(my_stack, __LINE__, __func__);
    }
    

}


void StackCtor(STACK *my_stack, const int doublecup)
{
    CheckPointer(my_stack);


    my_stack->canary_r = CANARY_VALUE;
    my_stack->canary_l = CANARY_VALUE;

    my_stack->capacity = doublecup;
    if (my_stack->capacity <= 0)
    {
        my_stack->stack_error = CAPACITY_IS_NEGATIVE;
        StackDump(my_stack, __LINE__, __func__);
    }

    size_t total = TotalBytes(my_stack->capacity);

    my_stack->temporary_array = (char *)calloc(1, total); //к сожалению массив то типа int, и вот как в него засунут 64 битовое число, я так и не понял, поэтому прибегаю к таким мерам
    if(my_stack->temporary_array == NULL){
        StackDump(my_stack, __LINE__, __func__);
    }

    *((long long *)my_stack->temporary_array) = my_stack->canary_l;
    *((long long *)(my_stack->temporary_array + sizeof(long long) + sizeof(int) * my_stack->capacity)) = my_stack->canary_r; //установили две канарейки

    my_stack->array_for_elements = (int *)(my_stack->temporary_array + sizeof(long long));

    my_stack->size = 0;
    my_stack->name_stack = "stack";

    if (my_stack->array_for_elements == NULL)
    {
        my_stack->stack_error = MEMORY_ALLOCATED;
        StackDump(my_stack, __LINE__, __func__);
    }

    StackOk(my_stack);
}

void StackDtor(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    free(my_stack->temporary_array);

    my_stack->temporary_array = NULL;
    my_stack->capacity = 0;
    my_stack->size = 0;
    my_stack->name_stack = NULL;
    my_stack->array_for_elements = NULL;

    my_stack->canary_l = 0;
    my_stack->canary_r = 0;

    CheckStackDtor(my_stack);
}

void PushB(STACK *my_stack, int value)
{ 
    CheckPointer(my_stack);
    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    { 
        StackDump(my_stack, __LINE__, __func__);
    }

    if (my_stack->size >= my_stack->capacity)
    { 
        int new_capacity = my_stack->capacity * 2;
        ResizeArray(my_stack, new_capacity);
    }

    my_stack->array_for_elements[my_stack->size] = value;
    my_stack->size++;

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    {
        StackDump(my_stack, __LINE__, __func__);
    }

}

void PopA(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    {
        StackDump(my_stack, __LINE__, __func__);
    }

    if (my_stack->size <= 0)
    {
        my_stack->stack_error = SIZE_IS_NEGATIV;
        StackDump(my_stack, __LINE__, __func__);
    }

    my_stack->size--; //удалили элемент

    if ((my_stack->size < my_stack->capacity / 4) && my_stack->capacity > 4)
    {
        int new_capacity = my_stack->capacity/2;
        ResizeArray(my_stack, new_capacity);
    }

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    { 
        StackDump(my_stack, __LINE__, __func__);
    }
    
}

void PrintStack(STACK *my_stack)
{
    CheckPointer(my_stack);
    
    printf("\nstack output\n");
    printf("----------------------------------\n");
    
    for (size_t i = 0; i < my_stack->size; i++)
    {
        printf("[%zu] element ---> %d\n", i, my_stack->array_for_elements[i]);
    }
    
}