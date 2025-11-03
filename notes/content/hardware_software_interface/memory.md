+++
date = '2025-10-10T03:36:13+03:00'
draft = false
title = 'Memory'
toc = true
weight = 40
+++

# Memory, Data, and Addressing

## Preliminaries

- Preliminaries
- Prepresenting information as bits and bytes
- Organizing and addressing data in memory
- Manipulating data in memory using C
- Boolean algebra and bit-level manipulations

### Hardware: Logical View

![H/W Logical View](/images/hw_logical_view.png)

### Hardware: Semi-Logical View
![H/W Semi Logical View](/images/semi_logical_view.jpg)

> Intel* P45 Express Chipset Block Diagram

### Hardware: Physical View

![HW Physical View](/images/hw_physical_view.png)

### CPU "Memory": Registers and Instruction Cache

![CPU Memory](/images/cpu_memory.png)

- There are a fixed number of registers in the CPU
  - Registers hold data
- There is an I-cache in the CPU that holds recently fetched instructions
  - If you execute a loop that fits in the cache, the CPU goes to memory for those instructions only once, then executes them out of its cache

### Performance: It's Not Just CPU Speed

- **Data and instructions reside in memory**
  - To execute an instruction, it must be fetched into the CPU
  - Next, the data on the which the instruction operates must be fetched from memory and brought to the CPU
- **CPU <--> Memory bandwidth can limit performance**
  - Improving performance 1: hardware improvements to increase memory bandwidth (e.g., DDR2 -> DDR3 -> DDR4)
  - Improving performance 2: move less data into/ out of the CPU 
    - Put some "memory" in the CPU chip itself (this is "cache" memory)

### Binary Representations

- Base 2 number representation
  - Represent $351_{10}$ as $0000000101011111_2$ or $101011111_2$
- Electronic implementation
  - Easy to store with bi-stable elements
  - Reliably transmitted on noisy and inaccurate wires

## Representing information as bits and bytes


### Encoding Byte Values

- Binary: $00000000_2$ -- $11111111_2$
  - Byte = 8 bits (binary digits)
  - Example: $00101011_2$ = $32 + 8 + 2 + 1$ = $43_{10}$
  - Example: $26_{10} = 16 + 8 + 2 = 00101010_2$
- Decimal: $0_{10}$ -- $255_{10}$
- Hexadecimal: $00_{16}$ -- $FF_{16}$
  - Groups of 4 binary digits
  - Byte = 2 hexadecimal (hex) or base 16 digits
  - Base-16 number representation
  - Use characters '0' to '9' and 'A' to 'F' to represent
  - Write $FA1D37B_{16}$ in C code as a 4-byte value: $0XFA1D37B$ or $0xfald37b$

|Hex|Decimal|Binary|
|---|-------|------|
|0  |0      |0000|
|1  |1      |0001|
|2  |2      |0010|
|3  |3      |0011|
|4  |4      |0100|
|5  |5      |0101|
|6  |6      |0110|
|7  |7      |0111|
|8  |8      |1000|
|9  |9      |1001|
|A  |10     |1010|
|B  |11     |1011|
|C  |12     |1100|
|D  |13     |1101|
|E  |14     |1110|
|F  |15     |1111|

How is memory organized?

### Byte-Oriented Memory Organization

- **Programs refer to addresses**
  - Conceptually, a very large array of bytes, each with an address (index)
  - Operating system provides an address space private to each "process"
    - Process = program being executed + its data + its "state"
    - Program can modify its own data, but not that of others
    - Clobbering code or "state" often leads to crashes
- **Compiler + run-time system control memory allocation**
  - Where different program objects should be stored
  - All allocation within a signle address space

### Machine Words

- **Machine has a "word size"**
  - Nominal size of integer-value data
    - Including addresses
  - Until recently, most machines used 32-bit (4 byte) words
    - Limits addresses to 4GB
    - Became too small for memory-intensive applications
  - Most current x86 systems use 64-bit (8-byte) word
    - Potential address space: $2_{64} \approx 1.8 X 10^{19}$ bytes (18 EB0 exabytes)
  - For backward-compatibility, many CPUs support different word sizes
    - Always a power-of-2 in the number of bytes: 1,2,4,8,...

### Word-Oriented Memory Organization

- **Address specify locations of bytes in memory**
  - Address of first byte in word
  - Address of successive words differ by 4 (32-bit) or 8 (64-bit)
  - Address of word 0, 1, ... 10?

|64-bit Words|32-bit Words|Bytes|Addr.|
|:-----------|:------------:|:-----:|-----:|
|           |    Addr   |______|0000|
|           |      =    |______|0001|
|    Addr   |    0000   |______|0002|
|      =    |           |______|0003|
|    0000   |    Addr   |______|0004|
|           |     =     |______|0005|
|           |   0004    |______|0006|
|           |           |______|0007|
|           |   Addr    |______|0008|
|           |      =    |______|0009|
|   Addr    |    0008   |______|0010|
|     =     |           |______|0011|
|   0008    |    Addr   |______|0012|
|           |     =     |______|0013|
|           |    0012   |______|0014|
|           |           |______|0015|

## Organizing and addressing data in memory

### Addresses and Pointers

| W| O| R| D|Address|
|:--|:--:|:--:|:--:|----:|
|--|--|--|--|$0000$|
|00|00|$01$|$5F$|$0004$|
|--|--|--|--|$0008$|
|--|--|--|--|$000C$|
|--|--|--|--|$0010$|
|00|00|$00$|$0C$|$0014$|
|--|--|--|--|$0018$|
|00|00|$00$|$04$|$001C$|
|--|--|--|--|$0020$|
|00|00|$00$|$1C$|$0024$|

- Address is a location in memory
- **Pointer is a data object that contains an address**
- Address 0004 stores value $351 (or 15F_{16})$
- Pointer to address 0004 stored in address 001C
- Pointer to a pointer in 0024
- Address 0014 stores the value 12


### Data Representations

- Sizes of objects (in bytes)

| Java Data Type | Go Data Type |   C Data Type   | Typical 32-bit | x86-64 |
| :------------- | :----------: | :-------------: | :------------: | :----: |
| `byte`         |    `byte`    |      `char`     |        1       |    1   |
| `short`        |    `int16`   |     `short`     |        2       |    2   |
| `int`          |     `int`    |      `int`      |        4       |    4   |
| `long`         |    `int64`   |   `long long`¹  |        8       |    8   |
| `float`        |   `float32`  |     `float`     |        4       |    4   |
| `double`       |   `float64`  |     `double`    |        8       |    8   |
| `boolean`      |    `bool`    |     `_Bool`     |        1       |    1   |
| `char`         |    `rune`    |     `char`²     |       2³       |   2³   |
| `void`         |       —      |      `void`     |        0       |    0   |
| (reference)    |       —      | `pointer` (`*`) |        4       |    8   |
| —              |       —      |     `long`⁴     |        4       |   8⁵   |
| —              |       —      |  `long double`  |        8       |   16⁶  |


- ⚙️ ABI Models — Explaining Size Differences

| ABI Model | `int` | `long` | `long long` | `pointer` | Typical OS/Platform           |
| :-------- | :---: | :----: | :---------: | :-------: | :---------------------------- |
| **ILP32** |   4   |    4   |      8      |     4     | 32-bit systems (x86, ARM32)   |
| **LP64**  |   4   |    8   |      8      |     8     | Linux/macOS x86-64, Unix-like |
| **LLP64** |   4   |    4   |      8      |     8     | Windows x86-64                |

1. **`long long` in C**

   * Always ≥ 64 bits. Often used for guaranteed 8-byte integers across all ABIs.

2. **`char` differences**

   * Java `char` → 16-bit UTF-16 code unit.
   * Go `rune` → 32-bit Unicode code point (`int32`).
   * C `char` → 8-bit byte, not Unicode-aware.

3. **`long` variation**

   * 32-bit in LLP64 (Windows 64-bit).
   * 64-bit in LP64 (Linux/macOS 64-bit).

4. **`long double`**

   * Varies: often 80-bit extended precision stored as 12 or 16 bytes.

### Byte Ordering

- **Endianness: big endian vs. little endian**
  - Two different converntions, used by different architectures
  - Origin: *Gulliver's Travels (see VS:APP2 textbook, section 2.1)*

### Byte Ordering Example
- **Big endian** (PowerPC, Sun, Internet)
  - Big end first: most-significant byte has lowest address
- **Little endian** (x86)
  - Little end first: least-significant byte has lowest address
- Example
  - Variable has 4-byte representation `0x01234567`
  - Address of variable is `0x100`

![byte ordering](/images/byte_ordering.png)

### Representing Integers

- `int A = 12345;`
- `int B = -12345;`
- `long int C = 12345;`

  - Decimal: `12345`
  - Binary: `0011 0000 0011 1001`
  - Hex: `3039` -> `0x00003039`

- **1A32,X86-64**
- IA32, x86-64 A: little endian
- Sun A: big endian

|(IA32, x86-64 A)| Sun A|
|:--|--:|
|39|00|
|30|00|
|00|30|
|00|39|


- IA32, x86-64 B: little endian
- Sun B(Two's complement representation for negative integers): big endian

|(IA32, x86-64 B)| Sun B|
|:--|--:|
|C7|FF|
|CF|FF|
|FF|CF|
|FF|C7|


|(IA32 C)|(x86-64 B)| Sun B|
|:-----|:------:|-----:|
|39|39|00|
|30|30|00|
|00|00|30|
|00|00|39|
|  |00|  |
|  |00|  |
|  |00|  |
|  |00|  |

## Manipulating data in memory using C

### Addresses and Pointers in C

```
& = 'address of value'
* = 'value at address' or 'dereference'
```

- **Variable declarations**
  - `int x, y;`
  - Finds two locations in memory in which to store 2 integers (1 word each)
- **Pointer declarations use `*`**
  - Declares a variable `ptr` that is a pointer to a data item that is an integer

```c
// ptr is a pointer to int
int *ptr;
``` 

```go
// golang
var ptr *int
```

- **Assignment to a pointer**
  - `ptr = &x;`
  - Assigns `ptr` to point to the address where x is stored

```c
int x = 10;
int *p = &x; // address of x
printf("%d\n", *p); // dereference pointer -> 10 
```

```go
// golang
x := 10
p := &x // address of x
fmt.Println(*p) // dereference pointer -> 10
```

### Addresses and Pointers in C

- To use the value pointed to by a pointer we use dereference (*)
  - Given a pointer, we can get the value it points to by using the * operator
  - `*ptr` is the value at the memory address given by the value of ptr
- Example
  - If `ptr = &x` then `y = *ptr + 1` is the same as `y = x + 1`
  - If `ptr = &y` then `y = *ptr + 1` is the same as `y = y + 1`
  - What is `*(&x)` equivalent to?
- We can do arithmetic on pointers
  - `ptr = ptr + 1;` // really adds 4: type of ptr is int*, and an it uses 4 bytes!
  - Changes the value of the pointer so that it now points to the next data item in memory (that may be y, or it may not - this is dangerous!)

NB: Unsafe situations in C
1. Dereferencing a null or dangling pointer

```c
int *p
*p = 5; // crash - p points nowhere
```

2. Writing past array boundaries
```c
int arr[3];
arr[5] = 69; // overwrites memory you don't own
```

3. Freeing the same memory twice or using freed memory
```c
free(p)
*p = 42; // undefined befaviour
```

4. Tricking the compiler into reinterpreting memory
```c
int x = 5;
float *f = (float*)&x;
```

### Assignment in C

- Left-hand-side = right-hand-side
  - LHS must evaluate to a memory location (a variable)
  - RHS must evaluate to a value (could be an address!)
- E.g., x at location `0x04`, y at `0x18`
  - x originally `0x0`, y originally `0x3CD02700`

| W| O| R| D|Address|
|:--|:--:|:--:|:--:|----:|
|--|--|--|--|$0000$|
|00|00|$00$|$00$|$0004$|
|--|--|--|--|$0008$|
|--|--|--|--|$000C$|
|--|--|--|--|$0010$|
|--|--|--|--|$0014$|
|$00$|$27$|$D0$|$3C$|$0018$|
|--|--|--|--|$001C$|
|--|--|--|--|$0020$|
|--|--|--|--|$0024$|

```c
int x, y;
x = y + 3; // get value at y, add 3, put it in x
```

| W| O| R| D|Address|
|:--|:--:|:--:|:--:|----:|
|--|--|--|--|$0000$|
|$03$|$27$|$D0$|$3C$|$0004$|
|--|--|--|--|$0008$|
|--|--|--|--|$000C$|
|--|--|--|--|$0010$|
|--|--|--|--|$0014$|
|$00$|$27$|$D0$|$3C$|$0018$|
|--|--|--|--|$001C$|
|--|--|--|--|$0020$|
|--|--|--|--|$0024$|

```c
int *x; // x is a pointer to int
int y;
x = &y + 3; // get address of y, add 12
// 0x0018 + 0x000C = 0x0024
```
- When you add an integer to a pointer, C automatically scalles the addition by the size of the pointed-to type

```c
*x = y; // value of y copied to location to which x points
```

- Store the value of y into the memory location the `x` points to.

| W| O| R| D|Address|
|:--|:--:|:--:|:--:|----:|
|--|--|--|--|$0000$|
|$03$|$27$|$D0$|$3C$|$0004$|
|--|--|--|--|$0008$|
|--|--|--|--|$000C$|
|--|--|--|--|$0010$|
|--|--|--|--|$0014$|
|$00$|$27$|$D0$|$3C$|$0018$|
|--|--|--|--|$001C$|
|--|--|--|--|$0020$|
|$00$|$27$|$D0$|$3C$|$0024$|

### Practical use cases where pointers make a difference:


1. **Pass by Reference (Modify Variables in Functions)**

By default, when you pass variables to a function in C or Go, you pass **copies** of them.
Pointers let you pass **references**, so the function can modify the *original* data.

- Example (C)

```c
void increment(int *n) {
    *n = *n + 1;   // modify the original value
}

int main() {
    int x = 5;
    increment(&x);
    printf("%d\n", x); // prints 6
}
```

Without pointers, you’d only modify a copy.

- Go Equivalent

```go
func increment(n *int) {
    *n = *n + 1
}

func main() {
    x := 5
    increment(&x)
    fmt.Println(x) // prints 6
}
```


2. **Working With Large Data (Avoid Copying)**

Pointers let you pass **large structures or arrays** to functions *without copying them*, improving performance and memory use.

- Example (C)

```c
struct BigStruct { int data[10000]; };

void process(struct BigStruct *b) {
    // operate on the actual data, not a copy
}
```

Go does the same with slices, maps, and structs — all of which use references under the hood.


3. **Dynamic Memory Management**

In C, pointers are used to **allocate memory at runtime** (on the heap).

```c
int *arr = malloc(10 * sizeof(int)); // allocate 10 ints
arr[0] = 5;
free(arr); // release memory
```

This is essential when the size of data isn’t known at compile time.

In Go, you don’t use `malloc()` directly — you use:

```go
p := new(int)
*p = 10
```

or composite literals like:

```go
user := &User{Name: "Doe"}
```


4. **Building Data Structures**

Pointers are **fundamental** to linked data structures:

* Linked Lists
* Trees
* Graphs
* Queues, Stacks, etc.

- Example (C)

```c
struct Node {
    int value;
    struct Node *next;
};
```

Each node **points** to another, forming a chain.

- Go Example

```go
type Node struct {
    Value int
    Next  *Node
}
```

5. **Sharing State Between Functions or Goroutines**

In Go, you often share access to the same data across goroutines using pointers and channels:

```go
type Counter struct { Value int }

func increment(c *Counter) {
    c.Value++
}

func main() {
    c := &Counter{}
    increment(c)
    fmt.Println(c.Value) // 1
}
```

6. **Interfacing With Hardware or Low-Level APIs**

Pointers are crucial when working **close to the system**:

* Device drivers
* Operating system kernels
* Embedded systems
* Interfacing with C libraries (via `unsafe` or cgo in Go)

- Example in C:

```c
int *deviceRegister = (int*)0x40021000;
*deviceRegister = 0x1; // write to hardware register
```

7. **Returning Multiple Values (Simulating Output Parameters)**

Before multiple return values existed, C functions used pointers to return extra results.

```c
void divide(int a, int b, int *quotient, int *remainder) {
    *quotient = a / b;
    *remainder = a % b;
}
```

8. **Optional or Nullable Values**

Pointers can represent “no value” (`NULL` or `nil`) cleanly — like an optional field.

- Go Example

```go
type User struct {
    Name    string
    Email   *string // optional
}
```


**Summary**

| Use Case          | Description                       | Language Example |
| :---------------- | :-------------------------------- | :--------------- |
| Pass by reference | Modify caller’s variables         | C, Go            |
| Avoid copying     | Handle large data efficiently     | C, Go            |
| Dynamic memory    | Allocate at runtime               | C                |
| Data structures   | Build linked lists, trees, graphs | C, Go            |
| Shared state      | Mutate common memory              | Go               |
| Hardware access   | Work with memory-mapped registers | C                |
| Multiple outputs  | Return extra values via pointers  | C                |
| Optional values   | Represent “no value” (`nil`)      | Go               |

## Arrays

- Arrays represent adjacent locations in memory storing the same type of data object
  - e.g. `int big_array[128];` allocates 512 adjacent bytes in memory starting at `0x00ff0000`
- Pointer arithmetic can be used for array indexing in C (if pointer and array have the same type!):

```c
int *array_ptr;
array_ptr = big_array;         // 0x00ff0000
array_ptr = &big_array[0];     // 0x00ff0000
array_ptr = &big_array[3];     // 0x00ff000c
array_ptr = &big_array[0] + 3; // 0x00ff000c(adds 3 * size of int)
array_ptr = big_array + 3;     // 0x00ff000c(adds 3 * size of int)
*array_ptr - *array_ptr + 1;   // 0x00ff000c(but big_array[3] is incremented)
array_ptr = &bit_array[130];   // 0x00ff0208(out of bounds, C doesn't check)
```
 - In general: `&big_array[i]` is the same as `(big_array + i)`, which implicitly computes: `&bigarray[0]+i*sizeof(bigarray[0]);`

### Representing strings

- A C-style string is represented by an array of bytes.
  - Elements are one-byte ASCII codes for each character.
  - A 0 byte marks the end of the array.

| Dec |   Char  | Dec | Char | Dec | Char | Dec | Char |
| :-: | :-----: | :-: | :--: | :-: | :--: | :-: | :--: |
|  32 | (space) |  33 |   !  |  34 |   "  |  35 |   #  |
|  36 |    $    |  37 |   %  |  38 |   &  |  39 |   '  |
|  40 |    (    |  41 |   )  |  42 |   *  |  43 |   +  |
|  44 |    ,    |  45 |   -  |  46 |   .  |  47 |   /  |
|  48 |    0    |  49 |   1  |  50 |   2  |  51 |   3  |
|  52 |    4    |  53 |   5  |  54 |   6  |  55 |   7  |
|  56 |    8    |  57 |   9  |  58 |   :  |  59 |   ;  |
|  60 |    <    |  61 |   =  |  62 |   >  |  63 |   ?  |
|  64 |    @    |  65 |   A  |  66 |   B  |  67 |   C  |
|  68 |    D    |  69 |   E  |  70 |   F  |  71 |   G  |
|  72 |    H    |  73 |   I  |  74 |   J  |  75 |   K  |
|  76 |    L    |  77 |   M  |  78 |   N  |  79 |   O  |
|  80 |    P    |  81 |   Q  |  82 |   R  |  83 |   S  |
|  84 |    T    |  85 |   U  |  86 |   V  |  87 |   W  |
|  88 |    X    |  89 |   Y  |  90 |   Z  |  91 |   [  |
|  92 |    \    |  93 |   ]  |  94 |   ^  |  95 |   _  |
|  96 |    `    |  97 |   a  |  98 |   b  |  99 |   c  |
| 100 |    d    | 101 |   e  | 102 |   f  | 103 |   g  |
| 104 |    h    | 105 |   i  | 106 |   j  | 107 |   k  |
| 108 |    l    | 109 |   m  | 110 |   n  | 111 |   o  |
| 112 |    p    | 113 |   q  | 114 |   r  | 115 |   s  |
| 116 |    t    | 117 |   u  | 118 |   v  | 119 |   w  |
| 120 |    x    | 121 |   y  | 122 |   z  | 123 |   {  |
| 124 |    |    | 125 |   }  | 126 |   ~  |     |      |


### Null-terminated strings

- For example, "Harry Potter" can be stored as a 13-byte array


|H | a | r | r | y | (space) | P | o | t | t | e | r | \0
|--|---|---|----|--|---------|---|---|---|---|---|---|---|
|72| `97`| 114| `114` |121 |`32`| 80| `111`| 116| `116`| 101| `114` | 0

- Why do we put a 0, or null zero, at the end of the string? Signifies the end of the string(length)
  - Note the special symbol: `string[12] = '\0';`

### Compatibility

`char S[6] = "12345";`

|(IA32, x86-64 S)| Sun S|
|:--|--:|
|31|31|
|32|32|
|33|33|
|34|34|
|35|35|
|00|00|

- Byte ordering (endianness) is not an issue for standard C strings (char arrays)
- Unicode characters - up to 4 bytes/character, depending on encoding (UTF-8, UTF-16, UTF-32)
- ASCII codes still work (just add leading 0 bits) but can support the many characters in all languages in the world
- Java and C have libraries for Unicode
  - Java commonly uses 2 bytes per character (UTF-16).
  - C can use wchar_t or specialized libraries for Unicode.
  - Go uses UTF-8 by default and provides the rune type for Unicode code points.


### Examining Data Representations

- Code to print byte representation of data
  - Any data type can be treated as a byte array by casting it to char

```c
void show_bytes(char *start, int len) {
  int i;
  for (i = 0; i < len; i++)
    printf("%p\t0x%.2x\n", start+i, *(start+i));
  printf("\n");
}
```

```c
void show_int (int x) {
  show_bytes ( (char *) &x, sizeof(int));
}
```

- `printf` directives
  - `%p` Print Pointer
  - `\t` Tab
  - `%x` Print value as hex
  - `\n` New line

Example:

```c
int a = 12345; // represented as 0x00003039
printf("int a = 12345;\n");
show_int(a); // show_bytes ( (byte *) &a, sizeof(int));
```

Reseult:

```c
int a = 12345;
0x7fff6f330dcc 0x39
0x7fff6f330dcd 0x30
0x7fff6f330dce 0x00
0x7fff6f330dcf 0x00
```

### Boolean algebra and bit-level manipulations

- Developed by George Boole in 19th Century
  - Algebraic representation of logic
    - Encode "True" as 1 and "False" as 0
  - AND: A&B = 1 when both A is 1 and B is 1
  - OR: A|B = 1 when either A is 1 or B is 1
  - XOR: A^B = 1 when either A is 1 or B is 1, but not both
  - NOT: ~A = 1 when A is 0 and vice-versa
  - DeMorgan's Law: ~(A|B) = ~A & ~B

| & | 0 | 1 |
|---|---|---|
| 0 | 0 | 0 |
| 1 | 0 | 1 |

| OR | 0 | 1 |
|----|---|---|
| 0 | 0 | 0 |
| 1 | 1 | 1 |

| ^ | 0 | 1 |
|---|---|---|
| 0 | 0 | 1 |
| 1 | 1 | 0 |

| NOT |   | 
|:---|---:|
| 0 | 1 |
| 1 | 0 |

### Manipulating Bits

- Boolean operators can be applied to bit vectors: operations are applied bitwise

0000 + 100101 = 1010101

| |0|1|1|0|1|0|0|1|
|-|-|-|-|-|-|-|-|-|
|&|0|1|0|1|0|1|0|1|
| |0|1|0|0|0|0|0|1|

<br>

| |0|1|1|0|1|0|0|1|
|-|-|-|-|-|-|-|-|-|
|OR|0|1|0|1|0|1|0|1|
| |0|1|1|1|1|1|0|1|
<br>

| |0|1|1|0|1|0|0|1|
|-|-|-|-|-|-|-|-|-|
|^|0|1|0|1|0|1|0|1|
| |0|0|1|1|1|1|0|0|
<br>


|~|0|1|0|1|0|1|0|1|
|-|-|-|-|-|-|-|-|-|
| |1|0|1|0|1|0|1|0|

### Bit-Level Operations in C
- Bitwise operations &, |, ^, ~(complement) are available in C
  - Apply to any "integral" data type
    - long, int, short, char
  - Argumants are treated as bit vectors
  - Operations applied bitwise
- Examples:

```c
char a, b, c;
a = (char) 0x41;   // 0x41 -> 01000001_2
b = ~a;            //         10111110_2 -> 0xBE
a = (char)0;       // 0x00 -> 00000000_2
b = ~a;            //         11111111_2 -> 0xFF
a = (char)0x69;    // 0x69 -> 01101001_2
b = (char)0x55;    // 0x55 -> 01010101_2
c = a & b;        //          01000001_2 -> 0x41
```

### Contrast: Logic Operations in C

- Logic operators in C: &&, ||, !
  - Behavior:
    - View 0 as "False"
    - Anything nonzero as "True"
    - Always return 0 or 1
    - Early termination (&& and ||)
- Examples (char data type)
  - !0x41             --> 0x00
  - !0x00             --> 0x01
  - 0x69 && 0x55      --> 0x01
  - 0x00 && 0x55      --> 0x00
  - 0x69 || 0x55      --> 0x01
  - p && *p++  (avoids null pointer access: null pointer = 0x000000000) short `for if (p) { *p++; }`

### Representing and Manupulating Sets

- Bit vectors can be used to represent sets
  - Width w bit vector represents subsets of {0,...,w-1}
  - $a_j=1 if j \forall A$ - each bit in the vector represents the absence (0) or presence (1) of an element in the set
  - 01101001 -> 7`65`4`3`21`0` -> {0,3,5,6}
  - 01010101 -> 7`6`5`4`3`2`1`0` -> {0,2,4,6}
- Operations
  - & Intersection           01000001 {0, 6}
  - | Union                  01111101 {0,2,3,4,5,6}
  - ^ Symmetric difference   00111100 {2,3,4,5}
  - ~ Complement             10101010 {1,3,5,7}
