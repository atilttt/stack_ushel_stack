#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

int StackCtor(STACK *my_stack, size_t doublecap, const char symbol_for_macros)
{
    check_pointer(my_stack);

    my_stack->capacity = doublecap;
    if (my_stack->capacity == 0)
    {
        return ZERO_CAPACITY;
    }
    my_stack->size = 0;
    my_stack->name_stack = "STACK";
    
    my_stack->array_for_elements = (int *)calloc(my_stack->capacity, sizeof(size_t));
    if (my_stack->array_for_elements == NULL)
    {
        free(my_stack->array_for_elements);
        return MEMORY_ALLOCATED;
    }

}

void StackDtor(STACK *my_stack)
{ 
    check_pointer(my_stack);

    my_stack->capacity = 0;
    my_stack->size = 0;
    my_stack->name_stack = NULL;
    my_stack->array_for_elements = NULL;
}

void PushB(STACK *my_stack, int value)
{   
    
    if(stack_ok(my_stack) == GOOD)
        ;
    else 
        stack_dump(my_stack);

    my_stack->array_for_elements[my_stack->size] = value;
    my_stack->size++;

    if (stack_ok(my_stack) == GOOD)
        ;
    else
        stack_dump(my_stack);

}

void PopA(STACK *my_stack)
{ 
    if (stack_ok(my_stack) == GOOD)
        ;
    else
        stack_dump(my_stack);

    
    my_stack->size--;
    int deleted_el = my_stack->array_for_elements[my_stack->size++]; 
    
    if (stack_ok(my_stack) == GOOD)
        ;
    else
        stack_dump(my_stack);
}

