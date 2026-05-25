/*
 * stack_demo.c — C: Stack Frames, Pointers & Register Conventions
 *
 * Demonstrates:
 *   1. swap()        — passing pointers; caller builds stack args
 *   2. sfact()       — local variable on stack, pointer passed to recursion
 *   3. call_swap()   — wraps the global-variable swap shown in the notes
 *   4. stack_layout  — prints how the compiler lays locals out via scanf trick
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* 1. Global variables (like zip1/zip2 in the notes)                  */
/* ------------------------------------------------------------------ */
int zip1 = 15213;
int zip2 = 98195;

/* ------------------------------------------------------------------ */
/* 2. swap — the classic pointer swap from the notes                  */
/*    Compiler generates: load args from stack → dereference → store  */
/* ------------------------------------------------------------------ */
void swap(int *xp, int *yp) {
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

void call_swap(void) {
    /* matches the notes: push &zip2, push &zip1, call swap */
    swap(&zip1, &zip2);
}

/* ------------------------------------------------------------------ */
/* 3. sfact — recursive factorial showing pointer to a local variable  */
/*    val lives on the stack of sfact; s_helper receives &val         */
/* ------------------------------------------------------------------ */
static void s_helper(int x, int *accum) {
    if (x <= 1)
        return;
    int z = (*accum) * x;   /* local z also on stack */
    *accum = z;
    s_helper(x - 1, accum);
}

int sfact(int x) {
    int val = 1;             /* must be on stack — we take its address */
    s_helper(x, &val);       /* pass pointer to caller's local */
    return val;
}

/* ------------------------------------------------------------------ */
/* 4. Illustrate stack frame layout with address arithmetic            */
/* ------------------------------------------------------------------ */
void show_frame_layout(void) {
    int a = 1, b = 2, c = 3;
    /*
     * On x86-64 the compiler typically places locals in descending order.
     * The differences show the slot sizes the compiler chose.
     */
    printf("  &a = %p\n", (void*)&a);
    printf("  &b = %p  (offset from a: %td bytes)\n", (void*)&b, (char*)&b - (char*)&a);
    printf("  &c = %p  (offset from a: %td bytes)\n", (void*)&c, (char*)&c - (char*)&a);
    (void)a; (void)b; (void)c; /* suppress unused warnings */
}

/* ------------------------------------------------------------------ */
/* 5. Caller-save demo: edx analogue in C                             */
/*    Shows that a value in a "caller-saved" register must be saved   */
/*    by the caller if needed across a call.                          */
/* ------------------------------------------------------------------ */
static int side_effect_fn(int x) {
    /* would clobber caller-save regs internally */
    return x + 98195;
}

void caller_save_demo(void) {
    int edx_analogue = 12345;           /* lives in a caller-save reg */
    printf("  Before call : edx_analogue = %d\n", edx_analogue);
    int result = side_effect_fn(edx_analogue); /* compiler saves if needed */
    printf("  After  call : edx_analogue = %d  (unchanged — compiler saved it)\n",
           edx_analogue);
    printf("  Function returned: %d\n", result);
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */
int main(void) {
    printf("\n=== 1. Pointer Swap (global variables) ===\n");
    printf("  Before: zip1=%d  zip2=%d\n", zip1, zip2);
    call_swap();
    printf("  After : zip1=%d  zip2=%d\n", zip1, zip2);

    printf("\n=== 2. Recursive sfact (pointer to local on stack) ===\n");
    for (int n = 1; n <= 7; n++)
        printf("  sfact(%d) = %d\n", n, sfact(n));

    printf("\n=== 3. Stack frame layout (address arithmetic) ===\n");
    show_frame_layout();

    printf("\n=== 4. Caller-save register demo ===\n");
    caller_save_demo();

    printf("\n");
    return 0;
}
