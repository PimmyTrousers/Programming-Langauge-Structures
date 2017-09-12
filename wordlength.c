#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int basic_word_length(char *word);
size_t advanced_word_length(const char *word);


int main(int argc, char** argv){
  if(argc > 1){
    printf("I don't take any arguments...\n");
    exit(0);
  }

  char c[100];

  printf("enter your word: ");
  scanf("%s", c);
  int lettercount = basic_word_length(c);
  printf("after the basic word length we get , %d\n", lettercount);
  lettercount = advanced_word_length(c);
  printf("after the advanced word length we get, %d\n", lettercount);
  printf("standard strlen() is, %zu\n", strlen(c));
}


int basic_word_length(char *word){
  int i;
  for(i = 0;word[i] != 0; ++i);
  return i;
}


// The actual string length function from OpenBSD
size_t advanced_word_length(const char *word){
  const char *s;
  for (s = word; *s; ++s);
  return(s-word);
}
