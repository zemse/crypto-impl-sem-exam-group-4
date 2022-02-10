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
#include <math.h>

// custom libraries
#include "field-element.c" // includes uint31.c

struct CurvePoint
{
    struct FieldElement x;
    struct FieldElement y;
    struct FieldElement z;
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

    struct FieldElement a = subFE(&B->x, &B->z);
    struct FieldElement b = addFE(&A->x, &A->z);
    struct FieldElement c = addFE(&B->x, &B->z);
    struct FieldElement d = subFE(&A->x, &B->z);

    struct FieldElement e = mulFE(&a, &b); //(X2 − Z2 )(X1 + Z1)
    struct FieldElement f = mulFE(&c, &d); //(X2 + Z2 )(X1 − Z1)

    struct FieldElement g = addFE(&e, &f);
    struct FieldElement h = subFE(&e, &f);

    struct FieldElement i = mulFE(&g, &g);
    struct FieldElement j = mulFE(&h, &h);

    struct FieldElement X4 = mulFE(&A->z, &i);
    struct FieldElement Z4 = mulFE(&A->x, &j);

    struct FieldElement zero = {.upper = 0, .lower = 0};
    struct CurvePoint sum = {.x = X4, .y = zero, .z = Z4};

    return sum;
}

struct CurvePoint doubleCP(struct CurvePoint *A)
{
    struct FieldElement a = addFE(&A->x, &A->z);
    struct FieldElement b = subFE(&A->x, &A->z);

    a = mulFE(&a, &a);
    b = mulFE(&b, &b);

    struct FieldElement X5 = mulFE(&a, &b);

    struct FieldElement four = {.upper = 0, .lower = 4};
    struct FieldElement two = {.upper = 0, .lower = 2};
    struct FieldElement _A = {.upper = 371610194, .lower = 1493483305};
    struct FieldElement c = mulFE(&A->x, &A->z);
    struct FieldElement d = addFE(&_A, &two);

    //((A + 2)/4)(4X1Z1 )
    struct FieldElement e = mulFE(&d, &c);
    //((X1 − Z1)^2 + (A + 2)(X1Z1))
    e = addFE(&b, &e);

    struct FieldElement f = mulFE(&c, &four);
    struct FieldElement Z5 = mulFE(&f, &e);

    struct FieldElement zero = {.upper = 0, .lower = 0};
    struct CurvePoint pdouble = {.x = X5, .y = zero, .z = Z5};

    return pdouble;
}

struct CurvePoint montgomeryLadder(struct CurvePoint *A, struct FieldElement *n)
{
    // TODO implement

    struct CurvePoint R = *A;
    struct CurvePoint S = doubleCP(A);

    //Get MSB
    unsigned long temp = convertToUnsignedLong(n);
    int len = (int)(log(temp) / log(2)) + 1;
    int pos = (1 << (len - 1));

    struct CurvePoint temp1[2];
    struct CurvePoint temp2[2];

    for (int i = len; i > 0; i--)
    {
        temp1[0] = doubleCP(&S);
        temp1[1] = addCP(&S, &R);

        temp2[0] = addCP(&S, &R);
        temp2[1] = doubleCP(&R);

        S = temp1[(pos & temp) == pos];
        R = temp2[(pos & temp) == pos];
        /*
        if ((pos & temp) == pos)
        {
            //"1"
            S = addCP(&S, &R);
            R = doubleCP(&R);
        }
        else
        {
            //"0"
            R = addCP(&S, &R);
            S = doubleCP(&S);
        }
        */
        temp = temp << 1;
    }

    return R;
}