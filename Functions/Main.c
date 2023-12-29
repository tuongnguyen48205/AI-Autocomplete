int main(int argc, char *argv[]) {
    // Message from Artem: The proposed in this skeleton file #define's,
    // typedef's, and struct's are the subsets of those from my sample solution
    // to this assignment. You can decide to use them in your program, or if
    // you find them confusing, you can remove them and implement your solution
    // from scratch. I will share my sample solution with you at the end of
    // the subject.

    // Start by making the automaton
    automaton_t *automaton = (automaton_t*)malloc(sizeof(*automaton));
    automaton->nid = NEGONE;
    automaton->ini = make_new_state(automaton);
    
    // Now go to stage 0.
    stagezero(automaton);
    
    // Now go to stage 1.
    printf(SDELIM, STAGEONE);
    stageone(automaton);
    
    // Now go to stage 2.
    stagetwo(automaton);
    
    // Finished, just need to free everything. A placeholder is used to allow 
    // the free_automaton function to work. After that is done, we just need to 
    // free the actual automaton.
    state_t *placeholder = (state_t*)malloc(sizeof(*placeholder));
    placeholder->outputs = make_empty_list();
    free_automaton(automaton, automaton->ini, placeholder);
    free(automaton);
    
    printf(THEEND);
    return EXIT_SUCCESS;        // algorithms are fun!!!
}
