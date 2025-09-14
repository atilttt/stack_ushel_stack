#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

int StackOk(STACK *my_stack)
{ 
    CheckPointer(my_stack);

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

    if (my_stack->array_for_elements == NULL)
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

void CheckStackDtor(STACK *my_stack)
{
    CheckPointer(my_stack);

    if (my_stack->capacity > 0)
    {
        fprintf(stderr, "StackDtor did not reset capacity\n");
        exit(STACK_DTOR_ERROR);
    }
    if (my_stack->size > 0)
    { 
        fprtinf(stderr, "StackDtor did not reset size\n");
        exit(STACK_DTOR_ERROR);
    }
    if(my_stack->name_stack != NULL)
    {
        fprintf(stderr, "StackDtor didn't set the pointer to zero\n");
        exit(STACK_DTOR_ERROR);
    }
    if (my_stack->array_for_elements != NULL)
    {
        fprintf(stderr, "StackDtor didn't set the pointer to zero\n");
        exit(STACK_DTOR_ERROR);
    }
}

void StackDump(STACK *my_stack, const int line_call)
{ 
    CheckPointer(my_stack);

    FILE *log = fopen("log.txt", "w");
    assert(log);
    fprintf(log, "========== WELCOME TO THE STACK ==========\n\n\n");
    
    fprintf(log, "Let's see what the silent verification has brought out. (called from line %d))\n", line_call);
    fprintf(log, "\n--------------------------------------------------------\n");

    switch(my_stack->stack_error)
    {
        case SIZE_IS_NEGATIV:
            fprintf(log, "As we can see, the size is negative, does this even happen?\n");
            break;
        case CAPACITY_IS_NEGATIVE:
            fprintf(log, "Brother, why is our capacity negative?\n");
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
        default:
            fprintf(log, "And where is the stack name?\n");
            exit(CRITICAL_ERROR); //тоже самое
            break; 
    } 
    
    fprintf(log, "Brief description of the stack\n\n");

    fprintf(log, "\n================================================\n");
    fprintf(log, "\n================================================\n");
    fprintf(log, "The address of the first element --> %p \
                  The address of the last element --> %p \
                  Stack address --> %p \
                  Number of stack elements --> %d \
                  Capacity stack --> %d \
                  Name stack --> %s\n", my_stack->array_for_elements, &my_stack->array_for_elements[my_stack->size], my_stack, my_stack->size, my_stack->capacity, my_stack->name_stack);

    for (size_t i = 0; i < my_stack->size; i++) // вот сообственно тот самый сигфолт, который я тогда поймал, обратился к нулевому указателю
    {
        fprintf(log, "[%d] ===> %d elements", my_stack->array_for_elements[i], i);
    }
    fprintf(log, "\n================================================\n");
    fprintf(log, "\n================================================\n");


    fprintf(log, "\n\n========== GOODBAY ==========\n\n");
    fclose(log);

    exit(CRITICAL_ERROR);
}