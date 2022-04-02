#include <string.h>
#include <ctype.h>
#include "encryption.h"

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
    int ind = 0;
    char ch;
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
}
