#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

double stack[10000];
int size = 0;
FILE *input_file;

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

void stack_underflow() {
    printf("Stack underflow error in \"add\" \n");
    exit(0);
}

int check_and_execute(char *w)
{
    char t[1];
    double tstack[10000];
    int tempSize = 0, tempIndex = 0, tempRollSize = 0, tempRollAmount = 0, c, n;
    double tempStack = 0;
    //add--------------------------------------------------------
    if (strcmp("add", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        stack[size - 2] = stack[size - 2] + stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //sub--------------------------------------------------------
    if (strcmp("sub", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        stack[size - 2] = stack[size - 2] - stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //mul--------------------------------------------------------
    if (strcmp("mul", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        stack[size - 2] = stack[size - 2] * stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //div--------------------------------------------------------
    if (strcmp("div", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        stack[size - 2] = stack[size - 2] / stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //idiv--------------------------------------------------------
    if (strcmp("idiv", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }

        stack[size - 2] = (int)stack[size - 2] / (int)stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //mod--------------------------------------------------------
    if (strcmp("mod", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }

        stack[size - 2] = (int)stack[size - 2] % (int)stack[size - 1];
        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //sqrt--------------------------------------------------------
    if (strcmp("sqrt", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }

        stack[size - 1] = sqrt(stack[size - 1]);
        return 1;
    }

    //sin--------------------------------------------------------
    if (strcmp("sin", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }

        stack[size - 1] = sin(stack[size - 1]);
        return 1;
    }

    //cos--------------------------------------------------------
    if (strcmp("cos", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }

        stack[size - 1] = cos(stack[size - 1]);
        return 1;
    }

    //pstack-----------------------------------------------------
    if (strcmp("pstack", w) == 0)
    {
        for (tempSize = 0; tempSize < size; tempSize++)
        {
            printf("%lf\n", stack[tempSize]);
        }
        printf("\n");
        return 1;
    }

    //dup--------------------------------------------------------
    if (strcmp("dup", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }

        stack[size] = stack[size - 1];
        size++;
        return 1;
    }

    //exch--------------------------------------------------------
    if (strcmp("exch", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        tempStack = stack[size - 1];
        stack[size - 1] = stack[size - 2];
        stack[size - 2] = tempStack;
        return 1;
    }

    //pop--------------------------------------------------------
    if (strcmp("pop", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }

        stack[size - 1] = 0;
        size--;
        return 1;
    }

    //index--------------------------------------------------------
    if (strcmp("index", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }
        if (stack[size - 1] < 0 || stack[size - 1] >= size)
        {
            printf("Error in index: \n%lf is not a valid index on stack\n", stack[size - 1]);
            exit(0);
        }
        if (floor(stack[size - 1]) != stack[size - 1])
        {
            printf("Error in index: \n%lf is not a valid index on stack\n", stack[size - 1]);
            exit(0);
        }
        tempIndex = (int)stack[size - 1];
        size--;
        tempIndex = size - tempIndex - 1;
        stack[size] = stack[tempIndex];
        size++;
        return 1;
    }

    //roll--------------------------------------------------------
    if (strcmp("roll", w) == 0)
    {
        if (size < 2)
        {
            stack_underflow();
        }
        if (stack[size - 2] > size)
        {
            printf("Error in roll: \n%lf is not a valid size of stack\n", stack[size - 2]);
            exit(0);
        }
        if (floor(stack[size - 2]) != stack[size - 2])
        {
            printf("Error in roll: \n%lf is not a valid size of stack\n", stack[size - 1]);
            exit(0);
        }
        if (floor(stack[size - 1]) != stack[size - 1])
        {
            printf("Error in roll: \n%lf is not a valid amount to roll stack\n", stack[size - 1]);
            exit(0);
        }

        tempRollSize = (int)stack[size - 2];
        tempRollAmount = (int)stack[size - 1] % tempRollSize;
        // printf("%d \t %d \n",tempRollSize, tempRollAmount);
        n = 0;
        size = size - 2;
        tempSize = size;
        for (c = size - tempRollSize; c < size; c++)
        {
            tstack[n] = stack[c];
            n++;
        }
        for (c = 0; c < tempRollSize; c++)
        {
            tempSize = (tempRollAmount + tempRollSize + (((tempRollSize - tempRollAmount) * 2) - 1) - c) % tempRollSize;
            //    printf("%d \n",tempSize);
            stack[size - 1 - c] = tstack[tempSize];
        }
        return 1;
    }
    //copy--------------------------------------------------------
    if (strcmp("copy", w) == 0)
    {
        if (size < 1)
        {
            stack_underflow();
        }
        if (floor(stack[size - 1]) != stack[size - 1])
        {
            printf("Error in copy: \n%lf is not a valid size of stack\n", stack[size - 1]);
            exit(0);
        }
        if (floor(stack[size - 1]) >= size)
        {
            printf("Error in copy: \n%lf is larger than size of stack\n", stack[size - 1]);
            exit(0);
        }

        tempRollAmount = (int)stack[size - 1];
        size--;
        tempSize = size;
        for (c = tempSize - tempRollAmount; c < tempSize; c++)
        {
            stack[size] = stack[c];
            size++;
        }

        return 1;
    }

    //comment----------------------------------------------------
    if (w[0] == '%')
    {
        t[0] = '%';
        while (t[0] != '\n')
        {
            fscanf(input_file, "%c", t);
        }
        return 1;
    }

    if (isnum(w))
    {
        //  printf("it was a number");
        return 0;
    }

    printf("\"%s\" is not a valid command\n", w);
    exit(0);
    //   printf("%s is not a valid command", w);
    return 1;
}

int main(int argc, char **argv)
{
    char w[100];
    int n, c = 0, i = 0;
    ;

    input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("can't open file %s\n", argv[1]);
        exit(1);
    }

    while (1)
    {
        //  printf("here\n");
        n = fscanf(input_file, "%s", w);
        if (n != 1)
        {
            break;
        }
        if (check_and_execute(w));
        else
        {
            stack[size] = atof(w);
            size++;
        }
    }
}