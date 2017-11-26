#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char s[256];

int main(){
        strcpy(s, "one two three");
        char* token = strtok(s, " ");
        while (token) {
                printf("token: %s\n", token);
                token = strtok(NULL, " ");
        }
}
