#ifndef CAPPARSER_H
#define CAPPARSER_H

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int parseFromFile(char *fileName);
int parseFromString(char *stringXML);
void recursiveParser(xmlNode *root);

#endif