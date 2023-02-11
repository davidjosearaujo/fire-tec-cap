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
    Frequency *next;
} Frequency;

typedef struct Audio
{
    char *mimeType;
    char *bytes;
} Audio;

typedef struct Data
{
    int n_frequencies;
    void *frequency;
    void *audio;
} Data;

Data parseFromFile(char *fileName);
// int parseFromString(char *stringXML);
void recursiveParser(xmlNode *root);

#endif