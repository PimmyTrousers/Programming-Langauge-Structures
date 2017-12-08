#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double term(char op[][50]);
double factor(char op[][50]);
double expression(char op[][50]);
int isnum(char *w);

int isnum(char *w)
{
    char *str = w;
    int span = strspn(w, "0123456789.-");
    if (str[span] == '\0')
    {
        return 1;
    }
    return 0;
}

double term(char op[][50])
{
    if (op[1][0] == 0)
    {
        return convert_num(op[1]);
    }
}

double factor(char op[][50])
{
    if (op[1][0] == 0)
    {
        return convert_num(op[1]);
    }
}

double expression(char op[][50])
{
    double result = 0;
    if (op[1][0] == 0)
    {
        return convert_num(op[1]);
    }
    for (int i = 0; op[i][0] != 0; i++)
    {
        if(isnum(op[i])){
            result += convert_num(op[i]);
        }
        if(strcmp(op[i], "*") == 1){
            result += term(op[i-1]);
        }
    }
}

void error_out(char *clue)
{
    printf("error: invalid entry... ");
    printf("%s\n", clue);
    exit(0);
}

double convert_num(char *num)
{
    int i, decimal_flag = 0, neg_flag = 1, digit;
    double number = 0;
    for (i = 0; num[i] > 0 && num[i] != 10; i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            digit = num[i] - '0';
            if (decimal_flag > 0)
            {
                number += digit / pow(10, decimal_flag);
                decimal_flag++;
            }
            else
            {
                number *= 10;
                number += digit;
            }
        }
        else if (num[i] == '.')
        {
            if (decimal_flag > 0)
            {
                error_out(num);
            }
            decimal_flag = 1;
        }
        else if (i == 0 && num[i] == '-')
        {
            neg_flag = -1;
        }
        else
        {
            error_out(num);
        }
    }
    return number * neg_flag;
}

int not_syn(char c)
{
    return c != ')' && c != '(' && c != ' ';
}
int paren(char c)
{
    return c == ')' || c == '(';
}
int whitespace(char c)
{
    return c == ' ' || c == '\n';
}
int end(char *s)
{
    return s[0] == ')' || s[0] <= 0;
}
int sub(char *operand)
{
    return operand[0] == '-' && operand[1] < 1;
}
int add(char *operand)
{
    return operand[0] == '+' && operand[1] < 1;
}
int isdiv(char *operand)
{
    return operand[0] == '/' && operand[1] < 1;
}
int mul(char *operand)
{
    return operand[0] == '*' && operand[1] < 1;
}

void copy(char *to, char *from)
{
    int i = 0;
    while (1)
    {
        to[i] = from[i];
        if (from[i] < 1)
            break;
        i++;
    }
}

char pop(char op[][50])
{
    int i;
    char c = op[0][0];
    for (i = 0; 1; i++)
    {
        copy(op[i], op[i + 1]);
        if (op[i][0] < 1)
            break;
    }
    return c;
}

void printop(char op[][50])
{
    int i;
    for (i = 0; 1; i++)
    {
        if (op[i][0] < 1)
            break;
        printf("%s ", op[i]);
    }
    printf("\n");
}

void read(char *filename, char op[50000][50])
{
    char c;
    int i = 0, j;
    FILE *fp = fopen(filename, "r");

    while (1)
    {
        c = fgetc(fp);
        while (whitespace(c))
        {
            c = fgetc(fp);
        }
        if (c == EOF)
            break;

        if (paren(c))
        {
            op[i][0] = c;
            op[i][1] = 0;
        }
        else
        {
            j = 0;
            while (1)
            {
                op[i][j] = c;
                if (paren(c))
                {
                    op[i][j] = 0;
                    i++;
                    op[i][0] = c;
                    op[i][1] = 0;
                    break;
                }
                if (c == ' ' || c < 1)
                {
                    op[i][j] = 0;
                    break;
                }
                j++;
                c = fgetc(fp);
                if (c == EOF)
                    break;
            }
        }
        i++;
    }
    op[i][0] = 0;
}

int main(int argc, char **argv)
{
    argc--;
    char op[5000][50];
    int i;
    char filename[20];
    if (argc == 0)
    {
        printf("No filename specified. Please provide one: ");
        scanf(" %s", filename);
        argv[1] = filename;
        argc++;
    }
    for (i = 0; i < argc; i++)
    {
        read(argv[i + 1], op);
        printf("%s: %lf\n", argv[i + 1], solve(op));
    }
}
