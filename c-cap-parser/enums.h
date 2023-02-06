#ifndef ENUMS_H
#define ENUMS_H

typedef enum Status
{
    Actual,
    Exercise,
    System,
    Test,
    Draft
} Status;

typedef enum MsgType
{
    Alert_M,
    Update,
    Cancel,
    Ack,
    Error
} MsgType;

typedef enum Scope
{
    Public,
    Restricted,
    Private
} Scope;

typedef enum Category
{
    Geo,
    Met,
    Safety,
    Security,
    Rescue,
    Fire,
    Health,
    Env,
    Transport,
    Infra,
    CBRNE,
    Other
} Category;

typedef enum ResponseType
{
    Shelter,
    Evacuate,
    Prepare,
    Execute,
    Avoid,
    Monitor,
    Assess,
    AllClear,
    None
} ResponseType;

typedef enum Urgency
{
    Immediate,
    Expected,
    Future,
    Past,
    Unknown_U
} Urgency;

typedef enum Severity
{
    Extreme,
    Severe,
    Moderate,
    Minor,
    Unknown_S
} Severity;

typedef enum Certainty
{
    Observed,
    Likely,
    Possible,
    Unlikely,
    Unknown_C
} Certainty;

#endif