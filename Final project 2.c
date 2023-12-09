/* Program to generate text based on the context provided by input prompts.

  Skeleton program written by Artem Polyvyanyy, http://polyvyanyy.com/,
  September 2023, with the intention that it be modified by students
  to add functionality, as required by the assignment specification.
  All included code is (c) Copyright University of Melbourne, 2023.

  Student Authorship Declaration:

  (1) I certify that except for the code provided in the initial skeleton file,
  the program contained in this submission is completely my own individual
  work, except where explicitly noted by further comments that provide details
  otherwise. I understand that work that has been developed by another student,
  or by me in collaboration with other students, or by non-students as a result
  of request, solicitation, or payment, may not be submitted for assessment in
  this subject. I understand that submitting for assessment work developed by
  or in collaboration with other students or non-students constitutes Academic
  Misconduct, and may be penalized by mark deductions, or by other penalties
  determined via the University of Melbourne Academic Honesty Policy, as
  described at https://academicintegrity.unimelb.edu.au.

  (2) I also certify that I have not provided a copy of this work in either
  softcopy or hardcopy or any other form to any other student, and nor will I
  do so until after the marks are released. I understand that providing my work
  to other students, regardless of my intention or any undertakings made to me
  by that other student, is also Academic Misconduct.

  (3) I further understand that providing a copy of the assignment specification
  to any form of code authoring or assignment tutoring service, or drawing the
  attention of others to such services and code that may have been made
  available via such a service, may be regarded as Student General Misconduct
  (interfering with the teaching activities of the University and/or inciting
  others to commit Academic Misconduct). I understand that an allegation of
  Student General Misconduct may arise regardless of whether or not I personally
  make use of such solutions or sought benefit from such actions.

  Signed by: Tuong Bao Nguyen 1463906
  Dated:     08/10/2023

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* #DEFINE'S -----------------------------------------------------------------*/
#define SDELIM "==STAGE %d============================\n"   // stage delimiter
#define MDELIM "-------------------------------------\n"    // delimiter of -'s
#define THEEND "==THE END============================\n"    // end message
#define NOSFMT "Number of statements: %d\n"                 // no. of statements
#define NOCFMT "Number of characters: %d\n"                 // no. of chars
#define NPSFMT "Number of states: %d\n"                     // no. of states
#define TFQFMT "Total frequency: %d\n"                      // total frequency

#define STAGEZERO 0                                         // stage zero
#define STAGEONE 1                                          // stage one
#define STAGETWO 2                                          // stage two

#define TRUE 1                                        // if a statement is true 
#define FALSE 0                                       // if a statement is 
                                                      // false 

#define INTZERO 0                                      // integer zero
#define INTONE 1                                       // integer one
#define NEGONE -1                                      // integer negative one

#define CRTRNC '\r'                             // carriage return character

#define MAX_OUTPUT_SIZE 37                      // maximum size of output

#define ELIPSE 3                                // number of dots in an elipse

/* TYPE DEFINITIONS ----------------------------------------------------------*/
typedef struct state state_t;   // a state in an automaton
typedef struct node  node_t;    // a node in a linked list

struct node {                   // a node in a linked list of transitions has
    char            str[MAX_OUTPUT_SIZE];        // ... a transition string
    state_t*        state;      // ... the state reached via the string, and
    node_t*         next;       // ... a link to the next node in the list.
};

typedef struct {                // a linked list consists of
    node_t*         head;       // ... a pointer to the first node and
    node_t*         tail;       // ... a pointer to the last node in the list.
} list_t;

struct state {                  // a state in an automaton is characterized by
    unsigned int    id;         // ... an identifier,
    unsigned int    freq;       // ... frequency of traversal,
    int             visited;    // ... visited status flag, and
    list_t*         outputs;    // ... a list of output states.
};

typedef struct {                // an automaton consists of
    state_t*        ini;        // ... the initial state, and
    int    nid;        // ... the identifier of the next new state.
} automaton_t;

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
int mygetchar(void);   // getchar() that skips carriage returns
void stagezero(automaton_t *automaton);   // starts stage zero
list_t *make_empty_list(void);   // makes an empty list written by Alistair 
    // Moffat. Copyright is found above function at the end of the program.
list_t *insert_at_tail(list_t *list, char str[], state_t *state);   // insert 
    //item at end of list. Modified version of insert_at_foot by Alistair Moffat
state_t *make_new_state(automaton_t *automaton);  // Makes a new state
void print_stagezero(automaton_t *automaton, int char_num);  //prints stage zero
void stageone(automaton_t *automaton);   // starts stage one
int print_stageone(int chars_counter, int output_index, char output[], 
                    int next_line);   // prints stageone
void stagetwo(automaton_t *automaton);   // starts stage two
void free_automaton(automaton_t *automaton, state_t *current, 
                    state_t *prev_state);   // frees the automaton
void sort_int_array(int A[], int n);   // Sorts the array in ascending order.
    // Written by Alistair Moffat
void int_swap(int *p1, int *p2);   // Swaps two integers. Written by 
    // Alistair Moffat
void find_depths_first_order(automaton_t *automaton,  int firstorder[],
                            state_t *current, int n);   
    // finds the depths first order
void print_stagetwo(automaton_t *automaton, int frequency, 
                    int comp_steps_num);   // prints stage two
int frequency_finder(automaton_t *automaton, int frequency, 
                     state_t *current);
    // finds the total frequency of the automaton
void do_compression(automaton_t *automaton, unsigned int compression_start, 
                    unsigned int compression_end);   // Does the compression

/* WHERE IT ALL HAPPENS ------------------------------------------------------*/
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

/* STAGES --------------------------------------------------------------------*/

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


/* USEFUL FUNCTIONS ----------------------------------------------------------*/

// An improved version of getchar(); skips carriage return characters.
// NB: Adapted version of the mygetchar() function by Alistair Moffat
int mygetchar() {
    int c;
    while ((c=getchar())==CRTRNC);
    return c;
}

// Inserts a node at the end of the list. Modified version of insert_at_foot
// written by Alistair Moffat.
list_t *insert_at_tail(list_t *list, char str[], state_t *new_state) {
    node_t *new = (node_t *)malloc(sizeof(*new));
    assert(list != NULL && new != NULL);
    new->state = new_state;
    strcpy(new->str, str);
    new->next = NULL;
    if (list->tail == NULL) {
        // this is the first insertion into the list
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    return list;
}

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

// Prints the output for stage zero.
void print_stagezero(automaton_t *automaton, int char_num) {
    printf("Number of statements: %d\n", automaton->ini->freq);
    printf("Number of characters: %d\n", char_num);
    printf("Number of states: %d\n", (automaton->nid) + INTONE);
}

// Prints the output for stage one and returns zero since we want to 
// reset the number of characters printed back to zero. While 
// printing, make sure that the output does not exceed the maximum 
// output size.
int print_stageone(int chars_counter, int output_index, char output[], 
                    int next_line) {
    // Start with the elipse.
    if (next_line == FALSE) {
        for (int j = 0; j < ELIPSE; j++) {
            if (chars_counter < MAX_OUTPUT_SIZE) {
                chars_counter++;
                printf(".");
            }
        }
    }

    // Now print the generated output.
    for (int i = 0; i < output_index; i++) {
        if (chars_counter < MAX_OUTPUT_SIZE) {
            chars_counter++;
            printf("%c", output[i]);
        }
        else {
            break;
        }
    }
    printf("\n");
    return INTZERO;
}

// Find the depths first order of the given automaton. uses a recursive 
// function call in order to do so.
void find_depths_first_order(automaton_t *automaton, int firstorder[],
                            state_t *current, int n) {
    
    // Place the current state into the first order array in the depths
    // first order
    firstorder[n] = current->id;
    n++;
    
    // Start by listing all the ASCII values for the outputs and sort it into
    // ascending order
    int ASCII_index[] = {INTZERO};
    int array_tracker = 0;
    node_t *iterator = current->outputs->head;
    while (iterator != NULL) { 
        ASCII_index[array_tracker] = (int)((iterator->str)[INTZERO]);
        array_tracker++;
        iterator = iterator->next;
    }
    sort_int_array(ASCII_index, array_tracker);

    // Now use a recursive call to go through the whole automaton and repeat
    // the process for every state
    for (int i = 0; i < array_tracker; i++) {
        iterator = current->outputs->head;
        if ((int)(iterator->str[INTZERO]) == ASCII_index[i]) {
            current = iterator->state;
            find_depths_first_order(automaton, firstorder, current, n);
        }
    } 
    return;
}

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

// Prints the output for stage two
void print_stagetwo(automaton_t *automaton, int frequency, int comp_steps_num) {
    printf("Number of states: %d\n", 
           (automaton->nid) + INTONE - comp_steps_num);
    printf("Total frequency: %d\n", frequency);
}

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

// Alistair Moffat, PPSAA, Chapter 10, December 2012
// (c) University of Melbourne
list_t *make_empty_list(void) {
    list_t *list = (list_t *) malloc(sizeof(*list));
    assert(list != NULL);
    list->head = list->tail = NULL;
    return list;
}

/* sorts n elements of array A in increasing order (2, 3, 4, 5)
 * using insertion sort (insertionsort.c, Figure 7.4 PPSAA) */
// By Alistair Moffat
void sort_int_array(int A[], int n) {
    /* assume that A[0] to A[n-1] have valid values */

    for (int i = 1; i < n; i++) {
        /* swap A[i] left into correct position (increasing order). */
        for (int j = i - 1; j >= 0 && A[j] > A[j + 1]; j--) {
            /* not there yet */
            int_swap(&A[j], &A[j + 1]);
        }
    }
}

/* exchange the values of the two variables indicated
 * by the arguments (insertionsort.c, Figure 7.4 PPSAA) */
// By Alistair Moffat
void int_swap(int *p1, int *p2) {
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}