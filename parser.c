#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_it_a_decimal(double* result, char input_number[100]);
int read_and_calculate_equation(double* result, char input_equation[100]);
int main(int argc, char* argv[]){
  double number;
  char input_equation[100];
  int result = 1;
  FILE* file_pointer;

  if(argc == 1){
    printf("this program takes in a file as an arguement\n");
    exit(0);
  }
  file_pointer = fopen(argv[1], "r");
  if(file_pointer == NULL){
    printf("something went wrong...");
    exit(0);
  }

  /* while(fscanf(file_pointer, "%c", input_equation) == 1){ */

  /* } */

  
  char input_equation2[100] = "34 + 96 - 10 / 2";
  read_and_calculate_equation(&number, input_equation2);

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

  // This is for doubles 
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

  // This is for integers
  if(number_flag){
    double multiplier = 1;
    for(int i = total_number_length; i != -1; i--){
      *result = (input_number[i]-'0')*multiplier + *result;
      multiplier = multiplier * 10;
    }
    return 1;
  }
  return 0;
}

int read_and_calculate_equation(double* result, char input_equation[100]){
  char temp_number[10];
  int temp_counter = 0;
  double temp_result = 0;
  double total_result = 0;
  int status_code = 1;

  for(int i = 0; input_equation[i] != '\0'; ++i){
    printf("currently looking at %c\n", input_equation[i]);
    if(input_equation[i] == '+'){
      printf("temp_number is %s\n", temp_number);
      status_code = is_it_a_decimal(&temp_result, temp_number);
      printf("the result from is it a decimal is %lf\n", *result);
      if(status_code == 0){
        printf("The equation you entered is wrong\n");
        //exit(0);
      }
      for(int j = 0; j < 10; j++){
        temp_number[j] = 0;
      }
    }
      if(input_equation[i] == '-'){
        printf("temp");
      }
    temp_number[temp_counter] = input_equation[i];
  }
  
}
