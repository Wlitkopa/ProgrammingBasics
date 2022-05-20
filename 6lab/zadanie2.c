#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


enum Day
{
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
};

struct Lesson
{
    char *className;
    enum Day day;
    int hour;
    int minute;
    int duration;
};

struct Node
{
    struct Lesson *lesson;
    struct Node *next;
};


void List__destroy(struct Node **list){


    int ind = 0;

    if (*list == NULL){
        printf("Lista nie istnieje (destroy)\n");
    }
    else {
        struct Node *current;
        while (*list != NULL){
            current = *list;
            *list = (*list)->next;
//            free(current->lesson->className);
//            free(current->lesson->className);
            free(current);
            printf("ind: %d", ind++);
        }
        printf("\n");
        *list = NULL;
//        free(list);
    }
}


void Lesson__init(struct Lesson* lesson, char* className, enum Day day, int hour, int minute, int duration) {
    lesson->hour = hour;
    lesson->minute = minute;
    lesson->duration = duration;
    lesson->className = malloc((strlen(className)*sizeof (*className)));
    strcpy(lesson->className, className);
//    lesson->className = className;
    lesson->day = day;
}

struct Lesson* Lesson__create(char* className, enum Day day, int hour, int minute, int duration){
    struct Lesson *lesson = malloc(sizeof (struct Lesson));
    Lesson__init(lesson, className, day, hour, minute, duration);
    return lesson;
}

void Node__init(struct Node* node, char* className, enum Day day, int hour, int minute, int duration) {
    node->lesson = Lesson__create(className, day, hour, minute, duration);
//    printf("Koniec Node__init\n");
//    printf("Uwaga, po Node__init:\nclassName: %s, day: %d, hour: %d, minute: %d, duration: %d\n", node->lesson->className, node->lesson->day, node->lesson->hour, node->lesson->minute, node->lesson->duration);
    node->next = NULL;

//    if (!node->next){
//        printf("NULL też dobrze działa\n");
//    }
}

struct Node* Node__create(char* className, enum Day day, int hour, int minute, int duration){
//    printf("Uwaga: className: %s, day: %d, hour: %d, minute: %d, duration: %d\n", className, day, hour, minute, duration);
    struct Node *node = malloc(sizeof (struct Node));
    Node__init(node, className, day, hour, minute, duration);
    return node;
}



void List__insert(struct Node **list, struct Lesson lesson, bool begin){
    struct Node *newnode;

    if (list != NULL){
        newnode = Node__create(lesson.className, lesson.day, lesson.hour,lesson.minute, lesson.duration);

        struct Node *current;
        struct Node *previous;

        if (begin){
            newnode->next = *(list);
            *(list) = newnode;
        }
        else{
            for (current = *list; current != NULL; current = current->next) {
                previous = current;
            }
            previous->next = newnode;
        }
    }
    else{
//        printf("Działam\n");
         *list = Node__create(lesson.className, lesson.day, lesson.hour,lesson.minute, lesson.duration);
//        list = newnode;
//        printf("\nW list__insert:\n\nPrzedmiot: %s\nDzień tygodnia: %u\nGodzina rozpoczęcia [Czas trwania]: %02d:%02d [%d]\n", (*list)->lesson->className, (*list)->lesson->day, (*list)->lesson->hour, (*list)->lesson->minute, (*list)->lesson->duration);

//        printf("Koniec list == NULL\n");
        if (list == NULL){
            printf("Coś nie działa\n");
        }
    }

//    newnode->lesson = malloc(sizeof (struct Lesson));
//    newnode->lesson = Lesson__create(lesson.className, lesson.day, lesson.hour,lesson.minute,lesson.duration);
//    newnode->next = NULL;


}


void List__remove(struct Node **list, struct Lesson lesson){
    struct Node *current;
    struct Node *previous;
    struct Node *temp;
    int index = 0;
    if ((*list) == NULL){
        printf("Lista nie istnieje\n");
        return;
    }
    for (current = *list; current != NULL; current = current->next) {

        if (!strcmp(current->lesson->className, lesson.className) && current->lesson->day == lesson.day && current->lesson->hour == lesson.hour && current->lesson->minute == lesson.minute && current->lesson->duration == lesson.duration && index == 0){
            temp = *list;
//            free(*list);
            *list = temp->next;
            free(temp);
            break;
        }
        else if (!strcmp(current->lesson->className, lesson.className) && current->lesson->day == lesson.day && current->lesson->hour == lesson.hour && current->lesson->minute == lesson.minute && current->lesson->duration == lesson.duration && current->next == NULL){
            free(current);
            previous->next = NULL;
            break;
        }
        else if (!strcmp(current->lesson->className, lesson.className) && current->lesson->day == lesson.day && current->lesson->hour == lesson.hour && current->lesson->minute == lesson.minute && current->lesson->duration == lesson.duration){
            previous->next = current->next;
            free(current);
            break;
        }

        previous = current;
        index += 1;
    }

}


void List__print(struct Node **list){

    struct Node *current;
    char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
    if (list == NULL){
        printf("Coś nie działa (print)\n");
    }

    for (current = *list; current != NULL; current = current->next)
    {
//        printf("DZIAŁA PRINT\n");
        printf("Przedmiot: %s\nDzień tygodnia: %s\nGodzina rozpoczęcia [Czas trwania]: %02d:%02d [%d]\n\n", current->lesson->className, dayNames[current->lesson->day], current->lesson->hour, current->lesson->minute, current->lesson->duration);
    }

//    for (int i = 0; i < 7; ++i) {
//        free(dayNames[i]);
//    }

}




int main(void) {


    struct Node *list = NULL;
    struct Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
    List__insert(&list, lesson, true);

    printf("=====================\n");
    List__print(&list); // Funkcja powinna wypisać:
    // Podstawy programowania, Środa 12:50 [90]
    printf("=====================\n");



    lesson.className = "Wychowanie fizyczne";
    lesson.day = MON;
    lesson.hour = 8;
    lesson.minute = 00;
    lesson.duration = 90;
    List__insert(&list, lesson, false);

    printf("=====================\n");
    List__print(&list); // Funkcja powinna wypisać:
    // Wychowanie fizyczne, Poniedziałek 8:00 [90]
    // Podstawy programowania, Środa 12:50 [90]
    printf("=====================\n");

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
//    List__insert(&list, lesson, true);

    printf("=====================\n");
    List__remove(&list, lesson);
    List__print(&list); // Funkcja powinna wypisać:
    // Podstawy programowania, Środa 12:50 [90]
    printf("=====================\n");


    List__destroy(&list); // Likwidacja listy
    List__destroy(&list); // Wypisuje: "Lista nie istnieje"

    return 0;
}













