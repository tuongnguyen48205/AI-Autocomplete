// Stage one. Generates output for a prompt based on the frequency of the 
// characters that appear within the prompts provided.
void stageone(automaton_t *automaton) {
    int c, chars_counter = 0;
    state_t *current = automaton->ini;
    node_t *iterator = current->outputs->head;
    int double_newspace = FALSE, next_line = FALSE;
    
    while (TRUE) {
        // A single newline character means that the prompt has been processed
        // and the output can now be printed. Two consecutive newline characters
        // means that its time to move to stage two.
        c = mygetchar();
        if (c == '\n' || c == EOF) {
            if (double_newspace == TRUE) {
                return;
            }
            double_newspace = TRUE;
            char *output = (char*)malloc(MAX_OUTPUT_SIZE * sizeof(char*));
            int output_index = 0;
            int leaf_tracker = FALSE;
            
            // A while loop is used to find the next state in the output
            while (leaf_tracker == FALSE && chars_counter != MAX_OUTPUT_SIZE) {
                iterator = current->outputs->head;
                unsigned int max_freq = 0;
                int greatest_ASCII = 0;
                if (current->freq == INTZERO || next_line == TRUE) {
                    leaf_tracker = TRUE;
                }
                else {
                    // Begin by finding the state with the highest frequency
                    // as well as largest ASCII at the same time for the case
                    // where two or more states share the largest frequency.
                    while (iterator != NULL) {
                        if (iterator->state->freq >= max_freq && 
                        (int)(iterator->str)[INTZERO] >= greatest_ASCII) {
                            max_freq = iterator->state->freq;
                            greatest_ASCII = (int)((iterator->str)[INTZERO]);
                        }
                        iterator = iterator->next;
                    }
                    output[output_index] = (char)greatest_ASCII;
                    output_index++;

                    // Set 'current' to be the state that corresponds to the 
                    // state containing the highest frequency and ASCII value.
                    iterator = current->outputs->head;
                    while (iterator != NULL) {
                        if ((int)((iterator->str)[INTZERO]) == greatest_ASCII) {
                            current = iterator->state;
                            break;
                        }
                        else {
                            iterator = iterator->next;
                        }
                    }
                }
            }           
            // Print out the output and reset current and free the output
            chars_counter = print_stageone(chars_counter, output_index, output,
                                          next_line);
            current = automaton->ini;
            free(output);
        }
        else {
            double_newspace = FALSE;               
            // Print out the prompt, making sure it is less than 37 characters
            if (chars_counter < MAX_OUTPUT_SIZE) {
                chars_counter++;
                printf("%c", c);
            }
            // Start by doing a comparison of the prompt to the automaton
            int match_found = FALSE;
            next_line = FALSE;
            iterator = current->outputs->head;

            while (iterator != NULL) {
                if (c == (iterator->str)[INTZERO]) {
                    current = iterator->state;
                    match_found = TRUE;
                    break;
                }
                else {
                    iterator = iterator->next;
                }
            }  
            // If a character in the prompt is not present in the automaton,
            // it means that the automaton does not support a replay of the 
            // entire prompt so append an elipse and don't generate text.
            if (match_found == FALSE) {
                next_line = TRUE;
                for (int k = 0; k < ELIPSE; k++) {
                    if (chars_counter < MAX_OUTPUT_SIZE) {
                        chars_counter++;
                        printf(".");
                    }
                }
            } 
        }              
    }
}