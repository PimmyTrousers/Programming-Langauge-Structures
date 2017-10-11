#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int is_it_a_decimal(double* result, char input_number[1000]);
void read_and_calculate_equation(double* result, char input_equation[1000]);
void REMOVETHEBULLSHIT(char* source);
void spacify_the_equation(char spacified_equation[1000], char input_equation[1000]);
int check_if_valid(char spacified_equation[1000]);


int main(int argc, char* argv[]){
  double number;
  char input_equation[1000][1000];
  char input_equation2[1000];
  char new_equation[1000];
  char spacified_equation[1000];
  int result = 1;
  int i = 0;
  int return_code;
  int total_counter;
  FILE* file_pointer;

  for(int i = 0; i < 100; i++){
    for(int j = 0; j < 1000; j++){
      input_equation[i][j] = 0;
    }
  }

  for(int i = 0; i < 1000; i++){
    input_equation2[i] = 0;
  }

  if(argc == 1){
    printf("this program takes in a file as an arguement\n");
    exit(0);
  }
  file_pointer = fopen(argv[1], "r");
  if(file_pointer == NULL){
    printf("something went wrong...");
    exit(0);
  }

  for(int wordcount = 0;fscanf(file_pointer, "%s", input_equation2) == 1;wordcount++){
    strcpy(input_equation[i], input_equation2);
    i++;
  }

  int stop = i;

  for(int i = 0; i < stop; i++){
    for(int j = 0; input_equation[i][j] != '\0'; j++){
      new_equation[total_counter] = input_equation[i][j];
      total_counter++;
    }
  }

  spacify_the_equation(spacified_equation,new_equation);
  if(!check_if_valid(spacified_equation)){
    printf("\n THE EQUATION WAS: %s\n", spacified_equation);
    printf(" this equation is invalid\n\n");
    exit(0);
  }
  read_and_calculate_equation(&number, spacified_equation);

  // read_and_calculate_equation(&number, input_equation2);
  printf("\n THE EQUATION WAS: %s\n THE ANSWER IS: %lf\n\n", spacified_equation, number);

}

int is_it_a_decimal(double* result, char input_number[1000]){
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

void read_and_calculate_equation(double* result, char input_equation[1000]){
  char temp_number[10];

  for(int i = 0; i < 10; i++){
    temp_number[i] = 0;
  }

  int temp_counter = 0;
  double temp_result = 0;
  double total_result = 0;
  int status_code = 1;
  int i;
  int space_count = 0;
  int number_flag = 0;
  int start_flag = 0;

  // checks for the first number (the input string must start with a number)
  for(i = 0; input_equation[i] != ' '; i++){
    temp_number[i] = input_equation[i];
  }

  // defines the number from a string and adds it to the total to return
  is_it_a_decimal(&temp_result, temp_number);
  total_result += temp_result;
  temp_result = 0;

  // printf("[DEBUG] after the first number the total is %lf\n", total_result);

  for(int i = 0; i < 10; i++){
    temp_number[i] = 0;
  }

  for(i = i; input_equation[i] != '\0'; ++i){
    // printf("input_equation[i] is %c\n", input_equation[i]);

    // checks for addition
    if(input_equation[i] == '+'){
      number_flag = 0;
      start_flag = 1;
      // printf("[DEBUG] found operator +\n");
      temp_counter = 0;

      //VERY BIZARRE CODE THAT CHECKS FOR THE NUMBER AHEAD
      for(i = i; space_count != 2; i++){
        temp_number[temp_counter] = input_equation[i];
        if(input_equation[i] > 47 && input_equation[i] < 58){
          number_flag = 1;
        }

        if(input_equation[i] == ' '){
          space_count++;
        }
        temp_counter++;
      }



      space_count = 0;
      REMOVETHEBULLSHIT(temp_number);
      // printf("[DEBUG] temp number is \"%s\"\n", temp_number);
      status_code = is_it_a_decimal(&temp_result, temp_number);
      total_result += temp_result;
      temp_result = 0;
      // printf("[DEBUG] total result is %lf\n", total_result);
      for(int j = 0; j < 10; j++){
        temp_number[j] = 0;
      }
      temp_counter = 0;
      i = i - 1;
    }

    // checks for negation
    if(input_equation[i] == '-'){
      number_flag = 0;
      start_flag = 1;
      // printf("[DEBUG] found operator -\n");
      temp_counter = 0;

      //VERY BIZARRE CODE THAT CHECKS FOR THE NUMBER AHEAD
      for(i = i; space_count != 2; i++){
        temp_number[temp_counter] = input_equation[i];
        if(input_equation[i] > 47 && input_equation[i] < 58){
          number_flag = 1;
        }
        if(input_equation[i] == ' '){
          space_count++;
        }
        temp_counter++;
      }

      space_count = 0;
      REMOVETHEBULLSHIT(temp_number);
      // printf("[DEBUG] temp number is \"%s\"\n", temp_number);
      status_code = is_it_a_decimal(&temp_result, temp_number);
      total_result -= temp_result;
      temp_result = 0;
      // printf("[DEBUG] total result is %lf\n", total_result);
      for(int j = 0; j < 10; j++){
        temp_number[j] = 0;
      }
      temp_counter = 0;
      i = i -1;
    }

    //checks for division
    if(input_equation[i] == '/'){
      number_flag = 0;
      start_flag = 1;
      // printf("[DEBUG] found operator /\n");
      temp_counter = 0;

      //VERY BIZARRE CODE THAT CHECKS FOR THE NUMBER AHEAD
      for(i = i; space_count != 2; i++){
        temp_number[temp_counter] = input_equation[i];
        if(input_equation[i] > 47 && input_equation[i] < 58){
          number_flag = 1;
        }
        if(input_equation[i] == ' '){
          space_count++;
        }
        temp_counter++;
      }

      space_count = 0;
      REMOVETHEBULLSHIT(temp_number);
      // printf("[DEBUG] temp number is \"%s\"\n", temp_number);
      status_code = is_it_a_decimal(&temp_result, temp_number);
      total_result /=  temp_result;
      temp_result = 0;
      // printf("[DEBUG] total result is %lf\n", total_result);
      for(int j = 0; j < 10; j++){
        temp_number[j] = 0;
      }
      temp_counter = 0;
      i = i - 1;
    }

    // checks for multiplication
    if(input_equation[i] == '*'){
      number_flag = 0;
      start_flag = 1;
      // printf("[DEBUG] found operator *\n");
      temp_counter = 0;

      //VERY BIZARRE CODE THAT CHECKS FOR THE NUMBER AHEAD
      for(i = i; space_count != 2; i++){
        temp_number[temp_counter] = input_equation[i];
        if(input_equation[i] > 47 && input_equation[i] < 58){
          number_flag = 1;
        }
        if(input_equation[i] == ' '){
          space_count++;
        }
        temp_counter++;
      }

      space_count = 0;
      REMOVETHEBULLSHIT(temp_number);
      // printf("[DEBUG] temp number is \"%s\"\n", temp_number);
      status_code = is_it_a_decimal(&temp_result, temp_number);
      total_result *= temp_result;
      temp_result = 0;
      // printf("[DEBUG] total result is %lf\n", total_result);
      for(int j = 0; j < 10; j++){
        temp_number[j] = 0;
      }
      temp_counter = 0;
      i = i - 1;
    }
    if(number_flag == 0 && start_flag == 1){
      printf("\n THE EQUATION WAS: %s\n", input_equation);
      printf(" this equation is invalid\n\n");
      exit(0);
    }
    temp_counter++;

  }
  *result = total_result;
}

void REMOVETHEBULLSHIT(char* source){
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ' && *i != '+' && *i != '-' && *i != '/' && *i != '*')
      i++;
  }
  *i = 0;
}

void spacify_the_equation(char spacified_equation[1000], char input_equation[1000]){
  int flag = 0;
  int count = 0;



  for(int i = 0; input_equation[i] != '\0'; i++){
    flag = 0;
    if(input_equation[i] == '+'){
      spacified_equation[count] = ' ';
      count++;
      spacified_equation[count] = '+';
      count++;
      spacified_equation[count] = ' ';
      count++;
      flag = 1;

    }
    if(input_equation[i] == '-'){
      spacified_equation[count] = ' ';
      count++;
      spacified_equation[count] = '-';
      count++;
      spacified_equation[count] = ' ';
      count++;
      flag = 1;
    }
    if(input_equation[i] == '/'){
      spacified_equation[count] = ' ';
      count++;
      spacified_equation[count] = '/';
      count++;
      spacified_equation[count] = ' ';
      count++;
      flag = 1;
    }
    if(input_equation[i] == '*'){
      spacified_equation[count] = ' ';
      count++;
      spacified_equation[count] = '*';
      count++;
      spacified_equation[count] = ' ';
      count++;
      flag = 1;
    }
    if(flag == 0){
      spacified_equation[count] = input_equation[i];
      count++;
    }
  }
  spacified_equation[count] = ' ';
}

int check_if_valid(char spacified_equation[1000]){
  for(int i = 0; spacified_equation[i] != '\0'; i++){
    if(spacified_equation[i] > 64 && spacified_equation[i] < 97){
      return 0;
    }

    if(spacified_equation[i] > 96 && spacified_equation[i] < 123){
      return 0;
    }

    if(spacified_equation[i] == '.' && spacified_equation[i+1] == '.'){
      return 0;
    }
  }
  return 1;
}
