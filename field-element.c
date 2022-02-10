/**
 * @file field-element.c
 * @author Group 4, Cryptography Implementation, 3rd Sem, MTech CRS Batch 2020-22
 * @brief This library implements the field element operations, which are used in the curve-point.c file.
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// standard libraries
#include <stdio.h>
#include <stdlib.h>

// custom libraries
#include "uint31.c"

struct FieldElement
{
    uint31 upper;
    uint31 lower;
};

struct FieldElement prime = {.upper = 1073741823, .lower = 2147483647}; // 2**61 - 1 = 1073741823 * 2**31 + 2147483647

// FUNCTION DECLARATIONS

/**
 * @brief Takes the modulo of the field element with the prime (Modular Reduction).
 * 
 * @param a The value to be taken modulo.
 */
struct FieldElement modFE(struct FieldElement *a);

/**
 * @brief Adds a and b then returns a new FieldElement structure (Field Addition).
 * 
 * @param a FieldElement value to be added.
 * @param b FieldElement value to be added.
 * @return result of addition struct FieldElement
 */
struct FieldElement addFE(struct FieldElement *a, struct FieldElement *b);

/**
 * @brief Subtracts a and b then returns a new FieldElement structure (Field Addition).
 * 
 * @param a FieldElement value to be subtracted from.
 * @param b FieldElement value to be subtracted.
 * @return result of subtraction struct FieldElement 
 */
struct FieldElement subFE(struct FieldElement *a, struct FieldElement *b);

/**
 * @brief Multiplies a and b then returns a new FieldElement structure (Field Multiplication).
 * 
 * @param a FieldElement value to be multiplied.
 * @param b FieldElement value to be multiplied.
 * @return result of struct FieldElement 
 */
struct FieldElement mulFE(struct FieldElement *a, struct FieldElement *b);

/**
 * @brief Sanity check for the field element. Throws an error if the field element is not valid.
 * 
 * @param a The FieldElement value to be checked.
 */
void checkFE(struct FieldElement *a);

/**
 * @brief Less than to comparison of two field elements.
 * 
 * @param a The value to be compared.
 * @param b The value to be compared.
 * @return int, 0 if false, 1 if true.
 */
int ltFE(struct FieldElement *a, struct FieldElement *b);

unsigned long convertToUnsignedLong(struct FieldElement *a);
struct FieldElement convertToFieldElement(unsigned long a);

/**
 * @brief Prints the two 31 bit limbs of the field element in base 10 or base 2.
 * 
 * @param a The FieldElement value to be printed.
 */
void printFE(struct FieldElement *a);
void printBinaryFE(struct FieldElement *a);
void printBinaryFEWithLabel(char label[], struct FieldElement *a);
void printFEWithLabel(char label[], struct FieldElement *a);

// FUNCTION IMPLEMENTATIONS

// subtracts a and b only if a > b
struct FieldElement _subFE(struct FieldElement *a, struct FieldElement *b)
{
    if (ltFE(a, b))
    {
        printf("Error in subFE: a is not less than b.\n");
        printBinaryFEWithLabel("a", a);
        printBinaryFEWithLabel("b", b);
        exit(EXIT_FAILURE);
    }
    struct Uint31Result resultLower = subU31_2(a->lower, b->lower);
    uint31 resultUpper = subU31(a->upper, b->upper); // does not overflow bcz the above if condition implies a >= b
    resultUpper = subU31(resultUpper, resultLower.carry);
    struct FieldElement result = {.upper = resultUpper, .lower = resultLower.value};
    return result;
}
struct FieldElement addFE(struct FieldElement *a, struct FieldElement *b)
{
    checkFE(a);
    checkFE(b);
    struct Uint31Result resultLower = addU31_2(a->lower, b->lower);
    uint31 resultUpper = addU31(a->upper, b->upper); // does not overflow bcz a and b are less than 2**30
    resultUpper = addU31(resultUpper, resultLower.carry);

    struct FieldElement result = {.upper = resultUpper, .lower = resultLower.value};

    if (!ltFE(&result, &prime))
    {
        // A < P and B < P
        // => A + B < 2P
        // => A + B - P < P
        result = _subFE(&result, &prime);
    }
    return result;
}

struct FieldElement subFE(struct FieldElement *a, struct FieldElement *b)
{
    struct FieldElement b_inv = _subFE(&prime, b);
    return addFE(a, &b_inv);
}

struct FieldElement mulFE(struct FieldElement *a, struct FieldElement *b)
{
    unsigned long a_ = convertToUnsignedLong(a);
    unsigned long b_ = convertToUnsignedLong(b);

    // splitting x and y into two halves
    unsigned long aH = (a_ >> 31) & 0x7FFFFFFF;
    unsigned long aL = a_ & 0x7FFFFFFF;
    unsigned long bH = (b_ >> 31) & 0x7FFFFFFF;
    unsigned long bL = b_ & 0x7FFFFFFF;

    // ab = h*(2**62) + m*(2**31) + l
    unsigned long h = aH * bH;
    unsigned long l = aL * bL;
    unsigned long m = (aH + aL) * (bH + bL) - h - l;

    h += ((m & 0x7FFFFFFF) << 31);
    l += (m >> 31) & 0x7FFFFFFF;

    return convertToFieldElement(l + 2 * h);
}

unsigned long convertToUnsignedLong(struct FieldElement *a)
{
    return (a->upper << 31) + (a->lower & 0x7FFFFFFF);
}

struct FieldElement convertToFieldElement(unsigned long a)
{
    unsigned long int prime_ = convertToUnsignedLong(&prime);
    a = a % prime_;

    struct FieldElement result;
    result.upper = a >> 31;
    result.lower = a & 0x7FFFFFFF;
    return result;
}

struct FieldElement modFE(struct FieldElement *a)
{
    return convertToFieldElement(convertToUnsignedLong(&prime));
}

int ltFE(struct FieldElement *a, struct FieldElement *b)
{
    if (a->upper != b->upper)
    {
        return a->upper < b->upper ? 1 : 0;
    }
    else
    {
        return a->lower < b->lower ? 1 : 0;
    }
}

void checkFE(struct FieldElement *a)
{
    if (!ltFE(a, &prime))
    {
        printf("Error in checkFE: val is greater than the prime. Following is the value:");
        printBinaryFE(a);
        printf("\nFollowing is the prime value:");
        printBinaryFE(&prime);
        printf("\n");
        exit(EXIT_FAILURE);
    }
}

void printFEWithLabel(char label[], struct FieldElement *a)
{
    printf("\nFieldElement %s <%lu,%lu>", label, a->upper, a->lower);
}

void printFE(struct FieldElement *a)
{
    printFEWithLabel("", a);
}

void printBinaryFEWithLabel(char label[], struct FieldElement *a)
{
    printf("FieldElement %s <", label);
    printBinaryU31(a->upper);
    printf(",");
    printBinaryU31(a->lower);
    printf(">\n");
}

void printBinaryFE(struct FieldElement *a)
{
    printBinaryFEWithLabel("", a);
}