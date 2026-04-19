+++
date = '2026-04-12T03:36:13+03:00'
draft = false
title = 'Procedures'
toc = true
weight = 30
+++

# Procedures & Stacks

- Stacks in memory and stack operations
- The stack used to keep trach of procedure calls
- Return addresses and return values
- Stack-based languages
- The Linux stack frame
- Passing arguments on the stack
- Allocating local variables on the stack
- Register-saving conventions
- Procedures and stacks on x64 architecture

### Memory Layout

![alt text](/images/stack.png)

| Memory Permissions        | Segment / Region       | Management / Initialization                |
|--------------------------|------------------------|-------------------------------------------|
| Writable; not executable | Stack                  | Managed automatically (by compiler/runtime) |
| Writable; not executable | Dynamic Data (Heap)    | Managed by programmer                      |
| Writable; not executable | Static Data            | Initialized when process starts            |
| Read-only; not executable| Literals               | Initialized when process starts            |
| Read-only; executable    | Instructions (Code)    | Initialized when process starts            |

### IA32 Call Stack

- Region of memory managed with a stack "discipline"
- Grows towards lower addresses
- Customarily shown "upside-down"
- Register `%esp` contains lowest stack address = address of "top" element

![alt text](/images/ia32-callstack.png)

**IA32 Call Stack: Push**

- `pushl Src`
  - Fetch value from Src
  - Decrement `%esp` by 4 (why 4?) It's a push long(4 bytes of 32 bit word)
  - Store value at address given by `%esp`

**IA32 Call Stack: Pop**

- `popl Dest`
  - Load value from address `%esp`
  - Write value to Dest
  - Increment `%esp` by 4

## Procedure Call Overview

- Caller

```
...
<set up args>
call
<clean up args>
<find return val>
...
```

- Callee

```
<create local vars>
...
<set up return value>
<destroy local vars>
return
```

- `Callee` must know where to find args
- `Callee` must know where to find "return address"
- Caller must know where to find return val
- Caller and Callee run on same CPU -> use the sameregisters
  - Caller might need to save registers that Callee might use
  - Callee might need to save registers that Caller has used

- Caller

```
...
<save regs>
<set up args>
call
<clean up args>
<restore regs>
<find return val>
...
```

- Callee

```
<save regs>
<create local vars>
...
<set up return value>
<destroy local vars>
<restore regs>
return
```

- The convention of where to leave/find things is called the `procedure call linkage`
  - Details vary between systems
  - We will see the convention for `IA32/Linux` in detail

### Procedure Control Flow

- Use stack to support procedure call and return
- Procedure call: call `label`
  - Push return address on stack
  - Jump to `label`
- Return address:
  - Address of instruction after call
  - Example from disassembly:

```asm
804854e: e8 3d 06 00 00 call  8048b90 <main>
8048553: 50             push1 %eax
```

  - Return address = 0x8048553 

- Procedure return: `ret`
    - Pop return address from stack
    - Jump to address

**Procedure Call Example**

![alt text](/images/procedure-call.png)

**Procedure Return Example**

![alt text](/images/procedure-return.png)

**Return Values**

- By convention, values returned by procedures are placed in the `%eax` register
  - Choice of %eax is arbitrary, could have easily been a different register
- Caller must make sure to save that register before calling a callee that returns a value
  - Part of register-saving convention
- Callee placed return value (any type that can fit in 4 bytes - integer, float, pointer, etc.) into the %eax register
  - For return values greater than 4 bytes, best to return a pointer to them
- Upon return, caller finds the return value in the %eax register

## Stack Based Languages

- Languages that support recursion
  - e.g, C, Pascal, Go
  - Code must be re-entrant
    - Multiple simultaneous instantiations of single procedure
  - Need some place to store state of each instantiation
    - Arguments
    - Local variables
    - Return pointer
- Stack discipline
  - Stack for a given procedure needed for a limited time
    - Start from when it is called to when it returns
  - Callee always returns before caller does
- Stack allocated in frames
  - State for a single procedure instantiation

** Call Chain Example**

```c
yoo(...)
{
    ...
    who();
    ...
}
```

```c
who(...)
{
    ...
    amI();
    ...
    amI();
    ...
}
```

```c
amI(...)
{
    ...
    amI();
    ...
}
```

Example Call Chain
```
yoo
↓
who -> amI
↓
amI
↓
amI
```

- Procedure amI is recursive (calls itself)

![alt text](/images/stack-frames.png)

** Stack Frames **
- Stack frame = portion of stack used for a single procedure instantiation

- Contents
  - Local variables
  - Function arguments
  - Return information
  - Temporary space
- Management
  - Space allocated when procedure is created
    - "set-up" code
  - Space deallocated upon return
    - "Finish" code

![alt text](/images/stack-frames-example.png)

## The Linux Stack Frame

![alt text](/images/linux-stack-frame.png)

- Current Stack Frame ("Top" to Bottom)
  - "Argument build" area (parameters for function about to be called)
  - Local variables (if can't be kept in registers)
  - Saved register context (when reusing registers)
  - Old frame pointer (for caller)

- Caller's Stack Frame
  - Return address
    - Pushed by `call` instruction
    - Arguments for this call

** Revisting swap**

```c
int zip1 = 15213;
int zip2 = 98195;

void call_swap()
{
    swap(&zip1, &zip2);
}

void swap(int *xp, int *yp)
{
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}
```

Calling swap from call_swap

```asm
call_swap:
    ...
    push1 $zip2  # Global var
    push1 $zip2  # Global var
    call swap
    ...
```

```asm
swap:
    # Setup
    push1 %ebp
    movl %esp, %ebp
    pushl %ebx

    # Body
    movl 12(%ebp), %ecx
    movl 8(%ebp), %edx
    movl (%ecx), %eax
    movl (%edx), %ebx
    movl %eax, (%edx)
    movl %ebx, (%ecx)

    # Finish
    movl -4(%ebp), %ebx
    movl %ebp, %esp
    popl %ebp
    ret
```

## Allocating local variables on the stack

### Register Saving Conventions

- When procedure `yoo` calles who:
  - yoo is the caller
  - who is the callee
- Can a register be used for temporary storage?

```asm
yoo:
    ...
    movl $12345, %edx
    call who
    addl%edx, %eax
    ...
    ret
```

```asm
who:
    ...
    movl 8(%ebp), %edx
    addl $98195, %edx
    ...
    ret
```

- Contents of register %edx overwritten by who
- Conventions
  - "**Caller Save**"
    - Caller saves temporary values in its frame before calling
  - "**Callee Save**"
    - Callee saves temporary values in its frame before using

**IA32/Linux Register Usage**

```asm
# Caller-save Temporaries
%eax
%edx
%ecx

# Callee-save Temporaries
%ebx
%esi
%edi

# Special
%esp
%ebp
```

- %eax, %edx, $ecx
  - Caller saves prior to call if values are used later
- %eax
  - also used to return integer value
- %ebx, %esi, %edi
  - Callee saves if wants to used them
- %esp, %ebp
  - special form of calle save- restored to original values upon exit from procedure

**Example: Pointer to Local Variables**

- Recursive Procedure
```c
void s_helper (int x, int *accum)
{
    if (x <= 1)
        return;
    else {
        int z = *accum * x;
        *accum = z;
        s_helper (x-1, accum);
    }
}

- Top-Level Call

```c
int sfact(int x)
{
    int val = 1;
    s_helper(x, &val);
    return val;
}
```

- Pass pointer to update location