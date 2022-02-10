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
        result = subFE(&result, &prime);
    }
    return result;
}

struct FieldElement subFE(struct FieldElement *a, struct FieldElement *b)
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