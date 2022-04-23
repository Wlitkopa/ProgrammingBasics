#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define MAX_LINE 128

int read_line()
{
    char line[MAX_LINE];
    int n;

    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int *nl, int *nw, int *nc)
{


    char *buffer = NULL;
//    buffer = (char*)malloc(1*sizeof (char));
//    printf("len1: %d\n", *len);

    size_t bufsize = 32;
    size_t chars = 0;
    int chars2 = 0;
    buffer = (char*)malloc(bufsize*sizeof(char));

    while (chars != -1) {
        chars = getline(&buffer, &bufsize, stdin);
        *nl += 1;
        *nc += (int)chars;


        int spaceflag = 0;

        for (int i = 1; i < (int)chars; i++) {
//            printf("%c", *(buffer+i));
//            printf("%d", (int)chars);
            if(*(buffer + i) == ' ' && *(buffer + i - 1) != ' '){
                *nw += 1;

                printf("i: %c   i-1: %c nw: %d \n", *(buffer + i),  *(buffer + i - 1), *nw);

            }

//            if((*buffer + i) == ' ' && spaceflag == 1){
//                *nw += 1;
//                spaceflag = 0;
//            }


        }
        *nw += 1;


    }
    *nl -= 1;
    free(buffer);

}


// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter)
{




}
/*******************************************************/
int main(void)
{
    int to_do;
    int nl = 0, nw = 0, nc = 0;
    int line_comment_counter, block_comment_counter;

    to_do = read_line();
    switch (to_do)
    {
        case 1: // wc()
            wc(&nl, &nw, &nc);
            printf("%d %d %d\n", nl, nw, nc);
            break;
        case 4:
            find_comments(&line_comment_counter, &block_comment_counter);
            printf("%d %d\n", block_comment_counter, line_comment_counter);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}
