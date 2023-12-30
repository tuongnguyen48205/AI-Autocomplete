// Finds the total frequency of the automaton using a recursive function call
int frequency_finder(automaton_t *automaton, int frequency, state_t *current) {
    node_t *iterator = current->outputs->head;
    frequency += current->freq;
    while (iterator != NULL) {
        current = iterator->state;
        iterator = iterator->next;
        frequency = frequency_finder(automaton, frequency, current);
    }
    return frequency;
}
