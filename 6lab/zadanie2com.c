/*
   Po wykonaniu tych instrukcji zmienna 'node1' wskazuje na następującą strukturę danych:

                                  Struktura 'Node'
                  +--------------------------------------------------------+
                  |                          Struktura 'Lesson             |
                  |              +---------------------------------------+ |
                  |              | className -> "Podstawy Programowania" | |
                  |              | day:          WED                     | |
                  | lesson :     | hour:         12                      | |
                  |              | minute:       50                      | |
                  |              | duration:     90                      | |
                  |              +---------------------------------------+ |
     node1 -----> +--------------------------------------------------------+
                  | next:        NULL                                      |
                  +--------------------------------------------------------+
       */



// Zwalniane pamięci w kolejności od pierwszego do ostatniego elementu listy
/*
current = head;    // Ustawienie zmiennej 'current' na pierwszy element listy
head = head->next; // Ustawienie zmiennej 'head' na drugi element listy
free(current);     // Zwolnienie pamięci dla pierwszego elementu

current = head;    // Ustawienie zmiennej 'current' na drugi element listy
head = head->next; // Ustawienie zmiennej 'head' na trzeci element listy
free(current);     // Zwolnienie pamięci dla drugiego elementu

free(head); // Zwolnienie pamięci dla trzeciego elementu
*/



/*
Po wykonaniu tych instrukcji lista wygląda następująco:

                 +--------+         +--------+         +------------+
                 | lesson |         | lesson |         | lesson     |
           +-->  +--------+    +--> +--------+    +--> +------------+
           |     |        |    |    |        |    |    |            |
  head ----+     | next   |----+    | next   |----+    | next: NULL |
                 +--------+         +--------+         +------------+
                     ^                  ^                     ^
                     |                  |                     |
                   node1              node2                  node3
*/
}

// Wstawianie węzłów do listy — drugi sposób
if (node1 != NULL && node2 != NULL && node3 != NULL)
{
head = node1;
head->next = node2;
head->next->next = node3;
}

// Wstawianie węzłów do listy — trzeci sposób
struct Node *current;

if (node1 != NULL && node2 != NULL && node3 != NULL)
{
current = head = node1; // Ustawienie wskaźników (zmiennych) 'current' oraz 'head' na pierwszy węzęł listy
current->next = node2;  // Dopięcie drugiego elementu (węzła) do 'current', czyli de facto do pierwszego węzła listy

current = current->next; // Ustawienie zmiennej 'current' na drugi element listy
current->next = node3;   // Dopięcie trzeciego elementu do 'current', czyli do drugiego (węzła)

/*
Dopinanie, ewentualnych, kolejnych węzłów:

current = current->next; // Ustawienie zmiennej 'current' na trzeci element listy
current->next = node4;   // Dopięcie czwartego elementu do 'current', czyli do trzeciego

current = current->next; // Ustawienie zmiennej 'current' na czwart element listy
current->next = node5;   // Dopięcie piątego elementu do 'current', czyli do czwartego

...
*/
}