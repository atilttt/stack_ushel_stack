#include "stack_ushel_stack.h"

int main(int argc, char **argv)
{
    STACK my_stack = {};
    

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    { 
        Instruction();
        return 0;
    }

    int capacity = 0;
    scanf("%d", &capacity);

    StackCtor(&my_stack, capacity);
    
    PushB(&my_stack, 2);
    PushB(&my_stack, 3);
    PushB(&my_stack, 1321);
    PushB(&my_stack, 134);
    PrintStack(&my_stack);
    

    

    return 0;
}