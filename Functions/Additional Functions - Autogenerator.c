// Alistair Moffat, PPSAA, Chapter 10, December 2012
// (c) University of Melbourne
list_t *make_empty_list(void) {
    list_t *list = (list_t *) malloc(sizeof(*list));
    assert(list != NULL);
    list->head = list->tail = NULL;
    return list;
}

/* sorts n elements of array A in increasing order (2, 3, 4, 5)
 * using insertion sort (insertionsort.c, Figure 7.4 PPSAA) */
// By Alistair Moffat
void sort_int_array(int A[], int n) {
    /* assume that A[0] to A[n-1] have valid values */

    for (int i = 1; i < n; i++) {
        /* swap A[i] left into correct position (increasing order). */
        for (int j = i - 1; j >= 0 && A[j] > A[j + 1]; j--) {
            /* not there yet */
            int_swap(&A[j], &A[j + 1]);
        }
    }
}

/* exchange the values of the two variables indicated
 * by the arguments (insertionsort.c, Figure 7.4 PPSAA) */
// By Alistair Moffat
void int_swap(int *p1, int *p2) {
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
