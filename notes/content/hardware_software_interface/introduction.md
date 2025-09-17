+++
date = '2025-09-02T03:36:13+03:00'
draft = false
title = 'Introduction'
weight = 10
+++

# The Hardware/ Software Interface Class

[Course text book: Computer Systems](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/CSAPP_2016.pdf)

## The Big Theme

- The hardware/ software interface
- How does the h/w(0s and 1s, processor executing instructions) relate to the s/w (Go programs)?
- Computing is about abstractions (but we can't forget reality)
- What are the abstractions that we use?
- What do YOU need to know about them?
  - When do they break down and you have to peek under the hood?
  - What bugs can they cause and how do you find them?
- Become a better programmer and begin to understand the important concepts that have evolved in building ever more complex computer systems.

### Roadmap


1. Memory and data
2. Integers and floats
3. Machine code and C
4. x86 assembly
5. Procedures and stacks
6. Arrays and structs
7. Memory and caches
8. Processes
9. Virtual memory
10. Memory allocation
11. Java/Go vs C

### Little theme 1: Representation

- All digital systems represnt everything as 0s and 1s
  - The o and 1 are really two different voltage ranges in the electronics
- Everything includes:
  - Numbers - integers and floating point
  - Character - the building blocks of strings
  - Instructions - the directives to the CPU that make up a program
  - Pointers - addresses of data objects stored away in memory
- These encodings are stored throughout a computer system
  - In registers, caches, memories, disks, etc
- They all need addresses
  - A way to find them
  - Find a new place to put a new item
  - Reclain the place in memory when data no longer needed

## Little theme 2: Translation

- There is a big gap between how we thing about programs and data and the 0s and 1s of computers
- Need languages to describe what we mean
- Languages need to be translated one step at a time
  - Word-by-word
  - Phrase structure
  - Grammar
- We know Java/Go as a programming language
  - Have to work our way down to the 0s and 1s of computers
  - Try not to lose anything in translation!
  - We'll encounter Java/Go byte-code, C language, assembly language, and machine code (for the X86 family of CPU architectues)

## Little theme 3: Control flow

- How do computers orchestrate the many things they are doing - seemingly in parallel
- What do we have to keep track of when we call a method, and then another, and then another, and so on
- How do we know what to do upon "return"
- How do we run multiple user programs and let them share a sigle computer and memory
