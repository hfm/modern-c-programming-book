#include <stdbool.h>
#include "stack.h"

static bool isStackFull(const Stack *p) {
    return p->top == p->size;
}

static bool isStackEmpty(const Stack *p) {
    return p->top == 0;
}

bool validateRange(Validator *pThis, int val) {
    Range *pRange = (Range *)(pThis->pData);
    return pRange->min <= val && val <= pRange->max;
}

bool validatePrevious(Validator *pThis, int val) {
    PreviousValue *pPrevious = (PreviousValue *)(pThis->pData);
    if (val < pPrevious->previousValue) return false;
    pPrevious->previousValue = val;
    return true;
}

bool validate(Validator *p, int val) {
    if (! p) return false;
    return p->validate(p, val);
}

bool push(Stack *p, int val) {
    if (! validate(p->pValidator, val) || isStackFull(p)) return false;
    p->pBuf[p->top++] = val;
    return true;
}

bool pop(Stack *p, int *pRet) {
    if (isStackEmpty(p)) return false;
    *pRet = p->pBuf[--p->top];
    return true;
}

int main(int argc, char const* argv[])
{
    int buf[16];
    Stack stack = newStack(buf);
    push(&stack, 123);

    Range range = {0, 9};
    Validator validator = rangeValidator(&range);
    Stack stack2 = newStackWithValidator(buf, &validator);
    push(&stack2, 123);

    PreviousValue previous = {0};
    Validator validator2 = previousValidator(&previous);
    Stack stack3 = newStackWithValidator(buf, &validator2);
    push(&stack3, 123);
    return 0;
}
