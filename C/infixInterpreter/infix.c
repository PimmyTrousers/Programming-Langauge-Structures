#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error_out(char *clue)
{
    printf("ERRORRRRRR\n");
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

int end_expression(char c)
{
    return c == ')' || c == 0;
}
int end_term(char c)
{
    return c == '+' || c == '-' || c == ')' || c == 0;
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
int openp(char *s)
{
    return s[0] == '(';
}
int closep(char *s)
{
    return s[0] == ')';
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
int is_op(char *s)
{
    return sub(s) || add(s) || isdiv(s) || mul(s);
}
int isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
};

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

int read(char *filename, char op[50000][50])
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

        if (paren(c) || isop(c))
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
                if (paren(c) || isop(c))
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
    return i;
}

int prec(char *a, char *b)
{
    int an, bn;
    if (add(a) || sub(a))
        an = 2;
    else if (mul(a) || isdiv(a))
        an = 3;

    if (add(b) || sub(b))
        bn = 2;
    else if (mul(b) || isdiv(b))
        bn = 3;

    if (openp(a) || openp(b))
        return 0;
    if (an == bn || an > bn)
        return 1;
    return 0;
}

double do_op(double a, char *op, double b)
{
    if (add(op))
        return a + b;
    if (sub(op))
        return a - b;
    if (mul(op))
        return a * b;
    if (isdiv(op))
    {
        if (b == 0)
            error_out("no division by zero");
        return a / b;
    }
}

double expression(char op[5000][50], int l)
{
    double operand[2500];
    char operator[2500][50];
    int i,
        sn = -1, //counter for operands
        st = -1; //counter for operators
    for (i = 0; i < l; i++)
    {
        if (openp(op[i]))
        {
            st++;
            operator[st][0] = '(';
        }
        else if (is_op(op[i]))
        {
            if (st < 0)
            {
                st++;
                copy(operator[st], op[i]);
            }
            else
            {

                while (!openp(operator[st]) && prec(operator[st], op[i]))
                {
                    if (sn < 1)
                        error_out("operand stack underflow");
                    operand[sn - 1] = do_op(operand[sn - 1],
                                            operator[st],
                                            operand[sn]);
                    sn--;
                    st--;
                }
                st++;
                copy(operator[st], op[i]);
            }
        }
        else if (closep(op[i]))
        {
            while (!openp(operator[st]))
            {
                if (st < 0)
                    error_out("mismatched parens");
                if (sn < 1)
                    error_out("operand stack underflow");
                operand[sn - 1] = do_op(operand[sn - 1],
                                        operator[st],
                                        operand[sn]);
                sn--;
                st--;
            }
            st--;
        }
        else
        {
            sn++;
            operand[sn] = convert_num(op[i]);
        }
    }
    for (st = st; st >= 0; st--)
    {
        if (sn < 1)
            error_out("operand stack underflow");
        if (paren(operator[st][0]))
            error_out("mismatched parens");
        operand[sn - 1] = do_op(operand[sn - 1],
                                operator[st],
                                operand[sn]);
        sn--;
    }
    return operand[0];
}

int main(int argc, char **argv)
{
    argc--;
    char op[5000][50];
    int i, l;
    char filename[20];
    if (argc == 0)
    {
        printf("No filename specified. Please provide one: ");
        scanf(" %s", filename);
        argv[1] = filename;
        argc++;
    }

    double ans[2];

    for (i = 0; i < argc; i++)
    {
        l = read(argv[i + 1], op);
        printop(op);
        printf("%lf\n", expression(op, l));
    }
}
