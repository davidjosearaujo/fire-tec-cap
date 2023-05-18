/*
 Structure for holding CAP parameters
 
 Description: 
 
 by: Miguel Coelho and David Araújo
*/
#ifndef STRUCTURES
#define STRUCTURES

typedef struct Parameter
{
    String valueName;
    String value;
    struct Parameter *next;
} Parameter;

#endif
