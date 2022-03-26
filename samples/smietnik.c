void fill(int size, int* matrix){

    srand48(time(NULL));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            matrix + (i*size + j)*sizeof(int) = (int) lrand48() % 10 + 1;

        }
    }

}

printf("%d \t", *(arrn[i] + j*sizeof (int)));

printf("\n");