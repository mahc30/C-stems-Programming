#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Forward declaration
typedef struct
{
    void *data;
    struct stack_t *next;
} stack_t;

//Memory Allocation
stack_t *stack_new()
{
    void *new_stack = malloc(sizeof(stack_t));
    if (new_stack == NULL)
    {
        perror("NOT ENOUGH MEMORY");
    }
}

//Constructor
void stack_ctor(stack_t *_stack, void *_data)
{
    _stack->data = _data;
    _stack->next = NULL;
}

bool stack_is_empty(stack_t *_stack)
{
    return !_stack;
}

void stack_push(stack_t *_stack, void *_data)
{
    stack_t *new_node = stack_new();
    stack_ctor(new_node, _data);
    new_node->next = _stack;
    _stack = new_node;
}

void *stack_pop(stack_t *_stack)
{
    if (stack_is_empty(_stack))
        return NULL;

    stack_t *first = _stack;
    _stack = _stack->next;
    void *data = first->data;
    free(first);

    return data;
}

void *stack_peek(stack_t *_stack)
{
    if (stack_is_empty(_stack))
        return NULL;

    return _stack->data;
}

