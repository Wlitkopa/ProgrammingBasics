#ifndef ENCRYPTION
#define ENCRYPTION

#include <stdbool.h>

struct Term {
    int hour;
    int minute;
    int duration;
};

void Term__init(struct Term* term, int hour, int minute, int duration);

struct Term* Term__create(int hour, int minute, int duration);

void Term__destroy(struct Term* term);

char* Term__toString(struct Term* term);

bool Term__earlierThan(struct Term* term1, struct Term *term2);

bool Term__laterThan(struct Term* term1, struct Term *term2);

bool Term__equals(struct Term* term1, struct Term *term2);

struct Term* Term__endTerm(struct Term* term1, struct Term *term2);



#endif