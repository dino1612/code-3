#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

struct Stack {
    int items[MAX_SIZE];
    int top;
};

typedef struct Stack Stack;

void initialize(Stack* s) {
    s->top = -1;
}

int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

int evaluatePostfix(char* exp) {
    Stack s;
    initialize(&s);
    int i, operand1, operand2;
    for (i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');
        }
        else {
            operand2 = pop(&s);
            operand1 = pop(&s);
            switch (exp[i]) {
            case '+':
                push(&s, operand1 + operand2);
                break;
            case '-':
                push(&s, operand1 - operand2);
                break;
            case '*':
                push(&s, operand1 * operand2);
                break;
            case '/':
                push(&s, operand1 / operand2);
                break;
            default:
                printf("Invalid operator\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return pop(&s);
}

int main() {
    char exp[MAX_SIZE];
    printf("Enter postfix expression: ");
    fgets(exp, MAX_SIZE, stdin);
    exp[strcspn(exp, "\n")] = 0; // Remove trailing newline from fgets input
    int result = evaluatePostfix(exp);
    printf("Result: %d\n", result);
    return 0;
}
