// Makes a new state in the automaton. Gives the state its respective ID,
// an output list, and sets its frequency to 1 since it is new.
state_t *make_new_state(automaton_t *automaton) {
    state_t *new = (state_t*)malloc(sizeof(*new));
    (automaton->nid)++;
    new->id = automaton->nid;
    new->freq = INTONE;
    new->visited = FALSE;
    new->outputs = make_empty_list();
    return new;
}
