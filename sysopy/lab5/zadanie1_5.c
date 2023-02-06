# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>

size_t copy(int in, int out, char *buffer, size_t taille);

size_t copy(int in, int out, char *buffer, size_t taille)
{
    ssize_t t;
    ssize_t bytes = 0;

    while ((t = read(in, buffer, taille)) > 0)
    {
        if (write(out, buffer, t) != t)
            return 0;
        bytes += t;
    }

    if (t < 0)
        perror("read");
    return bytes;
}

int main(int argc, char **argv)
{
    clock_t timing;
    int buffer_size = 1;
    char *buffer = malloc(sizeof(char) * buffer_size);

    if (!buffer)
    {
        perror("malloc ini");
        exit(1);
    }

    int fichier1 = open(argv[2], O_RDONLY);
    if (fichier1 < 0)
    {
        perror("base.txt");
        exit(1);
    }

    for (int i = 0; buffer_size <= 1048576; i++)
    {
        lseek(fichier1, 0L, SEEK_SET);
        char *temp_buffer = realloc(buffer, buffer_size * sizeof(char));
        if (!temp_buffer)
        {
            perror("malloc temp_buffer");
            exit(1);
        }
        int fichier2 = open("output.txt", O_WRONLY | O_CREAT, 0644);
        if (fichier2 < 0)
        {
            perror("open copy file");
            exit(1);
        }

        buffer = temp_buffer;

        timing = clock();
        size_t copied = copy(fichier1, fichier2, buffer, buffer_size);
        timing = clock() - timing;

        printf("%d, buffer size = %9d, time : %8ld (copied %zu bytes)\n",
               i, buffer_size, timing, copied);
        close(fichier2);
        remove("grosfichier_copie");

        buffer_size *= 2;
    }

    printf("\nKONIEC PIERWSZEJ CZĘŚCI\n");
    char c = getchar();

    buffer_size = atoi(argv[1]);
    lseek(fichier1, 0L, SEEK_SET);
    char *temp_buffer = realloc(buffer, buffer_size * sizeof(char));
    if (!temp_buffer)
    {
        perror("malloc temp_buffer");
        exit(1);
    }
    int fichier2 = open(argv[3], O_WRONLY | O_CREAT, 0644);
    if (fichier2 < 0)
    {
        perror("open copy file");
        exit(1);
    }

    buffer = temp_buffer;

    timing = clock();
    size_t copied = copy(fichier1, fichier2, buffer, buffer_size);
    timing = clock() - timing;

    printf("\n\n Mine buffer size = %9d, time : %8ld (copied %zu bytes)\n",
           buffer_size, timing, copied);
    close(fichier2);
    remove("grosfichier_copie");

    buffer_size *= 2;



    free(buffer);
    close(fichier1);

    return 0;
}