#include <stdio.h>
#include <stdbool.h>

// Bitmasks for suit and value
#define SUIT_MASK 0X30
#define VALUE_MASK 0X0F

// Check if two cards have the same suit
bool sameSuitP(char card1, char card2)
{
    return (!(card1 & SUIT_MASK) ^ (card2 & SUIT_MASK));
    // return (card1 & SUIT_MASK) == (card2 & SUIT_MASK);
}

// Compare values of two cards
bool greaterValue(char card1, char card2)
{
    return ((unsigned int)(card1 & VALUE_MASK) > (unsigned int)(card2 & VALUE_MASK));
}

// Generated code
int main()
{
    // Example card values encoded as chars.
    // Let's assume the encoding is:
    // Bits 4-5 for suit (00=Clubs, 01=Diamonds, 10=Hearts, 11=Spades)
    // Bits 0-3 for value (1-13 for Ace-King)
    //
    // 0x27 is binary 0010 0111. Suit is 0010, Value is 0111 (7) --> Seven of Hearts
    // 0x22 is binary 0010 0010. Suit is 0010, Value is 0010 (2) --> Two of Hearts
    // 0x15 is binary 0001 0101. Suit is 0001, Value is 0101 (5) --> Five of Diamonds

    char card1 = 0x27; // Seven of ❤️
    char card2 = 0x22; // Two of ❤️
    char card3 = 0x15; // Five of ♦️
    char card4 = 0x37; // Seven of ♠️

    // Tests
    printf("Comparing 7️⃣ ❤️ and 2️⃣ ❤️:\n");
    if (sameSuitP(card1, card2))
    {
        printf(" Same suit. ✅\n");
    }
    else
    {
        printf(" Different suits. ❌\n");
    }
    if (greaterValue(card1, card2))
    {
        printf(" Greater value. ✅\n");
    }
    else
    {
        printf(" Not greater value. ❌\n");
    }

    printf("\nComparing 7️⃣ ❤️ and 5️⃣ ♦️:\n");
    if (sameSuitP(card1, card3))
    {
        printf(" Same suit. ✅\n");
    }
    else
    {
        printf(" Different suits. ❌\n");
    }
    if (greaterValue(card1, card3))
    {
        printf(" Greater value. ✅\n");
    }
    else
    {
        printf(" Not greater value. ❌\n");
    }

    printf("\nComparing 7️⃣ ❤️ and 7️⃣ ♠️ (Equal values):\n");
    if (sameSuitP(card1, card4))
    {
        printf("  Same suit. ❌\n");
    }
    else
    {
        printf("  Different suits. ✅\n");
    }
    if (greaterValue(card1, card4))
    {
        printf("  Greater value. ❌\n");
    }
    else
    {
        printf("  Not greater value. ✅\n");
    }

    printf("\nComparing 2️⃣ ❤️ and 5️⃣ ♦️:\n");
    if (sameSuitP(card2, card3))
    {
        printf("  Same suit. ❌\n");
    }
    else
    {
        printf("  Different suits. ✅\n");
    }
    if (greaterValue(card2, card3))
    {
        printf("  Greater value. ❌\n");
    }
    else
    {
        printf("  Not greater value. ✅\n");
    }

    return 0;
}