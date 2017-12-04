#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXSYMBOLS 1000
int Num_symbols = 0;
char Symbol_table_identifier[MAXSYMBOLS][50];
double Symbol_table_definition[MAXSYMBOLS];

int init_Symbol_table()
{
  int i;
  for (i = 0; i < MAXSYMBOLS; i++)
  {
    Symbol_table_identifier[i][0] = '\0';
  }
  Num_symbols = 0;
}

int find(char *w)
{
  int i;

  for (i = 0; i < Num_symbols; i++)
  {
    if (strcmp(w, Symbol_table_identifier[i]) == 0)
    {
      return i;
    }
  }

  return -1;
}

int insert(char *w)
{
  if (Num_symbols >= MAXSYMBOLS)
  {
    printf("symbol table is full\n");
    exit(1);
  }
  strcpy(Symbol_table_identifier[Num_symbols], w);
  Num_symbols++;
  return Num_symbols - 1;
}

//----------------------------------------

int Pgm_marker = 0;
char Pgm[9000][50];

int read_program_file(FILE *fin)
{
  FILE *tmp;
  int q;

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

  tmp = fopen("temporary_junk8765", "r");
  if (tmp == NULL)
  {
    printf("can't open temp file\n");
    exit(1);
  }

  int n;
  char w[100];

  Pgm_marker = 0;
  while (1)
  {
    n = fscanf(tmp, "%s", w);
    if (n != 1)
    {
      break;
    }

    //    printf("the token is : %s\n",w) ;
    strcpy(Pgm[Pgm_marker++], w);
  }

  system("rm temporary_junk8765");
}

int print_program()
{
  int i;
  printf("\n");
  printf("===========================Pgm===============================\n");
  for (i = 0; i < Pgm_marker; i++)
  {
    printf("%d : %s\n", i, Pgm[i]);
  }
  printf("=============================================================\n");
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int OLDstr_to_decimal(char *str, double res[1])
// return 1 for yes, 0 for no
{
  int flag, i, sign, c, ans;

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

  ans = 0;
  while (str[i] != '\0')
  {
    c = str[i];
    if (('0' <= c) && (c <= '9'))
    {
      ans = ans * 10 + (c - '0');
    }
    else
    {
      flag = 0;
      break;
    }
    i++;
  }

  res[0] = sign * ans;
  return flag;
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

int pmark;
char token[100];
int next_token()
{
  pmark++;

  if (pmark >= Pgm_marker)
  {
    printf("end of program reached\n");
    exit(1);
  }

  strcpy(token, Pgm[pmark]);
}

double expression()
{
  int sig;
  double res[1];
  double a, b, c;
  int loc;

  next_token();

  if (str_to_decimal(token, res) == 1)
  {
    return res[0];
  }
  else if ((loc = find(token)) != -1)
  {
    return Symbol_table_definition[loc];
  }
  else if (strcmp(token, "(") == 0)
  {
    next_token();

    if (strcmp(token, "sqrt") == 0)
    {

      a = expression();
      c = sqrt(a);
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "square") == 0)
    {

      a = expression();
      c = a * a;
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "sin") == 0)
    {

      a = expression();
      c = sin(a);
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "cos") == 0)
    {

      a = expression();
      c = cos(a);
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "+") == 0)
    {

      a = expression();
      b = expression();
      c = a + b;
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "-") == 0)
    {

      a = expression();
      b = expression();
      c = a - b;
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "*") == 0)
    {

      a = expression();
      b = expression();
      c = a * b;
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "/") == 0)
    {

      a = expression();
      b = expression();
      c = a / b;
      next_token();
      if (strcmp(token, ")") == 0)
      {
        return c;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
    else if (strcmp(token, "define") == 0)
    {

      next_token();

      loc = find(token);
      if (loc == -1)
      {
        loc = insert(token);
      }

      a = expression();

      Symbol_table_definition[loc] = a;

      next_token();
      if (strcmp(token, ")") == 0)
      {
        return a;
      }
      else
      {
        printf("error : missing right paren\n");
      }
    }
  }
  else
  {

    printf("error : left paren expected\n");
    exit(1);
  }

} // end run_program

int main(int argc, char **argv)
{
  FILE *f;
  if (argc != 2)
  {
    printf("Usage : pgm   input_file.prefl\n");
    exit(1);
  }
  f = fopen(argv[1], "r");
  if (f == NULL)
  {
    printf("can't open file, %s\n", argv[1]);
    exit(1);
  }

  init_Symbol_table();
  //  int loc = insert("abc") ;
  //  Symbol_table_definition[loc] = 103 ;

  read_program_file(f);
  print_program();

  double e;
  pmark = -1;
  while (1)
  {
    e = expression();
    printf("expression = %lf\n", e);
  }
}
