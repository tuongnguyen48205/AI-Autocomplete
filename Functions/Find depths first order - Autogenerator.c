// Find the depths first order of the given automaton. uses a recursive 
// function call in order to do so.
void find_depths_first_order(automaton_t *automaton, int firstorder[],
                            state_t *current, int n) {
    
    // Place the current state into the first order array in the depths
    // first order
    firstorder[n] = current->id;
    n++;
    
    // Start by listing all the ASCII values for the outputs and sort it into
    // ascending order
    int ASCII_index[] = {INTZERO};
    int array_tracker = 0;
    node_t *iterator = current->outputs->head;
    while (iterator != NULL) { 
        ASCII_index[array_tracker] = (int)((iterator->str)[INTZERO]);
        array_tracker++;
        iterator = iterator->next;
    }
    sort_int_array(ASCII_index, array_tracker);

    // Now use a recursive call to go through the whole automaton and repeat
    // the process for every state
    for (int i = 0; i < array_tracker; i++) {
        iterator = current->outputs->head;
        if ((int)(iterator->str[INTZERO]) == ASCII_index[i]) {
            current = iterator->state;
            find_depths_first_order(automaton, firstorder, current, n);
        }
    } 
    return;
}
