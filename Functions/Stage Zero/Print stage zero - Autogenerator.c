// Prints the output for stage zero.
void print_stagezero(automaton_t *automaton, int char_num) {
    printf("Number of statements: %d\n", automaton->ini->freq);
    printf("Number of characters: %d\n", char_num);
    printf("Number of states: %d\n", (automaton->nid) + INTONE);
}
