# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>

void write_temp_equation(FILE* g);
double expression(char *w, double res);
int is_it_a_num(char *w);
int compare_open_close_brackets(char* command);



FILE *tmp;

typedef struct {
        char symbol[100];
        double value;
} SYMBOLTABLE;

SYMBOLTABLE symbol_table[100];

int main(int argc, char *argv[]){
        int q,n, numchars;
        double result;
        char token[100];
        int i = 0;
        FILE* input_file;
        char equation[200];
        char* result_string;
        input_file = fopen(argv[1], "r");

        if (input_file == NULL) {
                exit(1);
        }

        tmp = fopen("temp", "w");

        if (tmp == NULL) {
                exit(1);
        }

        // fgets(equation, 200, input_file);
        // printf("The input equation is %s\n", equation);
        // int paren_result = compare_open_close_brackets(equation);
        // printf("paren result is %d\n", paren_result);
        // if(paren_result != 0) {
        //         printf("invalid scheme\n");
        //         exit(0);
        // }

        //remove the ending \n
        size_t len = strlen(equation);
        if (len > 0 && equation[len - 1] == '\n'){
                equation[len - 1] = '\0';
        }

        write_temp_equation(input_file);
        fclose(tmp);

        tmp = fopen("temp", "r");
        if (tmp == NULL) {
                exit(1);
        }

        int j = 1;
        i = 0;


        //iterate over each character in the file
        while(1) {
                j = 1;
                n = fscanf(tmp, "%s", token);
                // printf("n is %d\n", n);
                // printf("token is \"%s\"\n", token);
                if (n == 1) {
                        if(strcmp("(", token) == 0) {
                                fscanf(tmp, "%s", token);
                                // printf("w is %s\n", w);
                        }
                        result = expression(token, 0);

                }
                if(n == -1) {
                        break;
                }
                if(j == 1) {
                        printf("%lf\n", result);
                }
        }
        system("rm temp");
        fclose(input_file);
}

void write_temp_equation(FILE* g){
        int q;
        q = fgetc(g);
        while (q != EOF) {
                // spacify the equation
                if ((q == '(') || (q == ')')) {
                        fputc(' ', tmp);
                        fputc(q, tmp);
                        fputc(' ', tmp);
                } else {
                        fputc(q, tmp);
                }
                q = fgetc(g);
        }
}

int is_it_a_num(char *w){
        char* str= w;
        int span = strspn(w, "0123456789.-");
        if(str[span] == '\0') {
                return 1;
        }
        return 0;
}

double expression(char *w, double res){
        // printf("w is %s\n", w);
        double v1;
        double v2;
        if(w[0] == ')') {
                return res;
        }
        // check if at the end of the operation
        if(is_it_a_num(w)) {
                return atof(w);
        }

        if(strcmp("(", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, res);
        }
        if(strcmp("+", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v2 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, v1+v2);
                // fscanf(tmp, "%s", w);
        }
        if(strcmp("-", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v2 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, v1-v2);
                //   fscanf(tmp, "%s", w);
        }
        if(strcmp("*", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v2 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, v1*v2);
                //   fscanf(tmp, "%s", w);
        }
        if(strcmp("/", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v2 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, v1/v2);
                // fscanf(tmp, "%s", w);
        }
        if(strcmp("sqrt", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, sqrt(v1));
        }
        if(strcmp("square", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, v1*v1);
                //    fscanf(tmp, "%s", w);
        }
        if(strcmp("sin", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, sin(v1));
                //  fscanf(tmp, "%s", w);
        }
        if(strcmp("cos", w) == 0) {
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                v1 = expression(w, res);
                fscanf(tmp, "%s", w);
                // printf("w is %s\n", w);
                res = expression(w, cos(v1));
        }

        // if our value in our symbol table matches our token return the result
        if(strcmp(symbol_table[0].symbol, w) == 0) {
                return symbol_table[0].value;
        }


        return res;
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
