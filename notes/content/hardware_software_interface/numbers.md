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
|--------|---|---|---|---|---|---|---|
| carry  | 1 | 1 | 1 | 0 | 0 | 0 | 0 |
| 63     | 0 | 1 | 1 | 1 | 1 | 1 | 1 |
| + 8    | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
|--------|---|---|---|---|---|--a-|---|
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
    |---------|--------|
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
|------|---------------------|---------------------|
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