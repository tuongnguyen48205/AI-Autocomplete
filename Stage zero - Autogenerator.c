// Stage zero, used to create the prefix automata constructed from the 
// input statements. It reads the statements character by character in
// order to make the automaton.
void stagezero(automaton_t *automaton) {
    printf(SDELIM, STAGEZERO);

    int chars_num = 0;   // Counts the number of characters
    int c, first_statement = TRUE;
    int double_newspace = FALSE;
    int new_branch = FALSE;
    state_t *latest_state = automaton->ini;
    state_t *current = automaton->ini;
    
    while (((c=mygetchar()) != EOF)) {
        chars_num++;
        
        char c_string[MAX_OUTPUT_SIZE] = "\0";
        c_string[INTZERO] = c;

        // If it is the first line in the input, then each character
        // in the first line will make a new state with frequency one.
        // The very last character in the first line becomes a leaf state.
        if (first_statement == TRUE) {
            if (c == '\n') {
                first_statement = FALSE;
                chars_num--;
                latest_state->freq = INTZERO;             
            }
            else {
                state_t *new = make_new_state(automaton);   
                latest_state->outputs = insert_at_tail(
                    latest_state->outputs, c_string, new);
                latest_state = latest_state->outputs->head->state;
            }
        }
            
        else if (first_statement == FALSE) {
            // If there is a newline character, it means that the last
            // state is a leaf state. If there are two consecutive 
            // newline characters, it is time to print the output for
            // stage zero and move on to stage one.
            if (c == '\n') {
                chars_num--;
                if (double_newspace == TRUE) {
                    print_stagezero(automaton, chars_num);
                    return;
                }
                current->freq = INTZERO;
                current = automaton->ini;
                new_branch = FALSE;
                double_newspace = TRUE;
            }
            else {
                double_newspace = FALSE;
                int match_found = FALSE;
                // Iterate through the automaton trying to find a match.
                // If a match is found, increase its frequency by one.
                if (new_branch == FALSE) {
                    (current->freq)++;
                    node_t *iterator = current->outputs->head;

                    while (iterator != NULL) { 
                        if (c == (iterator->str)[INTZERO]) {
                            match_found = TRUE;
                            current = iterator->state;
                            break;
                        }
                        else {
                            iterator = iterator->next; 
                        }
                    }
                }

                // If a match isn't found in the automaton, it means
                // that it does not exist in the automaton yet and so
                // a new state needs to be created on a new branch.
                if (match_found == FALSE) {
                    new_branch = TRUE;
                    state_t *new = make_new_state(automaton);
                    current->outputs = insert_at_tail(
                        current->outputs, c_string, new);
                    current = current->outputs->tail->state;
                }
            }
        }
    } 
}
