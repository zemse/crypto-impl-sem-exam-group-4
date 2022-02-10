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

typedef unsigned int uint31; // considering 31 bits as a limb

uint31 addU31(uint31 a, uint31 b);
uint31 subU31(uint31 a, uint31 b);
void printU31(uint31 a);
void printBinaryU31(uint31 a);

uint31 addU31(uint31 a, uint31 b)
{
    return (a + b) % (1 << 31);
}

uint31 subU31(uint31 a, uint31 b)
{
    return a - b % (1 << 31);
}

void printU31(uint31 a)
{
    printf("%u\n", a);
}

void printBinaryU31(uint31 a)
{
    // printf("%s: %u\n", str, );
    for (int i = 30; i >= 0; i--)
    {
        printf("%d", (a >> i) & 1);
    }
}
