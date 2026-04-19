+++
date = '2025-09-17T03:36:13+03:00'
draft = false
title = 'Architecture'
toc = true
weight = 10
+++

# Basics of architecture, machine programming

- [x] What is an ISA (Instruction Set Architecture)?
- [x] History of Intel processors and architectures
- [x] C, assembly, machine code
- [x] x86 basics: registers

## Translation Impacts Performance

![program lifetime](/images/prog_lifetime.png)
> Program lifetime illustration

- The time required to execute a program depends on:
  - The program.
  - The compiler: what set of assember instructions it translates the program into.
  - The instruction set architecture (ISA): what set of instructions it makes available to the compiler.
  - The hardware implementation: how much time it takes to execute an instruction.

### Instruction Set Architectures

- The ISA defines:
  - The system's state (e.g. registers, memory, program counter)
  - The instructions the CPU can execute
  - The effect that each of these instructions will have on the system state

### General ISA Design Decisions
1. Instructions
   - What instructions are available? What do they do?
   - How are they encoded? (eg 32bits, 64bits)
2. Registers
   - How many registers are there?
   - How wide are they? 
3. Memory(addressing modes)
   - How do you specify a memory location?

### x86
- **Processors that implement the x86 ISA completely dominate the server, desktop and laptop markets**
- **Evolutionary design**
  - Backwards compatibility up until 8086, introduced in 1978
  - Added more features as time goes on
- **Complex instruction set computer (CISC)**
  - Many different instructions with many different formats
    - But, only small subset encountered with Linux programs
  - (as opposed to Reduced Instruction Set Computers (RISC), which use simpler instructions)

### Intel x86 Evolution: Milestones

|Name   |Date   |Transistors|MHz|
|:----:|:-----:|:------------:|---:|
|8086   |1978 |29k         |5-10|

- First 16-bit processor. Basis for IBM PC & DOS
- 1MB address space

|Name|Date|Transistors|MHz|
|:----|:----:|:-----------:|---:|
|386|1985|275k        |16-33|

- First 32 bit processor, referred to as IA32
- Added "flat addressing"
- Capable of running Unix
- 32-bit Linux/gcc targets i386 by default

|Name|Date|Transistors|MHz|
|:----|:----:|:-----------:|---:|
|Pentium 4F|2005|230M |2800-3800|

- First 64-bit Intel x86 processor, referred to as x86-64

### Intel x86 Processors

Machine Evolution
  |----|----|
  |486|1989|
  |Pentium|1993|
  |Pentium/MMX|1997|
  |PentiumPro|1995|
  |Pentium III|1999|
  |Pentium 4|2001|
  |Core 2 Duo|2006|
  |Core i7|2008|

![Intel Core i7](/images/i7.png)

**Added Features**
 - Instructions to support multimedia operations
   - Parallel operations on 1, 2, and 4-byte data
 - Instructions to enable more efficient conditional operations
 - More cores!

**References for Intel processor specifications:**
  - [Automated Relational Knowledgebase](http://ark.intel.com/)
  - [Wikipedia](http://en.wikipedia.org/wiki/List_of_Intel_microprocessors)

### x86 Clones: Advanced Micro Devices(AMD)

**Historically**
  - AMD has followed just behind Intel
  - A little bit slower, a lot cheaper

**Then**
  - Recruited top circuit designers from Digital Equipment and other downward trending companies
  - Build Opteron: touch competitor to Pentium 4
  - Developed x86-64, their own extension of x86 to 64 bits

# Definitions

- [x] **Architecture**: (also instruction set architecture or ISA):
  - **The parts of a processor design that one needs to understand to write assembly code**
  - "What is directly visible to software"
- [x] **Microarchitecture**: Implementation of the architecture
- [x] Is cache size "architecture"? **No**
- [x] How about core frequency? **Microarchitecture**
- [x] And number of registers? **Yes, part of ISA**

### Assembly Programmer's View

![Assembly Programmer's View of the system](/images/assembly_view.png)

**Programmer-Visible State**
  - PC: Program counter
    - Address of next instruction
    - Called "EIP" in (IA32) or "RIP" in (x86-64)
  - Register file
    - Heavily used program data
  - Condition codes
    - Store status information about most recent arithmetic operation
    - Used for conditional branching
**Memory**
- Byte addressable array
- Code, user data, (some) OS data
- Includes stack used to support procedures

### Turning C into Object Code

- Code in files `p1.c` `p2.c`
- Compile with command: gcc -O1 p1.c p2.c -o p
  - Use basic optimizations (-O1)
  - Put resulting binary in file p

```goat
          +----------------------------+
  text    |  C program (p1.c p2.c)     |
          +----------------------------+
                     |
                     | Compiler (gcc -S)
                     v
          +----------------------------+
  text    | Asm program (p1.s p2.s)    |
          +----------------------------+
                     |
                     | Assembler (gcc or as)
                     v
          +----------------------------+       +----------------------+
 binary   | Object program (p1.o p2.o) |       | Static libraries (.a)|
          +----------------------------+       +----------------------+
                     |                                  |
                     | Linker (gcc or ld)               |
                     v                                  |
          +----------------------------+                |
 binary   | Executable program (a.out) |<---------------
          +----------------------------+       
                                               
```

### Compiling Into Assembly


**C Code**
```c
int sum(int x, int y)
{
  int t = x + y;
  return t;
}
```

**Generated IA32 Assembly**

```asm
sum:
  push1 %ebp
  mov1 %esp, %ebp
  mov1 12(%ebp), %eax
  addl 8(%ebp), %eax
  mov1 %ebp, %esp
  popl %ebp
  ret
```

**Obtain with command**

```
gcc -O1 -S code.c
```

Produces file code.s that holds the assembly code

### Three Basic Kinds of Assembly Instructions

1. **Perform arithmetic function on register or memory data**
2. **Transfer data between memory and register**
     - Load data from memory into register
     - Store register data into memory
3. **Transfer control**
     - Unconditional jumps to/from procedures
     - Conditional branches

### Assembly Characteristics: Data Types

- **Integer** data of 1, 2, 4 (IA32), or 8 (just in x86-64) bytes
  - Data values
  - Addresses (untyped pointers)
- **Floating point data of 4, 8, or 10 bytes**
- **What about "aggregate** types such as arrays or structs?
  - No aggregate types, just contiguously allocated bytes in memory.

### Object Code

Code for sum

```obj
0x401040 <sum>:
  0x55
  0x89
  0xe5
  0x8b
  0x45
  0x0c
  0x03
  0x45
  0x08
  0x89
  0xec
  0x5d
  0xc3
```

- Total of 13 bytes
- Each instruction 1,2, or 3 bytes
- Starts at address `0x401040`
- Not at all obvious where each instruction starts and ends

**Assembly**
- Translates `.s` to `.o`
- Binary encoding of each instruction
- Nearly-complete image of executable code
- Missing links between code in different files

**Linker**
- Resolves references between object files and (re)locates their data
- Combines with static run-time libraries 
  - E.g, code for  `malloc, printf`
- Some libraries are `dynamically linked` 
  - Linking occurs when program begins execution

### Machine Instruction Example

```c
int t = x + y;
```

```a
addl 8(%ebp), %eax
```

- Similar to expression: `x += y`
- More precisely:
  ```a
  int eax;
  int *ebp;
  eax += ebp[2]
  ```

- **C Code**: add two signed integers
- **Assembly**
  - Add two 4-byte integers
    - *Long* words in GCC speak
    - Same instruction whether signed or unsigned
  - Operands:
    - **x**: Register `%eax`
    - **y**: Memory `m[%ebp+8]`
    - **t**: Register `%eax`
      - Return function value in `%eax`
- **Object Code**

```a
ox401046:  03 45 08
```

  - 3-byte instruction
  - Stored at address `0x401046`

### Disassembling Object Code

- Disassembled

![Disassembled object code](/images/disassembled.png)

**Disassembler**

```
objdump -d p
```

- Useful tool for examining object code (`man 1 objdump`)
- Analyzes bit pattern of series of instructions (delineates instructions)
- Produces near-exact rendition of assembly code
- Can be run on either `p` (complete executable) or `p1.o` / `p2.o` file

### Alternative Disassembly

**Object**

```obj
0x401040 <sum>:
  0x55
  0x89
  0xe5
  0x8b
  0x45
  0x0c
  0x03
  0x45
  0x08
  0x89
  0xec
  0x5d
  0xc3
```

**Disassembled**

```a
0x401040 <sum>: push %ebp
0x401041 <sum+1>: mov %esp,%ebp
0x401043 <sum+3>: mov 0xc(%ebp),%eax
0x401046 <sum+6>: add 0x8(%ebp),%eax
0x401049 <sum+9>: mov %ebp,%esp
0x40104b <sum+11>: pop %ebp
0x40104c <sum+12>: ret
```

**Within gdb debugger**

```
gdb p
disassemble sum
(disassemble function)
x/13b sum
(examine the 13 bytes starting at sum)
```

### What can be disassembled?

- Anything that can be interpreted as executable code
- Disassembler examines bytes and reconstructs assembly source

## Registers

- A location in the CPU that stores a small amount of data, which can be accessed very quickly (once every clock cycle)
- Registers are at the heart of assembly programming
  - They are a precious commodity in all architectures, but especially x86

### Integer Registers (IA32)

- IA32 has 8 registers. 6 are general purpose and 2 special purpose(the last 2)

| Register | Size(32-bit) | Usage  (mostly obsolete)         |
|:--------:|:----:|:------------------------------|
| %eax     | 32   | Accumulator for operands and results data |
| %ecx     | 32   | Counter for string and loop operations |
| %edx     | 32   | I/O pointer                     |
| %ebx     | 32   | Pointer to data in the data segment |
| %esi     | 32   | Source pointer for string operations |
| %edi     | 32   | Destination pointer for string operations |
| %esp     | 32   | Stack pointer                   |
| %ebp     | 32   | Pointer to the base of the current stack frame|

### IA-32 General Purpose Registers (with 16-bit backward compatibility)

| 32-bit Register | 16-bit (BC) | High 8-bit | Low 8-bit |
|:---------------:|:-------------------------------:|:----------:|:---------:|
|      %eax       |      %ax                |    %ah     |   %al     |
|      %ebx       |      %bx                |    %bh     |   %bl     |
|      %ecx       |      %cx                |    %ch     |   %cl     |
|      %edx       |      %dx                |    %dh     |   %dl     |
|      %esi       |      %si                |            |           |
|      %edi       |      %di                |            |           |
|      %esp       |      %sp                |            |           |
|      %ebp       |      %bp                |            |           |


### x86-64 Integer Registers

### x86-64 Registers

| 64-bit  | 32-bit |
|:-------:|:------:|
| %rax    | %eax   |
| %rbx    | %ebx   |
| %rcx    | %ecx   |
| %rdx    | %edx   |
| %rsi    | %esi   |
| %rdi    | %edi   |
| %rsp    | %esp   |
| %rbp    | %ebp   |
| %r8     | %r8d   |
| %r9     | %r9d   |
| %r10    | %r10d  |
| %r11    | %r11d  |
| %r12    | %r12d  |
| %r13    | %r13d  |
| %r14    | %r14d  |
| %r15    | %r15d  |

- Extend existing registers, and add 8 new ones; all accessible as 8, 16, 32, 64

**Summary: Machine Programming**

- What is an ISA (Instruction Set Architecture)
  - Defines the system's state and instructions that are available to the software
- History of Intel processors and architectures
  - Evolutionary design leads to many quirks and artifacts
- C, assembly, machine code
  - Compiler must transform statements, expressions, procedures into low level instruction sequences
- x86 registers
  - Very limited number
  - Not all general-purpose
