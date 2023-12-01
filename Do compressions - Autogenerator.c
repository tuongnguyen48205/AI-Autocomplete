// Does the compression by joining adjacent states following the depths first
// order and deletes the arc between the two states involved in the compression.
// Does nothing if the compression isn't valid or if there are no more 
// compressions left to do.
void do_compression(automaton_t *automaton, unsigned int compression_start, 
               unsigned int compression_end) {
    
    state_t *start = automaton->ini;
    state_t * end;
    node_t *iterator = start->outputs->head, *output_len_iterator;
    
    // Start by finding where the compression starts in the automaton. If there
    // is more than one state connected, this is an invalid contraction so
    // returns.
    while (TRUE) {
        start->visited = TRUE;
        if (start->id == compression_start) {
            break;
        }
        else {
            while (iterator != NULL) {
                if (iterator->state->id == compression_start) {
                    start = iterator->state;
                    output_len_iterator = start->outputs->head;
                    int output_len_tracker = 0;
                    
                    while (output_len_iterator != NULL) {
                        output_len_tracker++;
                        iterator = iterator->next;
                    }
                    
                    if (output_len_tracker > INTONE) {
                        return;
                    }
                    
                    break;
                }
                else {
                    iterator = iterator->next;
                }
            }
            // No match found
            if (iterator == NULL) {
                // We know that it will not be found on a branch where the 
                // state id is greater than the one we're looking for
                iterator = start->outputs->head;
                while (iterator != NULL) {
                    if (compression_start > iterator->state->id &&
                        iterator->state->visited == FALSE) {
                        start = iterator->state;
                        break;
                    }
                }
            }
        }
    }  
    // Now find where the compression ends. If the end is a leaf state, it is 
    // not a valid contraction so returns. There should only be one arc 
    // connecting both of the states involved in the contraction.
    end = start->outputs->head->state;
    assert(end->id == compression_end);
    if (end->freq == INTZERO) {
        return;
    }

    // Now we can do the actual compression and delete the previous arc and 
    // join the two states and transfer over the outputs and free old nodes
    iterator = end->outputs->head;
    while (iterator != NULL) {
        node_t *new = (node_t*)malloc(sizeof(*new));
        (new->str)[INTZERO] = (start->outputs->head->str)[INTZERO];
        (new->str)[INTONE] = (iterator->str)[INTZERO];
        new->state = iterator->state;
        // Insert it into the outputs list at the head. (Inspired by Alistair
        // Moffat's insert_at_head function)
        new->next = start->outputs->head;
        start->outputs->head = new;
        if (start->outputs->tail == NULL) {
            start->outputs->tail = new;
        }
        node_t *prev = iterator;
        iterator = iterator->next;
        free(prev);
    }
    // Now remove the old output which would be at the tail of the outputs
    // and free the end state     
    free(start->outputs->tail);
    free(end->outputs);
    free(end);    
}