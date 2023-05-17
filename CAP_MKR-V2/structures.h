#ifndef STRUCTURES
#define STRUCTURES

typedef struct Parameter
{
    String valueName;
    String value;
    struct Parameter *next;
} Parameter;

#endif
