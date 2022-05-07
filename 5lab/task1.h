#ifndef ENCRYPTION
#define ENCRYPTION


enum Action* parse(int rozmiarTablicy, char *tablica[]);

enum Day Day__prevDay(enum Day day);

enum Day Day__nextDay(enum Day day);

char* Day__toString(enum Day day);


#endif