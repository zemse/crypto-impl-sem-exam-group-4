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
 * @param a The value to be taken modulo. The function writes the result to this value.
 */
void modFE(struct FieldElement *a);

/**
 * @brief Adds a and b then returns a new FieldElement structure (Field Addition).
 * 
 * @param a FieldElement value to be added.
 * @param b FieldElement value to be added.
 */
struct FieldElement addFE(struct FieldElement *a, struct FieldElement *b);

/**
 * @brief Multiplies a and b then returns a new FieldElement structure (Field Multiplication).
 * 
 * @param a FieldElement value to be multiplied.
 * @param b FieldElement value to be multiplied.
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

/**
 * @brief Prints the two 31 bit limbs of the field element in base 10.
 * 
 * @param a The FieldElement value to be printed.
 */
void printFE(struct FieldElement *a);

/**
 * @brief Prints the two 31 bit limbs of the field element in base 2.
 * 
 * @param a The FieldElement value to be printed.
 */
void printBinaryFE(struct FieldElement *a);

// FUNCTION IMPLEMENTATIONS

struct FieldElement addFE(struct FieldElement *a, struct FieldElement *b)
{
    checkFE(a);
    checkFE(b);
    uint31 carry = 0;
    uint31 sum = addU31(a->lower, b->lower);
    if (sum < a->lower)
    {
        carry = 1;
    }
    struct FieldElement result;
    result.upper = addU31(a->upper, addU31(b->upper, carry));
    result.lower = sum;
    if (!ltFE(&result, &prime))
    {
        // here we need to subtract the prime
    }
    return result;
}

void subFE(struct FieldElement *a, struct FieldElement *b, struct FieldElement *result)
{
    uint31 upper = a->upper;
    uint31 lower = a->lower;
    uint31 carry = 0;
    uint31 diff = subU31(lower, b->lower);
    if (diff > lower)
    {
        carry = 1;
    }
    result->upper = subU31(upper, subU31(b->upper, carry));
    result->lower = diff;
}

void modFE(struct FieldElement *a)
{
    // TODO implement
}

int ltFE(struct FieldElement *a, struct FieldElement *b)
{
    if (a->upper < b->upper)
    {
        return 1;
    }
    else if (a->upper == b->upper)
    {
        if (a->lower < b->lower)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
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
    printf("\nFieldElement %s <%u,%u>", label, a->upper, a->lower);
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
    printBinaryFEWithLabel("hello", a);
}