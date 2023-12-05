// Frees the automaton and all its components using a recursive function which
// travels through the entire automaton.
void free_automaton(automaton_t *automaton, state_t *current, 
                    state_t *prev_state) {
    if (prev_state->visited == FALSE) {
        prev_state -> visited = TRUE;
        free(prev_state->outputs);
        free(prev_state);
    }
    
    // For every single output, a recursion is called and the previous state
    // is freed along with its output list. Also, while iterating, the previous
    // iterator is also freed. This essentially frees up all the components
    // that make up the automaton.
    node_t *iterator = current->outputs->head;
    prev_state = current;
    while (iterator != NULL) {
        current = iterator->state;
        node_t *prev_iterator = iterator;
        iterator = iterator->next;
        free(prev_iterator);
        free_automaton(automaton, current, prev_state);
    }
}