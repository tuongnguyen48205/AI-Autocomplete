// Inserts a node at the end of the list. Modified version of insert_at_foot
// written by Alistair Moffat.
list_t *insert_at_tail(list_t *list, char str[], state_t *new_state) {
    node_t *new = (node_t *)malloc(sizeof(*new));
    assert(list != NULL && new != NULL);
    new->state = new_state;
    strcpy(new->str, str);
    new->next = NULL;
    if (list->tail == NULL) {
        // this is the first insertion into the list
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    return list;
}
