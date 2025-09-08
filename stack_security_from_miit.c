#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

int Stack_Ok(STACK *my_stack)
{ 
    check_pointer(my_stack);

    if(my_stack->size < 0)
    { 
        my_stack->stack_error = SIZE_IS_NEGATIV;
        return SIZE_IS_NEGATIV;
    }

    if (my_stack->capacity < 0)
    {
        my_stack->stack_error = CAPACITY_IS_NEGATIVE; 
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

void check_pointer(STACK *my_stack)
{ 
    if (my_stack == NULL)
    { 
        fprintf(stderr, "========== POINTER ON THE STACK IS NULL ============");
        exit(CRITICAL_ERROR);
    }
}

void stack_dump(STACK *my_stack)
{ 
    check_pointer(my_stack);

    FILE *log = fopen("log.txt", "w");
    assert(log);
    fprintf(log, "========== WELCOME TO THE STACK ==========\n\n\n");
    
    fprintf(log, "Let's see what the silent verification has brought out. (maybee everything is fine)\n");
    fprintf(log, "\n--------------------------------------------------------\n");

    int errors_code = Stack_Ok(my_stack);
    switch(errors_code)
    {
        case SIZE_IS_NEGATIV:
            fprintf(log, "As we can see, the size is negative\n");
            break;
        case CAPACITY_IS_NEGATIVE:
            fprintf(log, "Brother, why is our capacity negative?\n");
            break;
        case STACK_OVERFLOW:
            fprintf(log, "size > capacity ---> STACK OVERFLOOOOW\n");
            break;
        case NAME_INDEFINITE:
            fprintf(log, "And where is the stack name?\n");
            break;
        default:
            fprintf(log, "And where is the stack name?\n");
            break; 
    }

    fprintf(log, "Wow, there are no errors, then let's see what's in our stack.\n");
    fprintf(log, "\n================================================\n");
    fprintf(log, "\n================================================\n");
    fprintf(log, "Name STACK:%s\
                  Adress STACK: %p\
                  Size STACK: %zu\
                  Capacity STACK: %zu\
                  The adress of the first element: %p\
                  The adress of the last element: %p", my_stack->name_stack , my_stack, my_stack->size, my_stack->capacity, my_stack->array_for_elements, my_stack->array_for_elements[my_stack->size]);                      
    
    for (size_t i = 0; i < my_stack->size; i++)
    {
        fprintf(log, "\"%d\"--> [%zu] elements ", my_stack->array_for_elements[i], i);
    }
    fprintf(log, "\n================================================\n");
    fprintf(log, "\n================================================\n");


    fprintf(log, "\n\n========== GOODBAY ==========\n\n");
    fclose(log);
}