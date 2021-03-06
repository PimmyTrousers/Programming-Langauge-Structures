#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXSIZE 10                                                                      // definition for the max size of the stack

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
void add_null_terminator(char* equation);                                               // adds a null terminator at the end of the scheme so that no funny business happens

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
                        flag = handle_command(input_equation);
                        if(flag == 0) {
                                clear_array(input_equation, 1000);
                        }
                        else{
                                result = interpret_the_scheme(input_equation);
                                if(fmod(result,1) != 0) {
                                        printf(";Value: %lf\n", result);
                                }else{
                                        printf(";Value: %.0lf\n", result);
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
                        if(fmod(result,1) != 0) {
                                printf(";Value: %lf\n", result);
                        }else{
                                printf(";Value: %.0lf\n", result);
                        }
                }
                // wtf you doin
                else {
                        printf("too many closed brackets\n");
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

int handle_command(char* handle_command){
        for(int i = 0; i != 1000; i++) {
                if(handle_command[i] > 64 && handle_command[i] < 91) {
                        return 0;
                }
                if(handle_command[i] > 96 && handle_command[i] < 123) {
                        return 0;
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
        spacify_the_equation(spacified_equation, equation);
        add_null_terminator(spacified_equation);
        // printf("new equation \"%s\"\n", spacified_equation);

        for(int i = 0; spacified_equation[i] != '\0'; ++i) {
                if(spacified_equation[i] == '+' || spacified_equation[i] == '-' || spacified_equation[i] == '*' || spacified_equation[i] == '/' || spacified_equation[i] == '^') {
                        push(&op_stack, spacified_equation[i]);

                }
                else if((spacified_equation[i] > 47 && spacified_equation[i] < 58) || spacified_equation[i] == '.') {
                        int holder = i;
                        while(spacified_equation[i] != ' ') {
                                temp[i-holder] = spacified_equation[i];
                                i++;
                        }
                        temp[i] = '\0';
                        push(&num_stack, atof(temp));
                        clear_array(temp, 100);
                }
        }
        //display_char(&op_stack);
        //display_num(&num_stack);
        while(op_stack.top != -1) {
                char operator = pop(&op_stack);
                double temp1 = pop(&num_stack);
                double temp2 = pop(&num_stack);
                if(operator == '*') {
                        push(&num_stack, temp1*temp2);
                }
                if(operator == '+') {
                        push(&num_stack, temp1+temp2);
                }
                if(operator == '/') {
                        push(&num_stack, temp2/temp1);
                }
                if(operator == '-') {
                        push(&num_stack, temp1-temp2);
                }
                if(operator == '^') {
                        push(&num_stack, pow(temp1, temp2));
                }
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
                return;
        }
        else
        {
                printf ("\n The status of the stack is \n");
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
                return;
        }
        else
        {
                printf ("\n The status of the stack is \n");
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
                        spacified_equation[count] = ' ';
                        count++;
                        spacified_equation[count] = '-';
                        count++;
                        spacified_equation[count] = ' ';
                        count++;
                        flag = 1;
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
