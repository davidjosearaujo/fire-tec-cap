#ifndef STRUCTURES
#define STRUCTURES

typedef struct Frequency
{
    String name;
    String frequency;
    struct Frequency *next;
} Frequency;

#endif
