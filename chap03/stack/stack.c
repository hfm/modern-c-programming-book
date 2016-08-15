#include <stdbool.h>
#include "stack.h"

static bool isStackFull(const Stack *p) {
    return p->top == p->size;
}

static bool isStackEmpty(const Stack *p) {
    return p->top == 0;
}

static bool isRangeOk(const Range *p, int val) {
    return p == NULL ||
        (p->min <= val && val <= p->max);
}

bool push(Stack *p, int val) {
    if (! isRangeOk(p->pRange, val) || isStackFull(p)) return false;
    p->pBuf[p->top++] = val;
    return true;
}

bool pop(Stack *p, int *pRet) {
    if (isStackEmpty(p)) return false;
    *pRet = p->pBuf[--p->top];
    return true;
}
