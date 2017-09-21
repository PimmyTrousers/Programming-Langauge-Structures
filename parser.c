#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_it_a_decimal(double* result, char input_number[100]);

int main(int argc, char* argv[]){
  double number;
  char input_number[100];
  int result = 1;

  scanf("%s", input_number);

  result = is_it_a_decimal(&number, input_number);

  if(result){
    printf("the input is %lf\n", number);
  }
  else{
    printf("what you inputted is not a number\n");
  }
}

int is_it_a_decimal(double* result, char input_number[100]){
  int period_flag = 0;
  int letter_flag = 0;
  int number_flag = 0;
  int special_flag = 0;
  int total_number_length = 0;

  for(int i = 0; input_number[i] != 0; ++i){
    if(input_number[i] == 46){
      period_flag = 1;
    }

    if(input_number[i] > 64 && input_number[i] < 97){
      letter_flag = 1;
      return 0;
    }

    if(input_number[i] > 96 && input_number[i] < 123){
      letter_flag = 1;
      return 0;
    }

    if(input_number[i] > 47 && input_number[i] < 58){
      number_flag = 1;
    }
    if(input_number[i] > 32 && input_number[i] < 46){
      special_flag = 1;
      return 0;
    }
    total_number_length = i;
  }
  if(period_flag && number_flag){
    int numbercount = 0;
    while(input_number[numbercount] != '.'){
      numbercount++;
    }

    double multiplier = 1;
    for(int i = numbercount - 1; i != -1; i--){
      *result = (input_number[i] -'0')*multiplier + *result;
      multiplier = multiplier * 10;
    }

    multiplier = 1;
    for(int i = numbercount+1; i != total_number_length+1; i++){
      multiplier = multiplier / 10;
      *result = (input_number[i]-'0')*multiplier + *result;
    }
    return 1;
  }

  return 0;
}
