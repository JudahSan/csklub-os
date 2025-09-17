+++
date = '2025-09-17T03:36:13+03:00'
draft = false
title = 'Architecture'
weight = 20
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
