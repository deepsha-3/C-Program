#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int distance;
    char direction[5];

    scanf("%d%s",&distance,direction);
   
    if(strcmp(direction, "south")) {
        printf("look north\n");
        printf("shoot\n");
    }else if(strcmp(direction, "north")){
        printf("look south\n");
        printf("shoot\n");   
    }else if(strcmp(direction, "west")){
        printf("look east\n");
        printf("shoot\n");   
    }else if(strcmp(direction, "east")){
        printf("look west\n");
        printf("shoot\n");   
    }
    return 0;

}