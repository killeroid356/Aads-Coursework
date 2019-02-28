#include <stdio.h>
Board init_board(){
	Board b;
	return b;
	
}


int main(int argc, char **argv)
{
	struct Board{
		Row Positions[3];
		
	};
	struct Row{
		char row[3];
	};
	
	int boardsize = 3;
	int count = 0;
	printf("Welcome to Tic tac toe!\n");
	while(count != boardsize){
		for(int i = 2; i<boardsize; i++){
			printf("  |");
		}
		printf("  |\n");
		
		if(boardsize - count == 1){
			printf("\n\nStart Game!\n");
			
		}else{
			
			for(int i = 2; i<boardsize; i++)
			{
				printf("----");
			}
			printf("----\n");
		}
		count++;
	}
	Board b = init_board();
	
}