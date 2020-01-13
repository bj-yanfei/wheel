#include <iostream>
#include "stack.hpp"

void test_array_stack()
{
    Stack<int> *stack = new ArrayStack<int>();
    stack->push(5);
    stack->push(9);
    stack->push(3);
    stack->push(8);
    stack->push(6);

    stack->show();
    delete stack;
}

void test_linked_stack()
{
    Stack<int> *stack = new LinkedStack<int>();
    stack->push(5);
    stack->push(9);
    stack->push(3);
    stack->push(8);
    stack->push(6);

    stack->show();
    delete stack;
}

int main()
{

    test_array_stack();
    test_linked_stack();

    return 0;
}