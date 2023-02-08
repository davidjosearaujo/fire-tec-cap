#ifndef CAPPARSER_H
#define CAPPARSER_H

#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "elements.h"
#include "enums.h"

Alert parseFromFile(char *fileName);
Alert parseFromString(char *stringXML);
void* recursiveParser(xmlNode *root);
char *deparse(Alert *alert);

#endif