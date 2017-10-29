
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_this_fool(char list[10][100], int num_of_elements);
void print_sorted_list(char list[10][100], int num_of_elements);
void make_lower(char* word);
void time_to_use_qsort(char* list[10], int num_of_elements);

int main(int argc, char* argv[]){
  if(argc == 1){
    printf("This program expects arguments...\n");
    exit(0);
  }
  else if(argc > 11){
    printf("Stop smashing my stack yo\n");
    exit(0);
  }

  char word_list[10][100];

  for(int i = 0; i < argc - 1; i++){
    strcpy(word_list[i], argv[i+1]);
    printf("we have scanned in: %s\n", word_list[i]);
  }

  sort_this_fool(word_list, argc - 1);
  print_sorted_list(word_list, argc - 1);
}

void sort_this_fool(char word_list[10][100], int num_of_elements){ 
  int ordered_list[10];
  char temp[10];
  
  for (int i = 0; i < num_of_elements; i++) {
    make_lower(word_list[i]);
    for (int j = 0; j < num_of_elements - 1; j++) {
      make_lower(word_list[j]);

      // this condition checks for less than equality
      if (strcmp(word_list[j], word_list[j + 1]) > 0) {
        strcpy(temp, word_list[j]);
        strcpy(word_list[j], word_list[j + 1]);
        strcpy(word_list[j + 1], temp);
      }
    }
  }
}

void print_sorted_list(char list[10][100], int num_of_elements){
  for(int i = 0; i < num_of_elements; ++i){
    printf("[%d] - %s\n", i, list[i]);
  }
}

void make_lower(char* word){
  for(int i = 0; i < strlen(word); ++i){
    if(word[i] > 64 && word[i] < 90)
      word[i] = word[i] + 32;
  }
}
