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