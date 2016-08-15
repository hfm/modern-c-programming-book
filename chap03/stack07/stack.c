#include <stdbool.h>
#include "stack.h"

static bool isStackFull(const Stack *p) {
    return p->top == p->size;
}

static bool isStackEmpty(const Stack *p) {
    return p->top == 0;
}

bool validateRange(Validator *p, int val) {
    RangeValidator *pThis = (RangeValidator *)p;
    return pThis->min <= val && val <= pThis->max;
}

bool validatePrevious(Validator *p, int val) {
    PreviousValueValidator *pThis = (PreviousValueValidator *)p;
    if (val < pThis->previousValue) return false;
    pThis->previousValue = val;
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

    RangeValidator validator = newRangeValidator(0, 9);
    Stack stack2 = newStackWithValidator(buf, &validator.base);
    push(&stack2, 123);

    PreviousValueValidator validator2 = newPreviousValidator;
    Stack stack3 = newStackWithValidator(buf, &validator2.base);
    push(&stack3, 123);
    return 0;
}
