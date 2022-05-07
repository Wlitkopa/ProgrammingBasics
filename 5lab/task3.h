#ifndef ENCRYPTION
#define ENCRYPTION

#include <stdbool.h>

enum Day {MON, TUE, WED, THU, FRI, SAT, SUN};

enum Action {DAY_EARLIER = 1, DAY_LATER = 2, TIME_EARLIER = 3, TIME_LATER = 4};

struct Term {
    int hour;
    int minute;
    int duration;
    enum Day day;
};

struct Lesson {
    char *subject;
    struct Term *term;
};

struct TimeLimits{
    int min_hour;
    int max_hour;
    int min_minutes;
    int max_minutes;
};

void TimeLimits__init(struct TimeLimits *timelimits, int minh, int maxh, int minm, int maxm);

struct TimeLimits* Set__TimeLimits(int minh, int maxh, int minm, int maxm);

void Term__init(struct Term* term, int hour, int minute, int duration, enum Day day);

struct Term* Term__create(int hour, int minute, int duration, enum Day day);

struct Lesson* Lesson__create(int hour, int minute, int duration, enum Day day, char *subject);

void Term__destroy(struct Term* term);

void Lesson__destroy(struct Lesson* lesson);

void Time__destroy(struct TimeLimits* timelimits);

char* Term__toString(struct Term* term);

bool Term__earlierThan(struct Term* term1, struct Term *term2);

bool Term__laterThan(struct Term* term1, struct Term *term2);

bool Term__equals(struct Term* term1, struct Term *term2);

struct Term* Term__endTerm(struct Term* term1, struct Term *term2, enum Day day);

char *Lesson__toString(struct Lesson* lesson);

void Lesson__earlierTime(struct Lesson* lesson, struct TimeLimits *timelimits, struct TimeLimits *timelimits2);

void Lesson__laterTime(struct Lesson* lesson, struct TimeLimits *timelimits, struct TimeLimits *timelimits2);

void Lesson__laterDay(struct Lesson* lesson);

void Lesson__earlierDay(struct Lesson* lesson);

#endif