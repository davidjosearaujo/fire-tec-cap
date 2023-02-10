#ifndef CAPPARSER_H
#define CAPPARSER_H

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct Frequency
{
    char *name;
    float frequency;
} Frequency;

typedef struct Audio
{
    char *mimeType;
    char *bytes;
} Audio;

typedef struct Data
{
    Frequency *frequency;
    Audio *audio;
} Data;

Data parseFromFile(char *fileName);
// int parseFromString(char *stringXML);
void recursiveParser(xmlNode *root);

#endif