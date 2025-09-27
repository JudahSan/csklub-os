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

