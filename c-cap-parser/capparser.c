/*
    To compile: gcc -Wall -I/usr/include/libxml -o capparser capparser.c -lxml2
    To run: ./capparser <filename.xml>
*/
#include "capparser.h"

xmlDoc *document;

Alert parseFromFile(char *fileName)
{
    xmlNode *root;
    document = xmlReadFile(fileName, NULL, 0);
    root = xmlDocGetRootElement(document);
    void* alert;
    recursiveParser(&alert, root);
}

Alert parseFromString(char *stringXML)

    printf("Hi");
}

# TODO - Iterate with the parent Alert object
void* recursiveParser(void* parent, xmlNode *root)
{
    xmlNode *child;
    void* obj;

    switch (root->name)
    {
        case "alert":
            Alert a;
            obj = &a;
            break;
        
        case "info":
            Info a;
            obj = &a;
            break;

        case "eventcode":
            EventCode a;
            obj = &a;
            break;

        case "parameter":
            Parameter a;
            obj = &a;
            break;

        case "resource":
            Resource a;
            obj = &a;
            break;

        case "area":
            Area a;
            obj = &a;
            break;

        case "geocode":
            Geocode a;
            obj = &a;
            break;

        default:
            return;
    }

    for (child = root->children; child; child = child->next)
    {
        if (child->children != NULL)

            recursiveParser(child);

        else{
            
        }   
    }

    return obj;
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