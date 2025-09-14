#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

void StackCtor(STACK *my_stack, const int doublecup, const char *name_stack_user)
{
    CheckPointer(my_stack);
    StackOk(my_stack);

    my_stack->capacity = doublecup;
    my_stack->size = 0;
    my_stack->name_stack = name_stack_user;
    my_stack->array_for_elements = (int *)calloc(my_stack->capacity, sizeof(int));

    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    {
        StackDump(my_stack, 17);
    }
    else
        my_stack->stack_error = GOOD;
}

void StackDtor(STACK *my_stack)
{ 
    CheckPointer(my_stack);
    StackOk(my_stack);

    free(my_stack->array_for_elements);

    my_stack->capacity = 0;
    my_stack->size = 0;
    my_stack->name_stack = NULL;
    my_stack->array_for_elements = NULL;

    CheckStackDtor(my_stack);
}


void pushB(STACK *my_stack, int value)
{ 
    CheckPointer(my_stack);
    StackOk(my_stack);


    if (my_stack->size >= my_stack->capacity)
    { 
        my_stack->stack_error = STACK_OVERFLOW;
        StackDump(my_stack, 48);
    }

    my_stack->array_for_elements[my_stack->size] = value;
    my_stack->size++;
    
    StackOk(my_stack);
    if (my_stack->stack_error != GOOD)
    { 
        StackDump(my_stack, 46);
    }
    else
        my_stack->stack_error == GOOD;

}


void PopA(STACK *my_stack)
{ 
    CheckPointer(my_stack);
    StackOk(my_stack);


    if (my_stack->size >= 0 && (my_stack->size <= my_stack->capacity))
    { 
        my_stack->size--;
        int deleted_element = my_stack->array_for_elements[my_stack->size];
    }
    else
    { 
        my_stack->stack_error = SIZE_IS_NEGATIV;
        StackDump(my_stack, 79);
    }

    if ((my_stack->size > my_stack->capacity) && (my_stack->size < my_stack->capacity/4))
    {
        int capacity = my_stack->capacity / 4;
        int array_after_realloc = (int *)realloc(my_stack->array_for_elements, sizeof(int) * capacity);

        if (array_after_realloc != NULL)
        {
            my_stack->capacity = capacity;
            my_stack->array_for_elements = array_after_realloc;  
        }
        else
        {
            my_stack->stack_error = MEMORY_ALLOCATED; //ну вот это уже не крит, по-факту, хотя это надо как то обыграть
                                                      // мб стоит и в дамп закинуть, но потом
        }
    }
}

