#include "stack_ushel_stack.h"
#include "stack_security_from_miit.h"

int main(void)
{
    STACK my_stack = {};
    
    int capacity = 0;
    scanf("%d", &capacity);

    StackCtor(&my_stack, capacity);
    
    PushB(&my_stack, 10.2);
    //PrintStack(&my_stack);
    PushB(&my_stack, 3);
    //PrintStack(&my_stack);
    PushB(&my_stack, 1321);
    PushB(&my_stack, 'a');
    //PrintStack(&my_stack);
    //PushB(&my_stack, 'a'); 

    //PopA(&my_stack);
    //PrintStack(&my_stack);
    //PopA(&my_stack);
    //PrintStack(&my_stack);

    PrintStack(&my_stack);

    return 0;
}