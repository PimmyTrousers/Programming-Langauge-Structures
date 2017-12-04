/*
   TODO List:
   - TODO add functionality to replace sqrt cos and sin with their respective signs, this way you can push the operator rather than interpreting a string and pushing an arbitrary character
   - TODO implement more erro handling such as (sqrt sqrt) and (+ +)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 30                                                                      // definition for the max size of the stack

struct stack                                                                            // definition of stack struct
{
        double stk[MAXSIZE];                                                            // the actual stack implementation
        int top;                                                                        // pointer to the top of the stack
};
typedef struct stack STACK;                                                             // full definition as a datatype

STACK op_stack;                                                                         // stack for operations
STACK num_stack;                                                                        // stack for numbers

void clear_array(char* source, int length);                                             // cleans an array so theres no garbage
int handle_command(char* handle_command);                                               // Will handle commands if implemented
int compare_open_close_brackets(char* command);                                         // will check if the scheme is valid by comparing open and close brackets
void remove_all_chars(char* str, char c);                                               // takes a char and a string and removes the char from the string
double interpret_the_scheme(char* equation);                                            // does the dirty work of interpreting the scheme using 2 stack algorithm
void spacify_the_equation(char spacified_equation[100], char input_equation[100]);      // evens the spaces so that the computer can easily interpret
void add_null_terminator(char* equation);
int validate_token(char* token);                                             // adds a null terminator at the end of the scheme so that no funny business happens
void change_words_to_symbols(char* equation);
int validate_equation(char* equation);

void push(struct stack *s, double elem);                                                // STACK OP to push items
double pop(struct stack *s);                                                            // STACK OP to pop items
void display_char(struct stack *s);                                                     // STACK OP to display the character stack easily
void display_num(struct stack *s);                                                      // STACK OP  to display the number stack easily

int main(int argc, char* argv[]){
        char input_equation[100];
        char temp_equation[100];
        int diff = 0;
        int flag = 0;
        double result = 0;
        clear_array(input_equation, 1000);

        if(argc != 0) {
                printf("this program takes no arguments\n");
                exit(0);
        }
        printf("MIT/GNU Scheme running under OS X\nType `^C' (control-C) followed by `H' to obtain information about interrupts.\n\nCopyright (C) 2014 Massachusetts Institute of Technology\nThis is free software; see the source for copying conditions. There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\nImage saved on Wednesday January 4, 2017 at 8:46:32 AM\nRelease 9.2 || Microcode 15.3 || Runtime 15.7 || SF 4.41 || LIAR/C 4.118 || Edwin 3.116\n\nTHIS IS NOT THE ACTUAL MIT SCHEME\n\n");


        // interpreter loop
        while (1) {
                printf("1 ]=> ");
                fgets(input_equation, 1000, stdin);

                // checks to see if the user is trying to input multiline scheme or single line scheme by counting the number of open and close brackets
                diff = compare_open_close_brackets(input_equation);

                // if the user inputs valid scheme in one line
                if(diff == 0) {
                        flag = 1;
                        if(flag == 0) {
                                clear_array(input_equation, 1000);
                        }
                        else{
                                result = interpret_the_scheme(input_equation);
                                if(result != 57.007) {
                                        if(fmod(result,1) != 0) {
                                                printf(";Value: %lf\n", result);
                                        }else{
                                                printf(";Value: %.0lf\n", result);
                                        }
                                }else{
                                        printf("Invalid Scheme\n");
                                }
                        }
                }
                // if the user wants to input valid multiline scheme
                else if(diff > 0) {
                        while(1) {

                                fgets(temp_equation, 1000, stdin);
                                strcat(temp_equation, " ");
                                strcat(input_equation, temp_equation);

                                remove_all_chars(input_equation, '\n');

                                if(compare_open_close_brackets(input_equation) == 0) {
                                        break;
                                }
                        }
                        result = interpret_the_scheme(input_equation);
                        if(result != 57.007) {
                                if(fmod(result,1) != 0) {
                                        printf(";Value: %lf\n", result);
                                }else{
                                        printf(";Value: %.0lf\n", result);
                                }
                        }else{
                                printf("Invalid Scheme\n");
                        }
                }
                // wtf you doin
                else {
                        printf("exiting now...\n");
                        exit(0);
                }
                // prepare the array for next equation
                clear_array(input_equation, 1000);
        }
}

void clear_array(char* source, int length){
        for(int i = 0; i < length; ++i) {
                source[i] = 0;
        }
}


// return 0 if invalid and 1 if valid
int handle_command(char* handle_command){
        int flag = 0;
        for(int i = 0; i != 1000; i++) {

                if(handle_command[i] > 32 && handle_command[i] < 40) {
                        flag = 0;
                }

                if(handle_command[i] == 's' && handle_command[i+1] == 'i' && handle_command[i+2] == 'n') {
                        return 1;
                }

                if(handle_command[i] == 'c' && handle_command[i+1] == 'o' && handle_command[i+2] == 's') {
                        return 1;
                }
                if(handle_command[i] == 's' && handle_command[i+1] == 'q' && handle_command[i+2] == 'r' && handle_command[i+2] == 't') {
                        return 1;
                }
        }
        return 1;
}

int compare_open_close_brackets(char* command){
        int counter = 0;
        int found = 0;
        for(int i = 0; i < 1000; ++i) {
                if(command[i] == '(') {
                        counter++;
                        found = 1;
                }
                if(command[i] == ')') {
                        counter--;
                        found = 1;
                }
                if(counter == 0 && found == 1) {
                        command[i+1] = 0;
                }
        }
        if(found == 0) {
                return -1;
        }
        return counter;
}

void remove_all_chars(char* str, char c) {
        char *pr = str, *pw = str;
        while (*pr) {
                *pw = *pr++;
                pw += (*pw != c);
        }
        *pw = '\0';

}

double interpret_the_scheme(char* equation){
        op_stack.top = -1;
        num_stack.top = -1;
        char spacified_equation[100];
        char temp[100];
        clear_array(temp, 100);
        double result = 0;
        remove_all_chars(equation, '\n');
        change_words_to_symbols(equation);
        spacify_the_equation(spacified_equation, equation);
        add_null_terminator(spacified_equation);
        printf("new equation \"%s\"\n", spacified_equation);

        char s[256];
        strcpy(s, spacified_equation);
        char* token = strtok(s, " ");
        //validate_token(token);

        for(int i = 0; spacified_equation[i] != '\0'; ++i) {
                if(spacified_equation[i] == '+' || spacified_equation[i] == '-' || spacified_equation[i] == '*' || spacified_equation[i] == '/' || spacified_equation[i] == '^' || spacified_equation[i] == 'c' || spacified_equation[i] == 's' || spacified_equation[i] == 'q' || spacified_equation[i] == 'r') {
                        if(spacified_equation[i+3] == '+' || spacified_equation[i+3] == '-' || spacified_equation[i+3] == '*' || spacified_equation[i+3] == '/' || spacified_equation[i+3] == '^' || spacified_equation[i+3] == 'c' || spacified_equation[i+3] == 's' || spacified_equation[i+3] == 'q' || spacified_equation[i+3] == 'r') {
                                return 57.007;
                        }
                        else {
                                if (spacified_equation[i] == '-' && (spacified_equation[i+1] > 47 && spacified_equation[i+1] < 58)) {
                                        push(&num_stack, -1*(atof(&spacified_equation[i+1])));
                                }else{
                                        push(&op_stack, spacified_equation[i]);
                                }

                        }

                }
                if((spacified_equation[i] > 47 && spacified_equation[i] < 58) || spacified_equation[i] == '.' || spacified_equation[i] == '-') {
                        int holder = i;
                        while(spacified_equation[i] != ' ') {
                                temp[i-holder] = spacified_equation[i];
                                i++;
                        }
                        temp[i] = '\0';
                        if(temp[0] != '-') {
                                push(&num_stack, atof(temp));
                                clear_array(temp, 100);
                        }

                }

        }
        display_char(&op_stack);
        display_num(&num_stack);
        while(op_stack.top != -1) {
                char operator = pop(&op_stack);

                if(operator == '*') {
                        double temp1 = pop(&num_stack);
                        double temp2 = pop(&num_stack);
                        push(&num_stack, temp1*temp2);
                }
                if(operator == '+') {
                        double temp1 = pop(&num_stack);
                        double temp2 = pop(&num_stack);
                        push(&num_stack, temp1+temp2);
                }
                if(operator == '/') {
                        double temp1 = pop(&num_stack);
                        double temp2 = pop(&num_stack);
                        push(&num_stack, temp1/temp2);
                }
                if(operator == '-') {
                        double temp1 = pop(&num_stack);
                        double temp2 = pop(&num_stack);
                        push(&num_stack, temp2-temp1);
                }
                if(operator == '^') {
                        double temp1 = pop(&num_stack);
                        double temp2 = pop(&num_stack);
                        push(&num_stack, pow(temp1, temp2));
                }
                if(operator == 's') {
                        double temp1 = pop(&num_stack);
                        push(&num_stack, sin(temp1));
                }
                if(operator == 'c') {
                        double temp1 = pop(&num_stack);
                        push(&num_stack, cos(temp1));
                }
                if(operator == 'q') {
                        double temp1 = pop(&num_stack);
                        push(&num_stack, sqrt(temp1));
                }
                if(operator == 'r') {
                        double temp1 = pop(&num_stack);
                        push(&num_stack, temp1*temp1);
                }
                display_char(&op_stack);
                display_num(&num_stack);
        }

        result = pop(&num_stack);
        return result;
}

/*  Function to add an element to the stack */

void push(struct stack *s, double elem){
        int num;
        if (s->top == (MAXSIZE - 1))
        {
                printf ("Stack is Full\n");
                return;
        }
        else
        {
                s->top = s->top + 1;
                s->stk[s->top] = elem;
        }
        return;
}

/*  Function to delete an element from the stack */

double pop (struct stack *s){
        double num;
        if (s->top == -1)
        {
                printf ("Stack is Empty\n");
                exit(0);
                return (s->top);
        }
        else
        {
                num = (double)s->stk[s->top];
                s->top = s->top - 1;
        }
        return num;
}

/*  Function to display the status of the stack */

void display_char(struct stack *s){
        int i;
        if (s->top == -1)
        {
                printf ("Stack is empty\n");
                exit(0);
                return;
        }
        else
        {
                printf ("\n The status of the character stack is \n");
                for (i = s->top; i >= 0; i--)
                {
                        printf ("\"%c\"\n", (char)s->stk[i]);
                }
        }
        printf ("\n");
}

/*  Function to display the status of the stack */

void display_num(struct stack *s){
        int i;
        if (s->top == -1)
        {
                printf ("Stack is empty\n");
                exit(0);
                return;
        }
        else
        {
                printf ("\n The status of the number stack is \n");
                for (i = s->top; i >= 0; i--)
                {
                        printf ("%lf\n", s->stk[i]);
                }
        }
        printf ("\n");
}

void spacify_the_equation(char spacified_equation[100], char input_equation[100]){
        int flag = 0;
        int count = 0;

        for(int i = 0; input_equation[i] != '\0'; i++) {
                flag = 0;
                if(input_equation[i] == '+') {
                        spacified_equation[count] = ' ';
                        count++;
                        spacified_equation[count] = '+';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;

                }
                if(input_equation[i] == '-') {
                        if(!(input_equation[i+1] > 47 && input_equation[i+1] < 58)) {
                                spacified_equation[count] = ' ';
                                count++;
                                spacified_equation[count] = '-';
                                count++;
                                spacified_equation[count] = ' ';
                                count++;
                                flag = 1;
                        }
                }
                if(input_equation[i] == '/') {
                        spacified_equation[count] = ' ';
                        count++;
                        spacified_equation[count] = '/';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;
                }
                if(input_equation[i] == '*') {
                        spacified_equation[count] = ' ';
                        count++;
                        spacified_equation[count] = '*';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;
                }
                if(input_equation[i] == ')') {
                        spacified_equation[count] = ' ';
                        count++;
                        spacified_equation[count] = ')';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;
                }
                if(input_equation[i] == '(') {
                        if(i != 0) {
                                spacified_equation[count] = ' ';
                                count++;
                        }
                        spacified_equation[count] = '(';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;
                }
                if(flag == 0) {
                        spacified_equation[count] = input_equation[i];
                        count++;
                }
        }
        spacified_equation[count] = ' ';
        for(int i = 0; i != 100; i++) {
                if(spacified_equation[i] == ' ' && spacified_equation[i+1] == ' ') {
                        memmove(&spacified_equation[i], &spacified_equation[i+1], strlen(spacified_equation) - i);
                }
        }
}

void add_null_terminator(char* equation){
        int counter = 0;
        for(int i = 0; i < 1000; i++) {
                if(equation[i] == '(') {
                        counter++;
                }
                if(equation[i]==')') {
                        counter--;
                }
                if(counter == 0) {
                        equation[i+1] = 0;
                        break;
                }
        }
}

int validate_token(char* token){
        int i= 0;
        char *token_array[100];
        while (token != NULL) {
                token_array[i++] = token;
                token = strtok (NULL, " ");
        }
        for(i = 0; i != 100; i++) {
                if(*token_array[i] != '+' && *token_array[i] != '-' && *token_array[i] != '*' && *token_array[i] != '/' && *token_array[i] != 's' && *token_array[i] != 'c' && *token_array[i] != 'q' && *token_array[i] != 'r' && *token_array[i] != '(' && *token_array[i] != ')') {
                        printf("i was hit");
                }

        }
        // while(token) {
        //         if(*token != '+' && *token != '-' && *token != '*' && *token != '/' && *token != 's' && *token != 'c' && *token != 'q' && *token != 'r' && *token != '(' && *token != ')') {
        //                 if(atof(token) < 0 && atof(token) > 100) {
        //                         printf("Was i hit");
        //                         return 1;
        //                 }
        //         }
        //         printf("token: %s\n", token);
        //
        //         if(*token == '+' || *token == '-' || *token == '*' || *token == '/') {
        //                 printf("%f %f", atof((token+2)), atof(token+3));
        //                 if((atof((token+2)) > 0 && atof((token+2)) < 100) && (atof((token+3)) > 0 && atof((token+3)) < 100)) {
        //                         printf("valid");
        //                 }
        //         }
        //
        //         token = strtok(NULL, " ");
        // }
        return 0;
}

void change_words_to_symbols(char* spacified_equation){
        for(int i = 0; spacified_equation[i] != 0; i++) {
                if(spacified_equation[i] == 's' && spacified_equation[i+1] == 'i' && spacified_equation[i+2] == 'n') {
                        spacified_equation[i+1] = ' ';
                        spacified_equation[i+2] = ' ';
                }
                if(spacified_equation[i] == 'c' && spacified_equation[i+1] == 'o' && spacified_equation[i+2] == 's') {
                        spacified_equation[i+1] = ' ';
                        spacified_equation[i+2] = ' ';
                }
                if(spacified_equation[i] == 's' && spacified_equation[i+1] == 'q' && spacified_equation[i+2] == 'r' && spacified_equation[i+3] == 't') {
                        spacified_equation[i] = ' ';
                        spacified_equation[i+2] = ' ';
                        spacified_equation[i+3] = ' ';
                }
                if(spacified_equation[i] == 's' && spacified_equation[i+1] == 'q' && spacified_equation[i+2] == 'u' && spacified_equation[i+3] == 'a' && spacified_equation[i+4] == 'r' && spacified_equation[i+5] == 'e') {
                        spacified_equation[i] = ' ';
                        spacified_equation[i+1] = ' ';
                        spacified_equation[i+2] = ' ';
                        spacified_equation[i+3] = ' ';
                        spacified_equation[i+5] = ' ';
                }
        }
}
