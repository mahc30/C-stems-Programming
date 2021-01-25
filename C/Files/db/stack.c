#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void stack_push(stack_t **_stack, void *_data)
{
    stack_t *new_node = stack_new();
    stack_ctor(new_node, _data);
    new_node->next = (struct stack_t *)*_stack;
    *_stack = new_node;
}

void *stack_pop(stack_t **_stack, unsigned int _dealloc_size)
{
    stack_t *the_actual_stack = *_stack;
    if (stack_is_empty(the_actual_stack))
        return NULL;

    void *data = malloc(_dealloc_size);
    if(data == NULL){
        perror("NOT ENOUGH MEMORY");
        return NULL;
    }

    //I wanted to call stack_peek(_stack); but gcc didn' want to compile
    memcpy(data, the_actual_stack -> data,_dealloc_size); 
    *_stack = (stack_t *)the_actual_stack -> next;
    free(the_actual_stack);

    return data;
}

void *stack_peek(stack_t *_stack)
{
    if (stack_is_empty(_stack))
        return NULL;

    return _stack->data;
}