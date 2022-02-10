/**
 * @file curve-point.c
 * @author Group 4, Cryptography Implementation, 3rd Sem, MTech CRS Batch 2020-22
 * @brief This library implements the curve point operations, which are used in the main.c file.
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
#include "field-element.c" // includes uint31.c

struct CurvePoint
{
    struct FieldElement x;
    struct FieldElement y;
};

// FUNCTION DECLARATIONS

/**
 * @brief Adds a and b then returns a new CurvePoint structure (Curve Point Addition).
 * 
 * @param A CurvePoint value to be added.
 * @param A CurvePoint value to be added.
 */
struct CurvePoint addCP(struct CurvePoint *A, struct CurvePoint *B);

/**
 * @brief Doubles the point a then returns a new CurvePoint structure (Curve Point Doubling).
 * 
 * @param a CurvePoint value to be doubled.
 */
struct CurvePoint doubleCP(struct CurvePoint *A);

/**
 * @brief Multiplies the point a with the field element n and then returns a new CurvePoint structure (Montgomery Ladder).
 * Note: n is a field element and should be less than the order of the generator.
 * 
 * @param a CurvePoint value to be multiplied.
 * @param b CurvePoint value to be multiplied.
 */
struct CurvePoint montgomeryLadder(struct CurvePoint *A, struct FieldElement *n);

// FUNCTION IMPLEMENTATIONS

struct CurvePoint addCP(struct CurvePoint *A, struct CurvePoint *B)
{
    // TODO implement
    struct CurvePoint result;
    return result;
}

struct CurvePoint doubleCP(struct CurvePoint *A)
{
    return addCP(A, A);
}

struct CurvePoint montgomeryLadder(struct CurvePoint *A, struct FieldElement *n)
{
    // TODO implement
    struct CurvePoint result;
    return result;
}