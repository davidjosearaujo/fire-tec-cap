/*
    To compile: gcc -Wall -I/usr/include/libxml -o capparser capparser.c -lxml2
    To run: ./capparser <filename.xml>
*/
#include "capparser.h"

xmlDoc *document;

Data parseFromFile(char *fileName)
{
    xmlNode *root;
    document = xmlReadFile(fileName, NULL, 0);
    root = xmlDocGetRootElement(document);
    Data data;
    recursiveParser(&data, root);
}

// TODO - This function will only read the fields of interest, not the whole XML
void recursiveParser(Data* data, xmlNode *root)
{
    xmlNode *child;

    printf("Root is <%s>\n", root->name);

    for (child = root->children; child; child = child->next)
    {
        if (child->children != NULL)
            if (child->name == "parameter"){
                data->n_frequencies++;
            }
            recursiveParser(child);
        else
        {
            if (root->name == "parameter"){
                
            }
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