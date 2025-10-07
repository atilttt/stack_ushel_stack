#include "stack.h"
#include "stack_security_from_miit.h"



void CanaryDivision(unsigned int *canary_older, unsigned int *canary_junior)
{ 
    *canary_junior = (unsigned int)(CANARY_VALUE & MASK);
    *canary_older = (unsigned int)((CANARY_VALUE >> 32) & MASK); 
}

unsigned long long CanaryRestoring(unsigned int canary_older, unsigned int canary_start)
{ 
    return ((unsigned long long)canary_older << 32) | (long long)canary_start; 
}

size_t TotalBytes(int capacity)
{

    return sizeof(int) * (capacity + 4);
}



void ResizeArray(STACK *my_stack, int new_capacity)
{
    CheckPointer(my_stack);

    size_t new_total = TotalBytes(new_capacity);
    int *tempary = my_stack->array_for_elements - 2;

    int *temp_array = (int*)realloc(tempary, new_total);
    if (!temp_array)
    { 
        #ifdef NORMAL_MOD
            fprintf(stderr, "memory allocated\n");
            exit(MEMORY_ALLOCATED);
        #endif 

        #ifdef DEBUG_MOD
            StackDump(my_stack, __LINE__ , __func__);
        #endif
    }

    my_stack->array_for_elements = temp_array + 2;
    my_stack->capacity = new_capacity;

    unsigned int canary_older, canary_junior = 0;
    CanaryDivision(&canary_older, &canary_junior);

    my_stack->array_for_elements[my_stack->size] = (int)canary_older;
    my_stack->array_for_elements[my_stack->size + 1] = (int)canary_junior;

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        {
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif
}


void StackCtor(STACK *my_stack, const int doublecup, const char *name_stack)
{
    CheckPointer(my_stack);


    my_stack->canary_r = CANARY_VALUE;
    my_stack->canary_l = CANARY_VALUE;
    
    my_stack->capacity = doublecup;
    my_stack->size = 0;
    my_stack->name_stack = name_stack;

    if (my_stack->capacity < 0)
    {
        #ifdef NORMAL_MOD
            fprintf(stderr, "Capacity is negative\n");
            exit(CAPACITY_IS_NEGATIVE);
        #endif

        #ifdef DEBUG_MOD
            my_stack->stack_error = CAPACITY_IS_NEGATIVE;
            StackDump(my_stack, __LINE__, __func__);
        #endif
    }


    size_t total = TotalBytes(my_stack->capacity);

    my_stack->array_for_elements = (int*)calloc(total / sizeof(int), sizeof(int));
    if (!my_stack->array_for_elements){
    #ifdef NORMAL_MOD
        fprintf(stderr, "NULL pointer\n");
        exit(MEMORY_ALLOCATED);
    #endif

    #ifdef DEBUG_MOD
        StackDump(my_stack, __LINE__, __func__);
    #endif 
    }

    unsigned int canary_older, canary_junior = 0; // создаем две переменные для деления нашей канарейки
    CanaryDivision(&canary_older,&canary_junior);  //сообственно делим нашу канарейку, передаем адреса по понятной причине
    my_stack->array_for_elements[my_stack->size] = canary_older; //канарейка устанавливается в начало
    my_stack->array_for_elements[my_stack->size + 1] = canary_junior; 

    my_stack->array_for_elements[my_stack->size + 2] = canary_older;
    my_stack->array_for_elements[my_stack->size + 3] = canary_junior;
    
    my_stack->array_for_elements += 2;

    my_stack->hash = HashForStruct(my_stack); 

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        { 
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif
}

void StackDtor(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    my_stack->array_for_elements -= 2; //возвращаем указатель на место (на начало)
    free(my_stack->array_for_elements);

    my_stack->array_for_elements = NULL;
    my_stack->capacity = 0;
    my_stack->size = 0;
    my_stack->name_stack = NULL;
    my_stack->canary_l = 0;
    my_stack->canary_r = 0;
    my_stack->stack_error = GOOD;
    
    #ifdef DEBUG_MOD
        CheckStackDtor(my_stack);
        if (my_stack->stack_error != GOOD)
        { 
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif
}

void PushB(STACK *my_stack, int value)
{ 
    CheckPointer(my_stack);

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        {    
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif

    if (my_stack->size >= my_stack->capacity)
    { 
        int new_capacity = (my_stack->capacity == 0) ? 4 : my_stack->capacity * 2;
        ResizeArray(my_stack, new_capacity);
    }

    my_stack->array_for_elements[my_stack->size] = value;
    my_stack->size++;

    unsigned int canary_older, canary_junior = 0;
    CanaryDivision(&canary_older, &canary_junior);

    my_stack->array_for_elements[my_stack->size] = canary_older;
    my_stack->array_for_elements[my_stack->size + 1] = canary_junior;

    my_stack->hash = HashForStruct(my_stack); 

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        {
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif
}

void PopA(STACK *my_stack)
{ 
    CheckPointer(my_stack);

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        {
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif 

    if (my_stack->size <= 0)
    {
        #ifdef NORMAL_MOD
            fprintf(stderr, "The size is negativ\n");
            exit(SIZE_IS_NEGATIV);
        #endif

        #ifdef DEBUG_MOD
            my_stack->stack_error = SIZE_IS_NEGATIV;
            StackDump(my_stack, __LINE__, __func__);
        #endif
    }

    my_stack->size--;

    unsigned int canary_older, canary_junior = 0;
    CanaryDivision(&canary_older, &canary_junior);

    my_stack->array_for_elements[my_stack->size] = canary_older;
    my_stack->array_for_elements[my_stack->size + 1] = canary_junior;

    if ((my_stack->size < my_stack->capacity / 4) && my_stack->capacity > 4)
    {
        int new_capacity = my_stack->capacity / 2;
        ResizeArray(my_stack, new_capacity);
    }

    my_stack->hash = HashForStruct(my_stack); 

    #ifdef DEBUG_MOD
        StackOk(my_stack);
        if (my_stack->stack_error != GOOD)
        {    
            StackDump(my_stack, __LINE__, __func__);
        }
    #endif
}
void PrintStack(STACK *my_stack)
{
    CheckPointer(my_stack);
    
    printf("\nstack output\n");
    printf("----------------------------------\n");
    
    for (size_t i = 0; i < my_stack->size; i++)
    {
        printf("%zu element ---> [%d]\n", i, my_stack->array_for_elements[i]);
    }
    
}

void Instruction(void)
{
    printf("=============================================\n");
    printf("           STACK PROGRAM INSTRUCTION         \n");
    printf("=============================================\n");
    printf("Usage: ./stack_program [OPTIONS]\n\n");
    printf("OPTIONS:\n");
    printf("  -h, --help    Show this help message\n");
    printf("  (no args)     Run interactive stack demo\n\n");
    printf("FEATURES:\n");
    printf("  - Stack with canary protection\n");
    printf("  - Automatic memory management\n");
    printf("  - Overflow detection\n");
    printf("  - Error logging to file(if you have the debug mode enabled)\n");
    printf("  - To enable debug mode, comment out the line #define NORMAL_MOD\n");
    printf("=============================================\n");
}