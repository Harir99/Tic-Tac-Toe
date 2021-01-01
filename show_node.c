#include "ttt.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char const *argv[])
{   
    int i = 1;
    int index = 0;
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    while(i < argc){
        index = atoi(argv[i]);
        compute_score();
        print_node(htable[index]);
        i++;
    }
    if (htable[index].winner == 'X')  printf( "X has Won!\n" );
    else if (htable[index].winner == '-')  printf( "The game was a tie!\n" );
    else if(htable[index].winner == 'O') printf( "O has Won!\n" );
    return 0;
}
