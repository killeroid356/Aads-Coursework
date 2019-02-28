#include <stdio.h>
#include <stdbool.h>

struct Row{
	char row[3];
};

struct Board{
	struct Row Positions[3];	
};
struct Board init_board(){
	struct Board b;
	
	for(int i = 0; i<3; i++){
		for (int j = 0; j<3; j++){
			b.Positions[i].row[j]=' ';
		}
	}
	return b;
	
}
void print_board(struct Board b){
	int boardsize = 3;
	int count = 0;
	while(count != boardsize){
		for(int i = 0; i<boardsize-1; i++){
			printf(" %c|", b.Positions[i].row[count]);
		}
		printf(" %c\n",b.Positions[2].row[count]);
		if(boardsize - count == 1){
			printf("\n\nBoard Updated\n");
		}else{
			for(int i = 0; i<boardsize-1; i++)
			{
				printf("---");
			}
			printf("---\n");
		}
		count++;
	}
	
	
}

bool check_victory(struct Board b){
	bool won = false;
	
	
	return won;
}
char change_turn(char turn){
	if(turn == 'X'){
		turn = 'O';
	}else{
		turn = 'X';
	}
	return turn;
}
int main(int argc, char **argv)
{
	int row;
	int col;
	int turncount = 0;
	char turn = 'X';
	bool valid = false;
	bool won = false;
	printf("Welcome to Tic tac toe!\n");
	struct Board b = init_board();
	print_board(b);
	while(!won){
		while(!valid){
			printf("%c, your turn!\nrow:", turn);
			scanf("%d", &row);
			printf("column:");
			scanf("%d", &col);
			if(b.Positions[col-1].row[row-1] != ' '){
				printf("error place already full\n");
			}else{
				b.Positions[col-1].row[row-1] = turn;
				valid = true;
			}
			print_board(b);
		}
	won = check_victory(b);
	valid = false;
	turn = change_turn(turn);
	turncount++;
	if(turncount == 9){
		
		printf("Stalemate!\nPlay again? (y/n):");
		char decicion;
		scanf("%c", &decicion);
		if(decicion == 'y'){
			turncount = 0;
			b = init_board();
		}else{
			won = true;
		}
	}
	}
}