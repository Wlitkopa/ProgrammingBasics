#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void generate(int type, int records, char *fpointer){
    FILE *file = fopen(fpointer, "wb");
    char c;
    int n;

    for (int i = 0; i < records; ++i) {
        if (type == 1){
            c = (char)((rand()%93) + 33);
            fwrite(&c, 1, 1, file);
        }
        else{
            n = (int)(rand() % 100);
            fwrite(&n, sizeof (int), 1, file);
        }
    }
    fclose(file);
}


void getval(FILE *file, int size, int pos, int *where){
    fseek(file, pos*size, 0);
    fread(where, size, 1, file);
}


void setval(FILE *file, int index, int value, int size){
    fseek(file, index*size, 0);
    fwrite(&value, size, 1, file);

}


void sort(int type, int records, char *fpointer){

    FILE *file = fopen(fpointer, "rb+");
    int *min = (int*) malloc(1*sizeof (int));
    int *check = (int*) malloc(1*sizeof (int));
    int temp;
    int size = type ? 1 : sizeof (int);


    for (int i = 0; i < records; ++i) {
        getval(file, size, i, min);
        for (int j = i + 1; j < records; ++j) {
            getval(file, size, j, check);
            if (*min > *check){
                setval(file, j, *min, size);
                setval(file, i, *check, size);
                temp = *min;
                *min = *check;
                *check = temp;
            }
        }
    }
    free(min);
    free(check);
    fclose(file);
}


void list(int type, int records, char *fpointer){

    FILE *file = fopen(fpointer, "rb");
    int size = type ? 1 : sizeof (int);
    int ch;

    for (int i = 0; i < records; ++i) {
        if (type == 1){
            fseek(file, i*size, 0);
            fread(&ch, size, 1, file);
            printf("%c", (char)ch);
        }
        else{
            fseek(file, i*size, 0);
            fread(&ch, size, 1, file);
            printf("%d\n", ch);
        }

    }
    printf("\n");
    fclose(file);
}


int main(int argc, char **argv){

    if (argc != 5){
        printf("Wprowadź dane w ten sposób: nazwa_pliku liczba_rekordów(elementów) typ_rekordu(i-int, c-char) wybór_operacji(g/s/l - generate/sort/list\n");
        return 1;
    }
    int type;
    switch (argv[3][0]){
        case 'i':
            type = 0;
            break;
        case 'c':
            type = 1;
            break;
        default:
            printf("Wybierz odpowiedni typ rekordu: i-int lub c-char\n");
            return 1;
    }
    int mode;
    int num = atoi(argv[2]);
    switch (argv[4][0]){
        case 'g':
            mode = 0;
            generate(type, num, argv[1]);
            break;
        case 's':
            mode = 1;
            sort(type, num, argv[1]);
            break;
        case 'l':
            mode = 2;
            list(type, num, argv[1]);
            break;
        default:
            printf("Wybierz tryb: g-generate l-list s-sort\n");
            return 1;
    }

}