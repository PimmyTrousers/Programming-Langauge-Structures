
#include <stdio.h>
#include <stdlib.h>

int num_words = 5 ;
char word_list [10][100] = {
  "hello",
  "there",
  "how",
  "are",
  "you"
} ;


int main(int argc,  char **argv)
{
  char w[100] ;
  int i ;

  for (i = 0 ; i < num_words ; i++) {
    printf("%s\n",word_list[i]) ;
  }

  printf("enter word ") ;
  scanf("%s",w) ;

  for (i = 0 ; i < num_words ; i++) {
    if (strcmp(word_list[i], w) == 0) {
      break ;
    }
  }

  if (i < num_words) {
    printf("The word, %s, is in slot, %d.\n",w,i) ;
  } else {
    printf("The word, %s, is NOT in the list.\n",w) ;
  }

}
