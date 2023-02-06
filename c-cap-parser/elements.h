#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "enums.h"

typedef struct Area
{
    char *areaDesc;
    char *polygon;
    char *circle;
    char *geocode;
    char *altitude;
    char *ceiling;
} Area;

typedef struct Resource
{
    char *resourceDesc;
    char *mimeType;
    char *size;
    char *uri;
    char *derefUri;
    char *digest;
} Resource;

typedef struct Parameter
{
    char *valueName;
    char *value;
} Parameter;

typedef struct Info
{
    char *language;
    Category *category;
    char *event;
    ResponseType responseType;
    Urgency urgency;
    Severity severity;
    Certainty certainty;
    char *audience;
    char *eventCode;
    char *effective;
    char *onset;
    char *expires;
    char *senderName;
    char *headline;
    char *description;
    char *instruction;
    char *web;
    char *contact;
    Parameter *parameter;
    Resource *resource;
    Area *area;
} Info;

typedef struct Alert
{
    char *identifier;
    char *sender;
    char *sent;
    Status status;
    MsgType msgType;
    char *source;
    Scope scope;
    char *restriction;
    char *addresses;
    char *code;
    char *note;
    char *references;
    char *incidents;
    Info *info;
} Alert;

#endif