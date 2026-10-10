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

**Call Chain Example**

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

**Revisting swap**

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

**%ebp (Extended Base Pointer)**
- The "Anchor": Also called the Frame Pointer, it stays at a fixed location for the duration of a function.
- Stack Frames: At the start of a function, the old %ebp is saved, and the current %esp is copied into %ebp to "lock" the base of the new frame.

**%esp (Extended Stack Pointer)** 
- The "Mover": Points to the very top (the current lowest memory address) of the stack.
- Dynamic: its value changes automatically whenever you use push, pop, call, or ret instructions
- Tracking: It keeps track of the next available space or the last item placed on the stack
- Volatility: Because it shifts constantly during calcaltions or nested calls, it is difficult to use for finding specific variables

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
```

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

**Creating & Initializing Pointer**

```c
int sfact(int x)
{
  int val = 1;
  s_helper(x, &val);
  return val;
}
```
- Variable `val` must be stored on stack
  - Because: Need to create pointer to it
- Computer pointer as `-4(%ebp)`
- Push on stack as second argument

- Initial part of `sfact`

```
_sfact:
  pushl %ebp            # Save %ebp
  movl  %esp, %ebp      # Set %ebp
  subl  $16, %esp       # Add 16 bytes
  movl  8(%ebp), %edx   # edx = x
  movl  $1, -4(%ebp)    # val = 1
```

![alt text](/images/s_fact.png)


- Calling `s_helper` from sfact


```
leal  -4(%ebp), %eax  # Compute &val
pushl %eax            # Push on stack
pushl %edx            # Push x
call s_helper         # call
movl -4(%ebp), %eax   # Return val
...                   # Finish
```

- Important points:
  - IA32 procedures are a combination of instructions and conventions
    - Conventions prevent functions from disrupting each other
  - Stach is the right data structure for procedure call / return
    - If P calls Q, the Q returns before P

![alt text](/images/procedure_summary.png)

- Recursion handled by normal calling conventions
  - Can safely store values in local stack frame and in callee-saved registers
  - Put function arguments at top of stack
  - Result returned in `%eax`

## x86-64 Procedure Calling Convetion

- **Doubling of registers makes us less dependent on stack**
  - Store argument in registers
  - Store temporary variables in registers
- What do we do if we have too many arguments or too many temporary variables?

**x86-64 64-bit Registers: Usage Conventions**

| 64-bit  | Usage Conventions |
|:-------:|:------:|
| %rax    | Return value   |
| %rbx    | Callee saved   |
| %rcx    | Argument#4   |
| %rdx    | Argument#3   |
| %rsi    | Argument#2   |
| %rdi    | Argument#1   |
| %rsp    | Stack Pointer   |
| %rbp    | Callee saved   |
| %r8     | Argument#5   |
| %r9     | Argument#6   |
| %r10    | Caller saved  |
| %r11    | Caller saved  |
| %r12    | Callee saved  |
| %r13    | Callee saved  |
| %r14    | Callee saved  |
| %r15    | Callee saved  |

![alt text](/images/x86_registers.png)


```asm
swap:
  // Set Up
  pushl %ebp
  movl %esp, %ebp
  pushl %ebx

  // Body
  movl 12(%ebp), %ecx
  movl 8(%ebp), %edx
  movl (%ecx), %eax
  movl (%edx), %ebx
  movl %eax, (%edx)
  movl %ebx, (%ecx)

  // Finish
  movl -4(%ebp), %ebx
  movl %ebp, %esp
  popl %ebp
  ret
```


```asm
swap (64-bit long ints):
  movq (%rdi), %rdx
  movq (%rsi), %rax
  movq %rax, (%rdi)
  movq %rdx,(%rsi)
  ret
```

- Arguments passed in registers
  - First (xp) in `%rdi`, second (yp) in `%rsi`
  - 64-bit pointers
- No stack operations required (except ret)
- Avoiding stack
  - Call hold all local information in registers

**X86-64 procedure call highlights**

- Arguments (up to first 6) in registers
  - Faster to get these values from registers than from stack in memory
- Local variables also in registers (if there is room)
- `callq` instruction stores 64-bit return address on stack
  - Address pushed onto stack, decrementing `%rsp` by 8
- No frame pointer
  - All references to stack frame made relative to `%rsp`; eliminates need to update `%ebp/%rbp`, which is now avaible for general-purpose use
- Functions can access memory up to 128 bytes beyond `%rps`: the "red zone"
  - Can store some temps on stack without altering `%rsp`
- Registers still designated "caller-saved" or "calle-saved"

**x86-64 Stack Frames**

- Often (idelly), x86-64 functions need no stack frame at all
  - Just a return address is pushed onto the stack when a function call is made
- A function does need a stack frame when it:
  - Has too many local variables to hold in registers
  - Has local variables that are arrays or structs
  - Uses the address-of operator (&) to compute the address of a local variable
  - Calls another function that takes more than six arguments
  - Needs to save the state of callee-save registers before modifying them

**x86-64 Procedure Summary**

- Heavy use of registers (faster than using stack in memory)
  - Parameter passing
  - More temporaries since more registers
- Minimal use of stack
  - Sometimes none
  - when needed, allocate/deallocate entire frame at once
  - No more frame pointer: address relative to stack pointer
- More room for compiler optimizations
  - Prefer to store data in registers rather than memory
  - Minimize modifications to stack pointer


[**Stack Pointer**](https://www.youtube.com/watch?v=n8_2y5E8N4Y)
- Stack: last in first out. reserved portion of memory for temporary storage of registers
- Stack pointer: contains an address pointing to the stack
  - Increment/ Decrement
  - Pre-increment / Pre-decrement
    - Post -> Stack Pointer (SP) points to the next location to store a register value