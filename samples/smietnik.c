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


int one_two_one(int *arr1, const int len1, int *arr2, const int len2, int *arr3) {

    int counter = 0;
    int ind1 = 0;
    int ind2 = 0;
    int ind3 = 0;
    int arr[len1 + len2];
    int larger = (int) fmax(len1, len2);

    for (int i = 0; i < larger; ++i) {


        if ((ind2 == (len2 - 1) && ind1 != len1) || (arr1[ind1] > arr2[ind2])) {
            if (counter != 0 && (arr1[ind1] > arr3[ind3 - 1])) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }
            if (counter == 0) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }

            ind1 += 1;
        }
        if ((ind1 == (len1 - 1) && ind2 != len2) || (arr1[ind1] < arr2[ind2])) {
            if (counter != 0 && (arr2[ind2] > arr3[ind3 - 1])) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
            if (counter == 0) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
            ind2 += 1;
        }

        /*
        else if((arr1[ind1] == arr2[ind2]) && counter == 0){
            arr3[ind3] = arr1[ind1];
            ind1 += 1;
            ind2 += 1;
            ind3 += 1;
            counter += 1;
        }
        */


    }
    return counter;
}

int one_two_two(int *arr1, const int len1, int *arr2, const int len2, int *arr3) {

    int counter = 0;
    int ind1 = 0;
    int ind2 = 0;
    int ind3 = 0;

    for (int i = 0; i < (len1 + len2); ++i) {

        if (ind1 == len1 && ind2 != len2) {
            if (arr2[ind2] > arr3[ind3]) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
            ind2 += 1;
        }
        else if ( ind2 != len2 && (arr1[ind1] > arr2[ind2])) {
            if (arr1[ind1] > arr3[ind3]) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }
            ind1 += 1;
        }
        else if ( ind2 != len2 && (arr1[ind1] == arr2[ind2])){
            if (arr1[ind1] > arr3[ind3]) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }
            ind1 += 1;
            ind2 += 1;
        }
        if (ind2 == len2 && ind1 != len1) {
            if (arr2[ind2] > arr3[ind3]) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
            ind2 += 1;
        }
        else if (ind1 != len1 && (arr1[ind1] < arr2[ind2])) {
            if (arr2[ind2] > arr3[ind3]) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
            }
            ind1 += 1;
        }
        else if ( ind2 != len2 && (arr1[ind1] == arr2[ind2])){
            if (arr1[ind1] > arr3[ind3]) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
            }
            ind1 += 1;
            ind2 += 1;
        }
        if (counter == 0) {
            if (arr2[ind2] > arr1[ind1]) {
                arr3[ind3] = arr2[ind2];
                ind3 += 1;
                counter += 1;
                ind2 += 1;
            }
            else if (arr2[ind2] < arr1[ind1]) {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                ind1 += 1;
            }
            else {
                arr3[ind3] = arr1[ind1];
                ind3 += 1;
                counter += 1;
                ind1 += 1;
            }
        }
    }



    return counter;
}
if(arr[i][j] == 1){
first[0][0] = i;
first[0][1] = j;
onecounter += 1;
}
if((onecounter == 1) && (arr[i][j] == 1)){
second[0][0] = i;
second[0][1] = j;
onecounter += 1;
}
if(onecounter == 2){
break;
}