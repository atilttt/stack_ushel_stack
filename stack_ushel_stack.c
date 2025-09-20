#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

void StackCtor(STACK *my_stack, const int doublecup)
{
    CheckPointer(my_stack);

    my_stack->canary_r = CANARY_VALUE;
    my_stack->canary_l = CANARY_VALUE;

    my_stack->capacity = doublecup;
    if (my_stack->capacity <= 0)
    {
        my_stack->stack_error = CAPACITY_IS_NEGATIVE;
        StackDump(my_stack, __LINE__, "StackCtor");
    }

    my_stack->array_for_elements = (int *)calloc(my_stack->capacity + 2 * sizeof(long long), sizeof(int));
    if (my_stack->array_for_elements == NULL){
        StackDump(my_stack, __LINE__, "StackCtor");
    }

    *((long long*)my_stack->array_for_elements) = my_stack->canary_r;
    *((long long*)(my_stack->array_for_elements + my_stack->capacity)) = my_stack->canary_l;

    my_stack->size = 0;
    my_stack->name_stack = "stack";

    if (my_stack->array_for_elements == NULL)
    {
        my_stack->stack_error = MEMORY_ALLOCATED;
        StackDump(my_stack, __LINE__, "StackCtor");
    }

    StackOk(my_stack);
}

void StackDtor(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    free(my_stack->array_for_elements);

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

    if (my_stack->size >= my_stack->capacity)
    { 
        my_stack->stack_error = STACK_OVERFLOW;
        StackDump(my_stack, __LINE__, "PushB");
    }
    
    my_stack->array_for_elements[my_stack->size] = value;
    my_stack->size++;
    
    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
        StackDump(my_stack, __LINE__, "PushB");
    else
        my_stack->stack_error = GOOD;
}


int PopA(STACK *my_stack)
{ 
    CheckPointer(my_stack);
    StackOk(my_stack);

    if (my_stack->stack_error != GOOD)
        StackDump(my_stack, __LINE__, "PopA");

    if (my_stack->size <= 0)
    { 
        my_stack->stack_error = SIZE_IS_NEGATIV;
        StackDump(my_stack, __LINE__, "PopA");
    }

    my_stack->size--;
    int deleted_element = my_stack->array_for_elements[my_stack->size];

    if (my_stack->size < my_stack->capacity / 4 && my_stack->capacity > 4)
    {
        int new_capacity = my_stack->capacity / 2;
        int *array_after_realloc = (int *)realloc(my_stack->array_for_elements,
                                                  sizeof(int) * new_capacity);

        if (array_after_realloc != NULL)
        {
            my_stack->capacity = new_capacity;
            my_stack->array_for_elements = array_after_realloc;  
        }
        else
        {
            my_stack->stack_error = MEMORY_ALLOCATED;
            StackDump(my_stack, __LINE__, "PopA");
        }
    }

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
        StackDump(my_stack, __LINE__, "PopA");

    return deleted_element;
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