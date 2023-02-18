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
    data.frequency = NULL;
    data.audio = NULL;
    recursiveParser(&data, root);

    return data;
}

void recursiveParser(Data *data, xmlNode *root)
{
    xmlNode *child;
    for (child = root->children; child; child = child->next)
    {
        if (xmlStrEqual(child->name, (const xmlChar *)"parameter"))
        {
            Frequency *newFreq = (Frequency *)malloc(sizeof(Frequency));
            newFreq->name = (char *)xmlNodeGetContent(child->children);
            newFreq->frequency = (char *)xmlNodeGetContent(child->children->next);
            newFreq->next = NULL;

            Frequency *currentFreq = (Frequency *)data->frequency;
            if (currentFreq == NULL)
            {
                data->frequency = newFreq;
            }else{
                while (currentFreq->next != NULL)
                {
                    currentFreq = currentFreq->next;
                }
                currentFreq->next = newFreq;
            }
        }
        else if (xmlStrEqual(child->name, (const xmlChar *)"resource"))
        {
            Audio *newAudio = (Audio *)malloc(sizeof(Audio));
            newAudio->mimeType = (char *)xmlNodeGetContent(child->children->next);
            newAudio->bytes = (char *)xmlNodeGetContent(child->children->next->next);
            data->audio = newAudio;
        }
        else if (child->children != NULL)
        {
            recursiveParser(data, child);
        }
    }
}

/* 
int main(int argc, char **argv)
{
    char *filename;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
        return 1;
    }
    filename = argv[1];

    Data data = parseFromFile(filename);

    Frequency *temp = data.frequency;
    while (temp)
    {
        printf("Name: %s, Frequency: %s\n", temp->name, temp->frequency);
        temp = temp->next;
    }

    printf("mimeType: %s\nAudio: %s\n", data.audio->mimeType, data.audio->bytes);

    return 0;
}
*/