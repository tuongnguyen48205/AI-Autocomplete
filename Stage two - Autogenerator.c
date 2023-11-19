// Stage two. Compresses the automaton, doing a certain number of compression
// steps based on the number provided in stdin and processes prompts as well.
void stagetwo(automaton_t *automaton) {
    printf(SDELIM, STAGETWO);
    
    int c, i = 0;
    char *compression_steps_str = (char*)malloc(sizeof(
                                *compression_steps_str));
    int compression_steps_num = 0;
    
    while (((c=mygetchar()) != EOF)) {
        // Get the number of compression steps that need to be done
        if (c == '\n') {
            break;
            }
        else {
            // To save memory, make the array as small as possible and
            // increase in size based off of the size of the number in 
            // stdin
            compression_steps_str[i] = c;
            i++;
            compression_steps_str = (char*)realloc(compression_steps_str, 
                                                    sizeof(char) * i);
            compression_steps_str[i] = '\0';
        }
    }
    
    // Convert to integer and free the array
    compression_steps_num = atoi(compression_steps_str);
    free(compression_steps_str);
        
    /*
    // Start by finding the first depths order
    int firstorder[] = {INTZERO};
    int n = 0;
    state_t *current = automaton->ini;
    find_depths_first_order(automaton, firstorder, current, n);
            
    // Now do the compressions since we have found the first depths order. 
    // Start by finding valid contractions and do it the number of times 
    // as specified in the input prompt.
    int j, k, compression_tracker = 0;
    unsigned int compression_start, compression_end;
    for (j = 0; j < compression_steps_num; j++) {
        for (k = compression_tracker; k < automaton->nid; k++) {
            compression_tracker++;
            if (firstorder[k] - firstorder[k - INTONE] == INTONE) {
                compression_start = firstorder[k - INTONE];
                compression_end = firstorder[k];
                break;
            }
        }
        do_compression(automaton, compression_start, compression_end);
    }
    */     
                
    // Now to print the output for stage 2 and process the prompts and find
    // the total frequency.
    int frequency = 0;
    frequency = frequency_finder(automaton, frequency, automaton->ini);
    print_stagetwo(automaton, frequency, compression_steps_num);
    printf(MDELIM);
    stageone(automaton);
    return;
}