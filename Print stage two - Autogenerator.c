// Prints the output for stage two
void print_stagetwo(automaton_t *automaton, int frequency, int comp_steps_num) {
    printf("Number of states: %d\n", 
           (automaton->nid) + INTONE - comp_steps_num);
    printf("Total frequency: %d\n", frequency);
}