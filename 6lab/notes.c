//    // Zmienna 'head' będzie przechowywać wskazanie na pierwszy element / węzeł listy
//    struct Node *head = NULL;
//
//    struct Node *node1 = (struct Node *) malloc(sizeof(struct Node));
//    if (node1 != NULL) // Jeżeli udało się utworzyć węzeł, to wypełnij go danymi
//    {
//        node1 = Node__create("Podstawy Programowania", WED, 12, 50, 90);
//    }
//
//    struct Node *node2 = (struct Node *) malloc(sizeof(struct Node));
//    if (node2 != NULL) {
//        node2 = Node__create("Wychowanie fizyczne", MON, 8, 00, 90);
//    }
//
//    struct Node *node3 = (struct Node *) malloc(sizeof(struct Node));
//    if (node3 != NULL) {
//        node3 = Node__create("Konsultacje", THU, 11, 05, 30);
//    }
//
//    // Wstawianie węzłów do listy — pierwszy sposób
//    if (node1 != NULL && node2 != NULL && node3 != NULL) {
//        head = node1;
//        node1->next = node2;
//        node2->next = node3;
//
//
//        char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
//        struct Node *current;
//
//
//        // Wypisanie informacji o wszystkich lekcjach zawartych na liście
//        for (current = head; current != NULL; current = current->next) {
//            printf("Przedmiot: %s\nDzień tygodnia: %s\nGodzina rozpoczęcia [Czas trwania]: %02d:%02d [%d]\n\n",
//                   current->lesson->className, dayNames[current->lesson->day], current->lesson->hour,
//                   current->lesson->minute, current->lesson->duration);
//        }
//        free(head->next->next); // Zwolnienie pamięci dla trzeciego elementu
//        free(head->next);       // Zwolnienie pamięci dla drugiego elementu
//        free(head);             // Zwolnienie pamięci dla pierwszego elementu
//
//
//    }





//    if (list == NULL){
//        printf("Działam\n");
//        list = Node__create(lesson.className, lesson.day, lesson.hour,lesson.minute, lesson.duration);
//        list = newnode;
//        printf("\nW list__insert:\n\nPrzedmiot: %s\nDzień tygodnia: %u\nGodzina rozpoczęcia [Czas trwania]: %02d:%02d [%d]\n\n", list->lesson->className, list->lesson->day, list->lesson->hour, list->lesson->minute, list->lesson->duration);
//
//        printf("Koniec list == NULL\n");
//        if (list == NULL){
//            printf("Coś nie działa\n");
//        }
//    }
//
//
//
//
//    if (list == NULL){
//        printf("Coś nie działa (main)\n");
//    }