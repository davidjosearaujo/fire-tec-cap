/*
    To compile: gcc -Wall -I/usr/include/libxml -o parser parser.c -lxml2
    To run: ./parser <filename.xml>
*/
#include "capparser.h"


xmlDoc* document;
xmlNode *root, *first_child, *node;

Alert parseFromFile(char* fileName){
    document = xmlReadFile(fileName, NULL, 0);
    root = xmlDocGetRootElement(document);
    recursiveParser(root);
}

Alert parseFromString(char* stringXML){
    printf("Hi");
}

Alert recursiveParser(xmlNode* root){
    printf("Root: %s\n", root->name);
    if (root->children != NULL){
        first_child = root->children;
        printf("First child: %s\n", first_child->name);
        for (node = first_child; node; node = node->next)
        {
            // FIX: Need another way to check if node has children, this causes a segfault
            if (node->children != NULL){
                printf("Tag: %s\n\n", node->name);
                recursiveParser(node);
            }
            else{
                printf("Tag: %s and content: %s", node->name, xmlNodeGetContent(node));
            }
            
        }
    }
}

int main(int argc, char **argv)
{
    xmlDoc *document;
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