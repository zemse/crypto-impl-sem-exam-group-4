/**
 * @file uint31.c
 * @author Group 4, Cryptography Implementation, 3rd Sem, MTech CRS Batch 2020-22
 * @brief This is a library for abstracting to a 31 bit integer limb. This is used in the other files.
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

typedef unsigned long int uint31; // considering 31 bits as a limb

struct Uint31Result
{
    uint31 carry;
    uint31 value;
};

uint31 addU31(uint31 a, uint31 b);
uint31 subU31(uint31 a, uint31 b);
void printU31(uint31 a);
void printBinaryU31(uint31 a);

uint31 addU31(uint31 a, uint31 b)
{
    return (a + b) % (1 << 31);
}

struct Uint31Result addU31_2(uint31 a, uint31 b)
{
    struct Uint31Result result;
    result.value = (a + b) % (1 << 31);
    result.carry = (a + b) / (1 << 31);
    return result;
}

uint31 subU31(uint31 a, uint31 b)
{
    return a - b % (1 << 31);
}

struct Uint31Result subU31_2(uint31 a, uint31 b)
{
    struct Uint31Result result;
    result.value = a - b % (1 << 31);
    result.carry = (a - b) / (1 << 31) ? 1 : 0; // means subtraction overflow
    return result;
}

void printU31(uint31 a)
{
    printf("%lu\n", a);
}

void printBinaryU31(uint31 a)
{
    for (int i = 30; i >= 0; i--)
    {
        printf("%lu", (a >> i) & 1);
    }
}
