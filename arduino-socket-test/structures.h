#ifndef STRUCTURES
#define STRUCTURES

typedef struct Parameter
{
    String valueName;
    String value;
    struct Parameter *next;
} Parameter;

typedef struct Audio
{
    String value;
    struct Audio *next;
} Audio;

#endif
