
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void printtext(char *text){

    for (int i = 0; i < strlen(text); ++i) {
        printf("%c", *(text + i*sizeof (char)));
    }
    printf("\n\n");
}


int position(char c, char alphabet[]){

    int ctr = 0;
    char tempc = c;

    if(isupper(c)){
        tempc = (char) tolower(c);
    }
    for (int i = 0; i < strlen(alphabet); ++i) {
        if(tempc == alphabet[i]){
            break;
        }
        ctr ++;
    }
    return ctr;
}


void caesar(char *text, char *alphabet, char *ciphertext){

    int lenctr = 0;
    char ch;
    int ind = 0;
    while(*(text + ind*sizeof (char)) != '\0'){
        if((*(text + ind*sizeof (char)) != ' ')){
            while((*(text + ind*sizeof (char)) != ' ')&&(*(text + ind*sizeof (char)) != '\0')){
                lenctr ++;
                ind ++;
            }
            break;
        }
        ind ++;
    }

    for (int i = 0; i < strlen(text); ++i) {
        ch = *(text + i*sizeof (char));
        if((ch != ' ') && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))){
            *(ciphertext + i*sizeof (char)) = alphabet[((position(ch, alphabet)) + lenctr) % strlen(alphabet)];
        }
        else if(ch == ' ' ){
            *(ciphertext + i*sizeof (char)) = ch;
        }
    }
//    printf("Caesar function result: %s\n", ciphertext);
}


char* getEncryptedLine(char *alphabet){

    while(1){
        char ch;
        size_t length = 32;
        char *text = (char*)malloc(length*sizeof (char));
        int lenctr = 0;
        int ind = 0;
        char *ciphertext = (char*)malloc(strlen(text)*sizeof (char));

        puts("Napisz wiadomość, którą chcesz zaszyfrować: \n");
        length = getline(&text, &length, stdin);
        while(*(text + ind*sizeof (char)) != '\0'){
            if((*(text + ind*sizeof (char)) != ' ')){
                while((*(text + ind*sizeof (char)) != ' ')&&(*(text + ind*sizeof (char)) != '\0')){
                    lenctr ++;
                    ind ++;
                }
                break;
            }
            ind ++;
        }
        printf("%s \n", text);
        if((length == -1) || (strlen(text) == 1)){
            return NULL;
        }

//        caesar(text, alphabet, ciphertext);
        for (int i = 0; i < strlen(text); ++i) {
            ch = *(text + i * sizeof(char));
            if ((ch != ' ') && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
                *(ciphertext + i * sizeof(char)) = alphabet[((position(ch, alphabet)) + lenctr) % strlen(alphabet)];
//                printf("Position of %c: %d \n", ch, position(ch, alphabet));
//                printf("New element: %c\n", *(ciphertext + i));
            }
            else if (ch == ' ') {
                *(ciphertext + i * sizeof(char)) = ch;
            }
            else if (ch == EOF) {
                *(ciphertext + i * sizeof(char)) = '\0';
            }
        }
        printf("%s\n", ciphertext);
    }
}


int main(){

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char text[] = "ala ma kota i trzy chomiki";
    char *ciphertext = (char*)malloc(strlen(text)*sizeof (char));


    caesar(text, alphabet, ciphertext);
    printf("%s \n", ciphertext);

    printf("Result %s \n", getEncryptedLine(alphabet));

    free(ciphertext);

    return 0;
}
