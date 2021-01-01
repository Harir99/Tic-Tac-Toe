#include "ttt.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{   
    int i = 1;
    int index = 0;
    int count = 0;
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
   for ( i = 0; i < HSIZE; i++){
        if(htable[i].init == 1){
            count++;
        }
   }
    printf("%d\n",count);

    return 0;
}
