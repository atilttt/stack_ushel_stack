#include "stack_ushel_stack.h"
#include <stdio.h>
#include "stack_security_from_miit.h"

ERORRS StackOk(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    if (my_stack->canary_r != CANARY_VALUE)
    { 
        my_stack->stack_error = CANARY_RIGHT_DEAD;
        return CANARY_RIGHT_DEAD;
    }

    if (my_stack->canary_l != CANARY_VALUE)
    {
        my_stack->stack_error = CANARY_LEFT_DEAD;
        return CANARY_LEFT_DEAD;
    }

    if(my_stack->size < 0)
    { 
        my_stack->stack_error = SIZE_IS_NEGATIV;
        return SIZE_IS_NEGATIV;
    }

    if (my_stack->capacity <= 0)
    {
        my_stack->stack_error = CAPACITY_IS_NEGATIVE; //ну возможно и ноль, что тоже странно 
        return CAPACITY_IS_NEGATIVE; 
    }
    
    if (my_stack->size > my_stack->capacity)
    { 
        my_stack->stack_error = STACK_OVERFLOW;
        return STACK_OVERFLOW;
    }

    if (my_stack->temporary_array == NULL || my_stack->array_for_elements == NULL)
    { 
        my_stack->stack_error = MEMORY_ALLOCATED;
        return MEMORY_ALLOCATED;
    }

    if(my_stack->name_stack == NULL)
    {
        my_stack->stack_error = NAME_INDEFINITE;
        return NAME_INDEFINITE;
    }

    my_stack->stack_error = GOOD;
    return GOOD;
}

void CheckPointer(STACK *my_stack)
{ 
    if (my_stack == NULL)
    { 
        fprintf(stderr, "========== POINTER ON THE STACK IS NULL ============");
        exit(CRITICAL_ERROR);
    }
}

ERORRS CheckStackDtor(STACK *my_stack)
{
    CheckPointer(my_stack);

    if (my_stack->capacity > 0)
    {
        my_stack->stack_error = STACK_DTOR_ERROR;
        return STACK_DTOR_ERROR;
    }
    if (my_stack->size > 0)
    { 
        my_stack->stack_error = STACK_DTOR_ERROR;
        return STACK_DTOR_ERROR;
    }
    if(my_stack->name_stack != NULL)
    {
        my_stack->stack_error = STACK_DTOR_ERROR;
        return STACK_DTOR_ERROR;
    }
    if (my_stack->array_for_elements != NULL)
    {
        my_stack->stack_error = STACK_DTOR_ERROR;
        return STACK_DTOR_ERROR;
    }

    return GOOD;
}

void StackDump(STACK *my_stack, const int line_call, const char *name_function_call)
{ 
    CheckPointer(my_stack);

    FILE *log = fopen("log.txt", "a");
    assert(log);
    fprintf(log, "========== WELCOME TO THE STACK ==========\n\n\n");
    
    fprintf(log, "--------------------------------------------------------\n");
    fprintf(log, "Let's see what the silent verification has brought out.\n");
    fprintf(log, "THE DUMP WAS CAUSED BY %d line\n", line_call);
    fprintf(log, "\"%s\" caused the dump\n", name_function_call);
    fprintf(log, "ERROR CODE: %d\n", my_stack->stack_error);
    fprintf(log, "--------------------------------------------------------\n");

    switch(my_stack->stack_error)
    {
        case SIZE_IS_NEGATIV:
            fprintf(log, "As we can see, the size is negative, does this even happen?\n");
            break;
        case CAPACITY_IS_NEGATIVE:
            fprintf(log, "Brother, why is our capacity negative?(maybee zero)\n");
            break;
        case STACK_OVERFLOW:
            fprintf(log, "size > capacity ---> STACK OVERFLOW\n");
            break;
        case NAME_INDEFINITE:
            fprintf(log, "And where is the stack name?\n");
            break;
        case MEMORY_ALLOCATED:
            fprintf(log, "The trouble is, the array is lost\n");
            exit(CRITICAL_ERROR); //ну это сто проц крит, просто надо поймать это, иначе сигфолт ебаный
        case STACK_DTOR_ERROR:
            fprintf(log, "We're here because the destructor didn't work properly.(looking at the output)\n");
            break;
        case CANARY_RIGHT_DEAD:
            fprintf(log, "The right canary is dead\n");
            break;
        case CANARY_LEFT_DEAD:
            fprintf(log, "The left canary is dead\n");
            break;
        default:
            fprintf(log, "And where is the stack name?\n");
            exit(CRITICAL_ERROR); //тоже самое
            break; 
    } 
    
    fprintf(log, "\n================================================\n");
    fprintf(log, "Brief description of the stack");
    fprintf(log, "\n================================================\n");
    fprintf(log, "The name stack --> %s \n\
Capacity stack --> %d \n\
Size stack --> %d\n\
Stack address --> %p\n\
The adress of the last element --> %p\n\
The address of the penultimate element --> %p\n\
The address of the first element --> %p\n", my_stack->name_stack, my_stack->capacity, my_stack->size, my_stack, my_stack->array_for_elements + my_stack->capacity - 1, my_stack->array_for_elements + my_stack->capacity - 2, my_stack->array_for_elements);

    for (size_t i = 0; i < my_stack->size; i++) // вот сообственно тот самый сигфолт, который я тогда поймал, обратился к нулевому указателю
    {
        fprintf(log, "[%d] ===> %zu elements\n", my_stack->array_for_elements[i], i);
    }
    fprintf(log, "================================================\n");
    fprintf(log, "================================================\n");


    fprintf(log, "\n\n========== GOODBAY ==========\n\n");
    fclose(log);

    exit(CRITICAL_ERROR);
}