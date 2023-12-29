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
