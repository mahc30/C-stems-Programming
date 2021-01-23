#ifndef STACK_H
#define STACK_H
//Forward declaration
struct stack;

//Memory Allocation
struct stack *stack_new();

//Constructor
void stack_ctor(struct stack_t *, void *);

//Behaviour
bool stack_is_empty(struct stack_t *);
void stack_push(struct stack_t *, void *);
void *stack_pop(struct stack_t *);
void *stack_peek(struct stack_t *);

#endif