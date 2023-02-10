/*
    To compile: gcc -Wall -I/usr/include/libxml -o capparser capparser.c -lxml2
    To run: ./capparser <filename.xml>
*/
#include "capparser.h"

xmlDoc *document;

int parseFromFile(char *fileName)
{
    xmlNode *root;
    document = xmlReadFile(fileName, NULL, 0);
    root = xmlDocGetRootElement(document);
    recursiveParser(root);
}

int parseFromString(char *stringXML)
{
    printf("Hi");
}

// TODO - This function will only read the fields of interest, not the whole XML
void recursiveParser(xmlNode *root)
{
    xmlNode *child;

    printf("Root is <%s>\n", root->name);

    for (child = root->children; child; child = child->next)
    {
        if (child->children != NULL)
            recursiveParser(child);
        else
        {
            printf("\t Child is <%s> and content: %s\n", child->name, xmlNodeGetContent(child));
        }
    }
}

int main(int argc, char **argv)
{
    xmlNode *root, *first_child, *node;
    char *filename;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
        return 1;
    }
    filename = argv[1];

    parseFromFile(filename);
    exit(0);

    document = xmlReadFile(filename, NULL, 0);
    root = xmlDocGetRootElement(document);
    fprintf(stdout, "Root is <%s> (%i) \n", root->name, root->type);
    first_child = root->children;
    for (node = first_child; node; node = node->next)
    {
        fprintf(stdout, "\t Child is <%s> and content: %s\n", node->name, xmlNodeGetContent(node));
    }
    fprintf(stdout, "...\n");
    return 0;
}