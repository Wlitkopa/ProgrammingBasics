#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>



// Struktura przekazywana do wątków (ver 1)
struct thStrc1 {
    int h;
    int w;
    int el; // Liczba elementów w tablicy, które musi obliczyć dany wątek
    float *time;
};


// Struktura przekazywana do wątków (ver 2)
struct thStrc2 {
    int h;
    int w;
    int thnum;
    int allth;
    int xs;
//    float *time;
    int **arr;
};


// Struktura przekazywana do wątków (ver 3)
struct thStrc3 {
    int h;
    int w;
    float *time;
    int *row_start[];
};


// Funkcja obliczająca nowe wartości array dla wersji 1
void *ver1(void *arg) {
    struct thStrc1 *newStruct = (struct thStrc1*)arg;

}


// Funkcja obliczająca nowe wartości array dla wersji 2
void *ver2(void *arg) {
    clock_t t;
    t = clock();
    struct thStrc2 *newStruct = (struct thStrc2*)arg;
    int w = newStruct->w;
    int xs = newStruct->xs;
    int thnum = newStruct->thnum;
    int allth = newStruct->allth;
    int **arr = newStruct->arr;

    int start = ((thnum - 1) * xs);
    int end;

    if (thnum == allth){
        end = w - 1;
    }
    else {
        end = (thnum * xs);
    }

    for (int i = 0; i < newStruct->h; ++i) {
        for (int j = start; j < end; ++j) {
            arr[i][j] = (255 - arr[i][j]);
        }
    }
    free(arg);
    t = clock() - t;
    int *thTime = (int*)malloc(sizeof (int));
    *thTime = t;
    return (void*)thTime;
}


// Funkcja obliczająca nowe wartości array dla wersji 2

void *ver3(void *arg) {
    struct thStrc3 *newStruct = (struct thStrc3*)arg;

}

// Funkcja print'ująca tablicę dwuwymiarową 'arr', gdzie 'h' to liczba wierszy a 'w' to liczba kolumn
void printArray(int h, int w, int** arr){

        printf("Zawartość tablicy arr:\n");
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j != (w - 1)){
                printf("%d ", arr[i][j]);
            }
            else {
                printf("%d\n", arr[i][j]);
            }
        }
    }
}


// Funkcja zapisująca do pliku wartości przechowywane w tablicy 'arr'
void writeToFile(int h, int w, int** arr, FILE* file){

    char towrite[10];

    printf("Zapisuję arr do pliku\n");
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
//            sprintf(towrite, "%d", arr[i][j]);
            if (j != (w - 1)){
//                fprintf(file, "%s ", towrite);
                fprintf(file, "%d ", arr[i][j]);

            }
            else {
//                fprintf(file, "%s\n", towrite);
                fprintf(file, "%d\n", arr[i][j]);

            }
        }
    }
}


int main(int argc, char **argv) {

    clock_t totalTime;
    totalTime = clock();

    if (argc != 5) {
        printf("Syntax:\n ./new2  [threads_amount]   [input_file]   [output_file]   [version_number]\n");
        return 1;
    }

    for (int i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    int threads = atoi(argv[1]);
    char *inpfile = argv[2];
    char *outfile = argv[3];
    int ver = atoi(argv[4]);

    if (threads < 0) {
        printf("Enter integral number as a number of threads\n");
        return 1;
    }
    if ((ver != 1) && (ver != 2)){
        printf("'ver' value can be only '1' or '2'\n");
    }

    printf("threads: %d\ninpfile: %s\noutfile: %s\nver: %d\n", threads, inpfile, outfile, ver);

    FILE *coins = fopen(inpfile, "r");
    FILE *negative = fopen(outfile, "wb+");

    char cur;
    int n = 0;
    int m = 0;
    int cnt = 0;
    int ind = 0;
    int len = 0;
    int mgrey = 0;
    char list[6];
    char list2[3];


//    Zapisuję długość pliku
    fseek(coins, 0, SEEK_END);
    len = ftell(coins);
    printf("len: %d\n", len);
    fseek(coins, 0, SEEK_SET);


//    Tworzę listę, do której potem zapiszę cyfry liczb m (height) oraz n (width)
    for (int i = 0; i < 6; ++i) {
        list[i] = 0;
    }
    for (int i = 0; i < 3; ++i) {
        list2[i] = 0;
    }

// Przepisuję pierwsze dwie linijki pliku, którego negatyw ma powstać, do pliku, który będzie negatywem
    fseek(coins, 0, SEEK_SET);
    while (cnt < 2) {
        cur = (char) fgetc(coins);
        printf("%c", cur);
        fprintf(negative, "%c", cur);
        if (cur == '\n') {
            cnt += 1;
        }
    }

// Zczytuję cyfry liczb m oraz n i zapisuję je do listy
    cur = 'z';
    while (cur != '\n') {
        cur = (char) fgetc(coins);
        printf("%c", cur);
        fprintf(negative, "%c", cur);

        if (!isspace((int) cur)) {
            list[ind] = cur;
            ind += 1;
        }
    }

// Przekształcam sekwencję cyfr w wartości liczbowe m oraz n
    ind = 2;
    for (int i = 0; i < 6; ++i) {
        if (i < 3) {
            n += (list[i] - '0') * pow(10, ind);
            ind -= 1;
        } else {
            if (ind == -1) {
                ind = 2;
            }
            m += (list[i] - '0') * pow(10, ind);
            ind -= 1;
        }
    }

    printf("m (height): %d\n", m);
    printf("n (wide): %d\n", n);

// Zapisuję ostatnią linijkę nagłówka do pliku będącego negatywem
    cur = 'z';
    ind = 0;
    while (cur != '\n') {
        cur = (char) fgetc(coins);
        printf("%c", cur);
        fprintf(negative, "%c", cur);

        if (!isspace((int) cur)) {
            list2[ind] = cur;
            ind += 1;
        }
    }

// Zapisuję informację o tym, jaka jest największa wartość szarości (grey value)
    ind = 2;
    for (int i = 0; i < 3; ++i) {
        mgrey += (list2[i] - '0') * pow(10, ind);
        ind--;
    }
    printf("mgrey: %d\n", mgrey);


// Wyznaczam przedziały wartości szarości w zaleźności od liczby wątków (ver 1)

    printf("mgrey: %d\nthreads: %d\n", mgrey, threads);
    int set = floor(((float)mgrey/(double)threads));
    printf("set: %d\n", set);


// Wyznaczam przedziały x-owe w zaleźności od liczby wątków (ver 2)

    printf("n: %d\nthreads: %d\n", n, threads);
    int xs = ceil(((float)n/(double)threads));
    printf("xs: %d\n", xs);


// Wyznaczam przedziały wierszy w zaleźności od liczby wątków (ver 3)

    printf("m: %d\nthreads: %d\n", m, threads);
    int rows = floor(((float)m/(double)threads));
    printf("rows: %d\n", rows);


//    Tworzę tablice dwuwymiarową, w której będą przechowywane wartości szarości opisane w pliku wejściowym
    int** arr;
    arr = (int**) malloc(m*sizeof(int*));

    for (int i = 0; i < m; ++i) {
        arr[i] = (int*)malloc(n*sizeof(int));
    }


//    Zapisuję wartości szarości do tablicy 'arr' oraz zeruję tablicę pomocniczą 'list2'
    int gv = 0;
    int s = 0;
    int t = 0;
    cnt = 0;
    for (int i = 0; i < 3; ++i) {
        list2[i] = 0;
    }

    while (len != ftell(coins)) {
        cur = 'z'; // przypisuję 'cur' dowolną wartość inną niż '\n', żeby mógł wejść w pętlę while poniżej
        while (cur != '\n') {
            cur = (char)fgetc(coins);
            if (!(isspace((int)cur)) && (cur != '\n')) {
                gv *= 10;
                gv += atoi(&cur);
            }
            else if ((cnt < 1) && (cur != '\n')) {
                cnt++;
            }

            else {
                arr[s][t] = gv;
                t++;
                if (t == n) {
                    s++;
                    t = 0;
                }
                gv = 0;
                cnt = 0;
            }
        }
    }


// Do odkomentowania: print'owanie lub zapisywanie do pliku
//    printArray(m, n, arr);
//    writeToFile(m, n, arr, negative);


// Tworzę wątki dla wersji pierwszej
// if (ver == 1) {
//    }



// Tworzę wątki dla wersji drugiej
    if (ver == 2){

        pthread_t th[threads];
        printf("if (ver == 2):\n");

        for (int i = 0; i < threads; ++i) {

            struct thStrc2 *curStr;
            curStr = (malloc(sizeof (struct thStrc2)));
            (*curStr).arr = arr;
            (*curStr).thnum = (i + 1);
            (*curStr).h = m;
            (*curStr).w = n;
            (*curStr).xs = xs;
            (*curStr).allth = threads;
//            printf("Przypisałem wartości\n");

            if (pthread_create(&th[i], NULL, ver2, (void*)curStr) != 0){
                perror("Failed to create thread\n");
            }
        }

        for (int i = 0; i < threads; ++i) {
            int *thTime;
            if (pthread_join(th[i], (void**)&thTime) != 0){
                perror("Failed to join thread\n");
            }
            double time_taken = ((double)*thTime)/CLOCKS_PER_SEC;
            printf("thread[%d] time: %f\n", (i + 1), time_taken);
            free(thTime);
        }
        writeToFile(m, n, arr, negative);
        totalTime = clock() - totalTime;
        double total_time_taken = ((double)totalTime)/CLOCKS_PER_SEC;
        printf("Całkowity czas poświęcony na wykonanie wersji 2: %f\n", total_time_taken);

    }


// Tworzę wątki dla wersji trzeciej
// if (ver == 3) {
//    }


// Zwalniam pamięć i zamykam pliki
    printf("Zwalniam pamięć\n");
    for (int i = 0; i < m; ++i) {
        free(arr[i]);
    }
    free(arr);

    fclose(coins);
    fclose(negative);
    return 0;

}
