# include <stdio.h>
# include <stdlib.h>
# include <openssl/md5.h>
# include <string.h>
# include <unistd.h>

//  gcc -Wall ./zad3.c -o zad3 -lcrypto -lssl && ./zad3



char* str2md5(const char *str, int length, char* out) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
//    char *out = (char *) malloc(33);
//    char out[3]

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n * 2]), 16 * 2, "%02x", (unsigned int) digest[n]);
    }

    return out;
}

int main(int argc, char *argv[]){


    char *hash = "e00cf25ad42683b3df678c61f42c6bda";

    char alphnr[62] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                   'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                   '0','1','2','3','4','5','6','7','8','9'};

    printf("hash: %s\n", hash);

    char temp[7];

    for (int i = 0; i < 62; i++) {
//        printf("hash: %c\n", alphnr[i]);
        int num = fork();
        if (num < 0) {
            fprintf(stderr, "Fork Failed\n");
            return -1;
        }
        else if (num == 0) {
            char *out = (char *) malloc(33);
            for (int j = 0; j < 62; j++) {
                for (int k = 0; k < 62; k++) {
//                    printf("Jako dziecko jestem tutaj i maham\n");
                    for (int l = 0; l < 62; l++) {
                        for (int m = 0; m < 62; m++) {
                            for (int n = 0; n < 62; n++) {
//                                printf("Jako dziecko jestem tutaj i maham\n");
                                temp[0] = alphnr[i];
                                temp[1] = alphnr[j];
                                temp[2] = alphnr[k];
                                temp[3] = alphnr[l];
                                temp[4] = alphnr[m];
                                temp[5] = alphnr[n];
                                temp[6] = '\0';
                                //                            printf("temp: %s\n", temp);
                                //                            setenv("ShellVar", temp, 1) ;
                                //                            int retur = system("h=$(echo -n $ShellVar | md5sum | awk '{print($1)}'); if [ \"$h\" = \"$hash\" ]; then  echo \"Takie same: $ShellVar\n\"; exit 0; else exit 1; fi");
                                //                            int ret = system("exit -1");
                                //                            printf("Giga retur: %d\n", ret);

                                char *retur = str2md5(temp, strlen(temp), out);
                                //                            printf("Output: %s\n", retur);

                                if (strcmp(retur, hash) == 0) {
                                    printf("Scrackowano: %s\n", temp);
                                    printf("hash: %s\n", hash);
                                    printf("md5sum: %s\n", retur);

                                    //                                return 0;
                                }
                            }
                        }
                    }
//                    printf("Jestem tutaj (trzecia litera): %s\n", temp);

                }
                printf("Jestem tutaj (druga litera): %s\n", temp);
            }
            printf("Jako dziecko skończyłem sprawdzanie na: %s\n", temp);
            free(out);
            return 0;
        }
        else {
            printf("Stworzyłem dziecko sprawdzające literę: %c\n", alphnr[i]);
        }
    }
    return 0;
}

