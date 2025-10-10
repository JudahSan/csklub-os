+++
date = '2025-09-24T03:36:13+03:00'
draft = false
title = 'Numbers'
weight = 30
+++

# Integer & Floating Point Numbers

- Representation of integers: unsigned and signed
- Unsigned and signed integers in C
- Arithmetic and shifting
- Sign extension

- Background: fractional binary numbers
- IEEE floating-point standard
- Floating-point operations and rounding
- Floating-point in C


### Encoding
- How about encoding a standard deck of playing cards?
- 52 cards in 4 suits
  - How do we encode suits, face cards?
- What operations do we want to make easy to implement?
  - Which is the higher value card?
  - Are they the same suit?

**Two possible representation**
- 52 cards - 52 bits with bit corresponding to card set to 1
  - "One-hot" encoding
  - Drawbacks:
    - Hard to campare values and suits
    - Large number of bits required
- 4 bits for suit, 13 bits for card value - 17 bits with two set to 1
  - "Two-hot" encoding
  - Easier to compare suits and values
    - Still am excessive number of bits

**Two better representations**
- Binary encoding of all 52 cards - only 6 bits needed
  - Fits in one byte
  - Smaller that one-hot or two-hot encoding, but how can we make value and suit comparisons easier?
- Binary encoding of suit (2 bit) and value (4 bits) separately
  - Also fits in one byte, and easy to do comparisons

### Some basic operations

- Checking if two cards have the same suit:

```c
#define SUIT_MASK 0X30
char array[5];  // represents a 5 card hand
char card1, card2; // two cards to compare
card1 = array[0];
card2 = array[1];

...
if sameSuitP(card1, card2) {
...

bool sameSuitP(char card1, char card2) {
    return (! (card1 & SUIT_MASK) ^ (card2 & SUIT_MASK));
    // return (card1 & SUIT_MASK) == (card2 & SUIT_MASK);
}
```

`SUIT_MASK = 0X30;` => `00110000`

- Comparing the values of two cards:

```c
#define VALUE_MASK 0X0F
#define SUIT_MASK 0X30
char array[5]; // represents a 5 card hand
char card1, card2;
card1 = array[0];
card2 = array[1];

...
if greaterValue(card1, card2) {
...

bool greaterValue(char card1, char card2) {
    return ((unsigned int) (card1 & VALUE_MASK) > (unsigned int) (card2 & VALUE_MASK));
}
```

`VALUE_MASK = 0X0F` => `00001111`

### Unsigned Integers

  - Unsigned value

  $$
  b_7b_6b_5b_4b_3b_2b_1b_0 
  = b_7 \cdot 2^7 + b_6 \cdot 2^6 + b_5 \cdot 2^5 + b_4 \cdot 2^4 + b_3 \cdot 2^3 + b_2 \cdot 2^2 + b_1 \cdot 2^1 + b_0 \cdot 2^0.
  $$

  **Formula:**

  $$1+2+4+8+...+2^(N-1) = 2^N - 1$$

- You add/subtract them using the normal "carry/borrow" rules, just in binary

63 + 8 = 71

|        | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|:--------|:---:|:---:|:---:|:---:|:---:|:---:|---:|
| carry  | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
| 63     | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
| + 8    | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
|--------|---|---|---|---|---|---|---|
| sum    | 1 | 0 | 0 | 0 | 1 | 1 | 1 |

$$
63 + 8 = 71
$$

$$
00111111 + 00001000 = 01000111
$$

$$
63_{10} = 111111_2, \quad 
8_{10}  = 001000_2, \quad 
71_{10} = 1000111_2
$$


### Signed Integers

- Simplified YT explanation: [video](https://www.youtube.com/watch?v=zMX2WERv74k)

- Let's do the natural thing for the positives
  - They correspond to the unsigned integers of the same value
    - Example (8 bits): 0x00 = 0, 0x01 = 1, ..., 0x7f = 127
- But, we need to let about half of them be negative
  - Use the high order bit to indicate *negative*: call it the "sign bit"
    - Call this a "sign-and-magnitude" representation
  - Examples (8 bits):
    - $$0x00 = 00000000_2$$ is non-negative, because the sign bit is 0
    - $$0x7F = 01111111_2$$ is non-negative
    - $$0x85 = 10000101_2$$ is negative
    - $$0x80 = 10000000_2$$ is negative

### Sign-and-Magnitude Negatives

- How should we represent **-1** in binary?
  - Sign-and-magnitude: $$10000001_2$$
    - Use the Most Significant Bit (MSB) for + or -, and the other bits to give magnitude
    - (Unfortunate side effect: there are two representations of 0!)
    - Another problem: math is cumbersome

![Number wheel](/images/number_wheel.png)

 - Example: 

$$4 - 3 != 4 + (-3)$$

$$4 = 0100$$
$$3 = 0011$$
$$-3=1011$$

$$4 - 3 = 0100 + 0011 = 0001 -> 1$$ 
$$4 + (-3) = 0100 + 1011 = 1111 -> 7$$  

### Two's Complement Negatives

- **How should we represent -1 in binary?**
  - Rather than a sign bit, let Most Significant Bit(MSB) have same value, but negative weight
    - W-bit word: Bits $0, 1, ..., W-2$ add $2^0, 2^1, ..., 2^(W-2)$ to value of integer when set, but bit W-1 adds $-2^(W-1)$ when set
    - e.g. unsigned 
  
        $$
        1010_{2} = 1 \cdot 2^{3} + 0 \cdot 2^{2} + 1 \cdot 2^{1} + 0 \cdot 2^{0} = 10_{10}
        $$

    - signed
  
        $$
        1010_{2} = -1 \cdot 2^{3} + 0 \cdot 2^{2} + 1 \cdot 2^{1} + 0 \cdot 2^{0} = -6_{10}
        $$

  - So -1 represented as $1111_2$; all negatives integers still has Most Significant Bit (MSB) = 1
  - Advantages of two's complement: only one zero, simple arithmetic
  - To get negative representation of any integer, take bitwise complement and then add one
    $$~x + 1 = -x$$

### Two's Complement Arithmetic

- The same addition procedure works for both unsigned and two's complement integer
  - Simplifies hardware: only one adder needed
  - Algorithm: simple addition, discard the highest carry bit
    - Called "modular" addition: result is sum module $2^W$
  - Examples

    **Example 1: 4 + 3**

    | Decimal | Binary |
    |---------|--------|
    | 4       | 0100   |
    | +3      | 0011   |
    | =7      | 0111   |

    ---

    **Example 2: 4 + (–3)**

    | Decimal | Binary |
    |---------|--------|
    | 4       | 0100   |
    | –3      | 1101   |
    | =1      | 10001  |
    |         | drop carry → 0001 |

    ---

    **Example 3: –4 + 3**

    | Decimal | Binary |
    |:---------|--------:|
    | –4      | 1100   |
    | +3      | 0011   |
    | =–1     | 1111   |
    |         | MSB = 1 → negative → invert(1111) = 0000 → +1 = 0001 → –1 |

### Two's Complement

- Why does it work?
  - Put another way: given the bit representation of a positive integer, we want the negative bit representation to always sum to 0 (ignoring the carry-out bit) when added to the positive representation.
  - This turns out to be the *bitwise complement plus one*
    - What should the 8-bit representation of -1 be? $00000001 + 11111111$ = 1 $00000000$ (we want whichever bit string gives the right result)

### Unsigned & Signed Numeric Values

|   X  |       Unsigned      |       Signed        |
|:------|:---------------------:|---------------------:|
|0000  |          0          |          0          |
|0001  |          1          |          1          |
|0010  |          2          |          2          |
|0011  |          3          |          3          |
|0100  |          4          |          4          |
|0101  |          5          |          5          |
|0110  |          6          |          6          |
|0111  |          7          |          7          |
|1000  |          8          |         -8          |
|1001  |          9          |         -7          |
|1010  |         10          |         -6          |
|1011  |         11          |         -5          |
|1100  |         12          |         -4          |
|1101  |         13          |         -3          |
|1110  |         14          |         -2          |
|1111  |         15          |         -1          |

- Both signed and unsigned integers have limits
  - If you compute a number that is too big, you wrap: 6 + 4 = ? 15U +2U = ?
  - If you compute a number that is too small, you wrap: -7 - 3 ? 0U - 2U = ?
- The CPU may be capable of "throwing an exception" for overflow on signed values
  - But it won't for unsigned
- C and Java just cruise along silently when overflow occurs...

### Visualizations

- Same W bits interpreted as signed vs unsigned:

![Same W bits visuals](/images/same_w_bits.png)

- Two's complement (signed) addition: x and y are W bits wide

![Two's complement (signed)](/images/2s_complement_visual.png)

### Values To Remember

- Unsigned Values
  - UMin = 0
    - 000...0
  - UMax = $2^W -1$
    - 111...1
- Two's Complement Values
  - TMin = $-2^{W-1}$
    - 100...0
  - TMax = $2^{W-1}-1$
    - 011...1
  - Negative 1
    - 111...1 0xFFFFFFFF (32 bits)

## Unsigned and signed Integers in C

|      | `8`   | `16`     | `32`          | `64`                      |
|:------|:-----:|:--------:|:-------------:|-------------------------:|
| `UMax` | _255_ | `65,535` | _4,294,967,295_ | `18,446,744,073,709,551,615` |
| `TMax` | _127_ | `32,767` | _2,147,483,647_ | `9,223,372,036,854,775,807`  |
| `TMin` | _-128_ | `-32,768` | _-2,147,483,648_ | `-9,223,372,036,854,775,808` |


**Observations**

- $|TMin| = TMax + 1$
  - Asymmetric range
- $UMax = 2 * TMax + 1$

**C Programming**

- `#include <limits.h>`
- Declares constants, e.g:
  - ULONG_MAX
  - LONG_MAX
  - LONG_MIN
- Values are platform specific
- See: `/usr/include/limits.h` on Linux

### Signed vs Unsigned in C

**Casting**

```c
int tx, ty;
unsigned ux, uy;
```

- Explicit casting between signed and unsigned:

```c
tx = (int) ux;
uy = (unsigned) ty;
```

- Implicit casting also occurs via assignments and function calls:

```c
tx = ux;
uy = ty;
```

 - The gcc flag -Wsign-conversion produces warning for implicit casts, but -Wall does not.
- How does casting beteen signed and unsigned work - what values are going to be produced?
  - Bits are unchanged, just interpreted differently.

### Casting Surprises

- Expression Evaluation
  - If you mix unsigned and signed in a single expression, then signed values implicitly cast to unsigned.
  - Including comparison operators `<.>,==,<=,>=`
  - Examples for W = 32: `TMIN = -2,147,483,648` `TMAX: 2,147,483,647`

| Constant_1     | Constant_2        | Relation | Evaluation |
|:----------------|:-------------------:|:----------:|------------:|
| 0              | 0U                | ==       | unsigned   |
| -1             | 0                 | <        | signed     |
| -1             | 0U                | >        | unsigned   |
| 2147483647     | -2147483648       | >        | signed     |
| 2147483647U    | -2147483648       | <        | unsigned   |
| -1             | -2                | >        | signed     |
| (unsigned)-1   | -2                | >        | unsigned   |
| 2147483647     | 2147483648U       | <        | unsigned   |
| 2147483647     | (int)2147483648U  | >        | unsigned   |

## Shifting and sign extension

### Shift Operations for unsigned integers

- **Left shift: x<<y**
  - Shift bit-vector x left by y positions
    - Throws away extra bits on left
    - Fill with 0s on right
- **Right shift: x>>y**
  - Shift bit-vector x right by y positions
    - Throw away extra bits on right
    - Fill with 0x on left

|   Operation   |     Binary   |Value (2^n)  |
|:--------------|:------------:|------------:|
|         x     | **00000110** |       6     |
|        <<3    | **00110000** |      48     |
|        <<2    | **00000001** |       1     |


|   Operation   |     Binary   |    Value    |
|:--------------|:------------:|------------:|
|         x     | **11110010** |     242     |
|       <<3     | **10010000** |144(overflow)|
|       <<2     | **00111100** |      60     |

### Shift Operations for signed integers

- **Left shift: x<<y**
  - Equivalent to mulitplying by $2^y$
  - (if resulting values fits, no 1s are lost)
- **Right shift: x>>y**
  - Logical shift (for unsigned values)
    - Fill with 0s on left
  - Arithmetic shift (for signed values)
    - Replicate most significant bit on left
    - Maintains sign of x
  - Equivalent to dividing by $2^y$
    - Correct rounding (towards 0) requires some care with signed numbers


| Operation       | Binary       | Value          |
|:----------------|:------------:|---------------:|
| x               | **01100010** |            98  |
| << 3            | **00010000** | 16 (784)       |
| Logical >> 2    | **00011000** |            24  |
| Arithmetic >> 2 | **00011000** |                |


| Operation       | Binary       | Value               |
|:----------------|:------------:|--------------------:|
| x               | **10100010** |              -94    |
| << 3            | **00010000** | 16 (underflow)      |
| Logical >> 2    | **00101000** | 40 (wrong)          |
| Arithmetic >> 2 | **11101000** |              -24    |



> NB: Undefined behaviour when y < 0 or y >= word_size

### Using Shifts and Masks

- **Extract the 2nd most significant byte of an integer**:
  - First shift, then mask: ( x>>16) & 0xFF

|  Operation   |               Binary               |
|:-------------|:----------------------------------:|
|     x        | 01100001 01100010 01100011 01100100|
|   x>>16      | 00000000 00000000 01100001 01100010|
|  0xFF(mask)  | 00000000 00000000 00000000 11111111|
|(x>>16) & OXFF| 00000000 00000000 00000000 01100010|

- **Extract the sign bit of a signed integer**:
  - $(x >> 31)$ & $1$ - need the **"& 1"** to clear out all other bits except LSB.
- **Conditionals as Boolean expressions** (assuming x is 0 or 1)
  - `if (x) a = y else a = z;` which is the same as `a = x ? y : z;`
  - Cab ve re-written (assuming arithmetic right shift) as: 
    - a = ((x<<31)>>31 & y + ((!x) << 31)>>31) & z

### Sign Extension

- **Task**:
  - Given w-bit signed integer x
  - Convert it to w+k-bit integer with same value
- **Rule**:
  - Make k copies of sign bit:
  - X = $x_{w-1},...,x_{w-1},x_{w-1},x_{w-2},...,x_0$

![Shifting and sign extension](/images/shift_sign_extension.png)


### Sign Extension Example

- Converting from smaller to larger integer data type
- C automatically performs sign extension

```c
short int x = 12345;
int ix = (int) x;
short int y = -12345;
int iy = (int) y;
```

|Variable| Decimal |    Hex  |Binary|
|:-------|:-------:|:-------:|:---------|
|   x    | 12345 | 30 39     |00110000 001101101
|  ix    | 12345 |00 00 30 39|00000000 00000000 00110000 01101101
|   y    |-12345 |CF C7      |11001111 11000111 
|  iy    |-12345 |FF FF CF C7|11111111 11111111 11001111 11000111

## Fractional Binary Numbers

- Representation
  - Bits to right of "binary point" represent fractional power of 2
  - Represents rational number

$$
\sum_{k=-j}^{i} b_k \times 2^k
$$

### Fractional Binary Numbers: Examples

|     Value      |           Representation        |
|:---------------|:-------------------------------:|
| 5 and 3/4      | $101.11_2$ |
|2 and 7/8       | $10.111_2$  |
|63/64        |  $0.111111_2|

- **Observations**
  - Divide by 2 by shifting right
  - Multiply by 2 by shifting left
  - Numbers of the form $0.111111...._2$ are just below $1.0$
    - $\frac{1}{2} + \frac{1}{4} + \frac{1}{8} + ... + \frac{1}{2^{i}}+...\rightarrow 1.0$
    - Shorthand notation for all 1 bits to the right of binary point: $1.0 - \epsilon$

### Representable Values

- **Limitations of fractional binary numbers**:
  - Can only exactly represent numbers that can be written as $x * 2^y$
  - Other rational numbers have repeating bit representations

|     Value      |           Repeating bit Representation        |
|:---------------|:------------------------------------------:|
|        1/3     |      $0.0101010101[01]..._2$    |
|     1/5        |    $0.001100110011[0011]..._2$  |
|      1/10      |    $0.0001100110011[0011]..._2$ |

### Fixed Point Representation
- We might try representing fractional binary numbers by picking a fixed place for an implied binary poing
  - 'fixed point binary numbers'
- Example using 8-bit fixed point numbers
  - the binary point between bits 2 and 3: $b_7b_6b_5b_4b_3[.]b_2b_1b_0$
  - the binary point between bits 4 and 5: $b_7b_6b_5[.]b_4b_3b_2b_1b_0$
- The position of the binary point affects the range and precision of the representation
  - range: difference between largest and smallest numbers possible
  - precision: smallest posible difference between any two numbers

### Fixed Point Pros and Cons
- Pros
  - It's simple. The same hardware that does integer arithmetic can do fixed point arithmetic
    - In fact, the programmer can use ints with an implicit fixed point
    - ints are just fixed point numbers with the binary point to the right of $b_0$
- Cons
  - There is no good way to pick where the fixed point should be
    - Sometimes you need range, sometimes you need precision - the more you have of one, the less of the other.