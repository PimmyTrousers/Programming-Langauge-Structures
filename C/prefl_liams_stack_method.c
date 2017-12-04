/*
  Liam Beveridge's idea is to have a stack
  of operators and a stack of numbers.
  When a right paren is encountered, use
  the operator on the top of the operator
  stack to operate on the numbers on 
  the top of the number stack.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int jexit(int n)
{
  system("rm temporary_junk8765");
  exit(n);
}

int str_to_decimal(char *str, double res[1])
// return 1 for yes, 0 for no
// this deals with decimal points
{
  int flag, i, sign, c;
  double ans;

  flag = 1;

  if (str[0] == '-')
  {
    i = 1;
    sign = -1;
  }
  else
  {
    i = 0;
    sign = 1;
  }

  double tenpow = 1;
  int numdpoints = 0; // number of decimal points in string
  ans = 0;
  while (1)
  {
    c = str[i];

    if (c == '\0')
    {
      break;
    }
    else if (c == '.')
    {
      numdpoints++;
      if (numdpoints > 1)
      {
        flag = 0;
        break;
      }
    }
    else if (('0' <= c) && (c <= '9'))
    {
      if (numdpoints == 0)
      {
        ans = ans * 10 + (c - '0');
      }
      else
      {
        tenpow *= 10;
        ans = ans + (c - '0') / tenpow;
      }
    }
    else
    {
      flag = 0;
      break;
    }

    i++;
  } // end while (1)

  res[0] = sign * ans;
  return flag;
}

int Osp = -1;
char Ostack[1000][30];
int Opush(char *w)
{
  Osp++;
  if (Osp >= 1000)
  {
    printf("Operator stack overflow\n");
    jexit(0);
  }
  strcpy(Ostack[Osp], w);
}

int Opop(char *w)
{
  if (Osp < 0)
  {
    printf("Operator stack underflow\n");
    jexit(0);
  }
  else
  {
    strcpy(w, Ostack[Osp]);
  }
  Osp--;
}

int print_Ostack()
{
  int i;
  printf("++++++++++++++++++++++\n");
  for (i = 0; i <= Osp; i++)
  {
    printf("%s\n", Ostack[i]);
  }
  printf("----------------------\n");
}

int Nsp = -1;
double Nstack[1000];
int Npush(double w)
{
  Nsp++;
  if (Nsp >= 1000)
  {
    printf("Number stack overflow\n");
    jexit(0);
  }
  Nstack[Nsp] = w;
}

double Npop()
{
  double w;
  if (Nsp < 0)
  {
    printf("Numbers stack underflow\n");
    jexit(0);
  }
  else
  {
    w = Nstack[Nsp];
  }
  Nsp--;
  return w;
}

int print_Nstack()
{
  int i;
  printf("++++++++++++++++++++++\n");
  for (i = 0; i <= Nsp; i++)
  {
    printf("%lf\n", Nstack[i]);
  }
  printf("----------------------\n");
}

int main(int argc, char **argv)
{
  FILE *fin, *tmp;
  int q;

  if (argc != 2)
  {
    printf("Usage : pgm inputfile\n");
    exit(1);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL)
  {
    printf("can't open file %s\n", argv[1]);
    exit(1);
  }

  tmp = fopen("temporary_junk8765", "w");
  if (tmp == NULL)
  {
    printf("can't open temp file\n");
    exit(1);
  }

  q = fgetc(fin);
  while (q != EOF)
  {
    if ((q == '(') || (q == ')'))
    {
      fputc(' ', tmp);
      fputc(q, tmp);
      fputc(' ', tmp);
    }
    else
    {
      fputc(q, tmp);
    }
    q = fgetc(fin);
  }

  fclose(fin);
  fclose(tmp);

  // ------------------------------------------

  /*
  tmp = fopen("temporary_junk8765", "r") ;
  if (tmp == NULL) {
    printf("can't open temp file\n") ;
    exit(1) ;
  }

  int n ;
  char w[100] ;
  while (1) {
    n = fscanf(tmp,"%s",w) ;
    if (n != 1) { break ; }
    printf("the token is : %s\n",w) ;
  }

  system("rm temporary_junk8765") ;
  */

  // ------------------------------------------

  tmp = fopen("temporary_junk8765", "r");
  if (tmp == NULL)
  {
    printf("can't open temp file\n");
    exit(1);
  }

  int n;
  char w[100];
  double v, v1, v2;
  int sig;
  char operator[20];

  Osp = -1;
  Nsp = -1; // initialize stacks

  while (1)
  {

    //    print_Ostack() ;

    n = fscanf(tmp, "%s", w);
    if (n != 1)
    {
      break;
    }
    //    printf("the token is : %s\n",w) ;

    sig = str_to_decimal(w, &v);
    if (sig == 1)
    {

      Npush(v);
    }
    else if (strcmp(w, "(") == 0)
    {

      n = fscanf(tmp, "%s", w);
      if (n != 1)
      {
        break;
      }
      //  printf("the token is : %s\n",w) ;
      if (strcmp(w, "+") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "-") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "*") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "/") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "square") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "sqrt") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "sin") == 0)
      {
        Opush(w);
      }
      else if (strcmp(w, "cos") == 0)
      {
        Opush(w);
      }
      else
      {
        printf("unrecognized operator(A) = %s\n", w);
        jexit(0);
      }
    }
    else if (strcmp(w, ")") == 0)
    {
      /*
      printf("rparen encountered : \n") ;
      print_Ostack() ;
      print_Nstack() ;
      */

      Opop(operator);
      if (strcmp(operator, "+") == 0)
      {
        v2 = Npop();
        v1 = Npop();
        v = v1 + v2;
        Npush(v);
      }
      else if (strcmp(operator, "-") == 0)
      {
        v2 = Npop();
        v1 = Npop();
        v = v1 - v2;
        Npush(v);
      }
      else if (strcmp(operator, "*") == 0)
      {
        v2 = Npop();
        v1 = Npop();
        v = v1 * v2;
        Npush(v);
      }
      else if (strcmp(operator, "/") == 0)
      {
        v2 = Npop();
        v1 = Npop();
        v = v1 / v2;
        Npush(v);
      }
      else if (strcmp(operator, "square") == 0)
      {
        v1 = Npop();
        v = v1 * v1;
        Npush(v);
      }
      else if (strcmp(operator, "sqrt") == 0)
      {
        v1 = Npop();
        v = sqrt(v1);
        Npush(v);
      }
      else if (strcmp(operator, "sin") == 0)
      {
        v1 = Npop();
        v = sin(v1);
        Npush(v);
      }
      else if (strcmp(operator, "cos") == 0)
      {
        v1 = Npop();
        v = cos(v1);
        Npush(v);
      }
      else
      {
        printf("unrecognized operator (B) = %s\n", operator);
      }
    }
    else
    {
      printf("unrecognized symbol = %s\n", w);
      jexit(0);
    }

  } // end outer while (1)

  v = Npop();

  if (Nsp != -1)
  {
    printf("error : Numeric stack not empty as it should be :\n");
    print_Nstack();
    jexit(0);
  }

  if (Osp != -1)
  {
    printf("error : Operator stack not empty as it should be :\n");
    print_Ostack();
    jexit(0);
  }

  printf("Expression Accepted : value = %lf\n", v);

  system("rm temporary_junk8765");
}
