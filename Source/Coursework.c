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

struct Replay{
	int numofmoves;
	struct Board States[9];
};

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

void play_replay(struct Replay r){
	for(int i = 0; i < r.numofmoves; i++){
		print_board(r.States[i]);
	}
	printf("\nEnd of replay\n");
}

bool check_victory(struct Board b, char *winner){
	bool won = false;
	for(int i = 0; i<3; i++){
		if (b.Positions[i].row[0] != ' ' && b.Positions[i].row[0] == b.Positions[i].row[1] && b.Positions[i].row[0] == b.Positions[i].row[2]){
			*winner = b.Positions[i].row[0];
			won = true;
		}
		else if(b.Positions[0].row[i] != ' ' && b.Positions[0].row[i] == b.Positions[1].row[i] && b.Positions[0].row[i] == b.Positions[2].row[i]){
			*winner = b.Positions[0].row[i];
			won = true;
		}
	}
	if(b.Positions[0].row[0] != ' ' && b.Positions[0].row[0] == b.Positions[1].row[1] && b.Positions[0].row[0] == b.Positions[2].row[2]){
		*winner = b.Positions[1].row[1];
		won = true;
	}else if(b.Positions[0].row[2] != ' ' && b.Positions[0].row[2] == b.Positions[1].row[1] && b.Positions[0].row[2] == b.Positions[2].row[0]){
		*winner = b.Positions[1].row[1];
		won = true;
	}
	
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
	int replaycount = 0;
	int viewnumber;
	char turn = 'X';
	char decicion;
	char winner = '-';
	bool valid = false;
	bool won = false;
	bool done = false;
	bool viewing = true;
	printf("Welcome to Tic tac toe!\n");
	struct Board b = init_board();
	struct Replay r;
	struct Replay List[20];
	while(!done){
		while(!won){
			while(!valid){
				print_board(b);
				row = 0;
				col = 0;
				printf("%c, your turn!\nrow:", turn);
				while(scanf("%d", &row)!= 1 ){
					printf("Invalid data\nrow:");
					getchar();
				}
				
				if (row > 3){valid = false;}
				printf("column:");
				while(scanf("%d", &col) !=1){
					printf("Invalid data\nrow:");
					getchar();
				}
				getchar();
				if (col > 3){valid = false;}
				if(b.Positions[col-1].row[row-1] != ' '){
					printf("error place already full\n");
				}else{
					b.Positions[col-1].row[row-1] = turn;
					valid = true;
				}
			}
			r.States[turncount] = b;
			won = check_victory(b, &winner);
			if(!won){valid = false;}
			turn = change_turn(turn);
			turncount++;
			if(turncount == 9 && !won){
				print_board(b);
				printf("Stalemate!\nPlay again or view replays? (y/n/r):");
				if(decicion == '\n'){scanf("%c", &decicion);} //clearing decision because bugs and stuff
				scanf("%c", &decicion);
				if(decicion == 'y'){
					if(replaycount<20){
						r.numofmoves = turncount;
						List[replaycount] = r;
						replaycount = replaycount + 1;
					} else{
						printf("Replay Storage full, please restart program if you want to save different replays\n");
					}
					turncount = 0;
					b = init_board();
					turn = 'X';
				}else if(decicion == 'r'){
					if(replaycount<20){
						r.numofmoves = turncount;
						List[replaycount] = r;
						replaycount = replaycount + 1;
					} else{
						printf("Replay Storage full, please restart program if you want to save different replays\n");
					}
					viewing = true;
					while(viewing){
						printf("\nEnter the number of replay to display: ");
						scanf("%d", &viewnumber);
						if(viewnumber-1 >= replaycount || viewnumber == 0){
							printf("Error, replay not found");
						}else{
							play_replay(List[viewnumber-1]);
						printf("Continue viewing replays? (y/n):");
						if(decicion == '\n'){scanf("%c", &decicion);} //clearing decision because bugs and stuff
						scanf("%c", &decicion);
						if(decicion == 'n'){viewing = false;}
						}
					}
					turncount = 0;
					b = init_board();
					turn = 'X';
				}else{
					won = true;
					done = true;
				}
			}
		}
		print_board(b);
		if(replaycount<20){
			r.numofmoves = turncount;
			List[replaycount] = r;
			replaycount = replaycount + 1;
		} else{
			printf("Replay Storage full, please restart program if you want to save different replays\n");
		}
		printf("%c is the winner!", winner);
		printf("\nPlay again or view replays? (y/n/r):");
		if(decicion == '\n'){scanf("%c", &decicion);} //clearing decision because bugs and stuff
		scanf("%c", &decicion);
		if(decicion == 'y'){
			turncount = 0;
			b = init_board();
			turn = 'X';
			won = false;
		}else if(decicion == 'r'){
			viewing = true;
			while(viewing){
				printf("\nEnter the number of replay to display: ");
				scanf("%d", &viewnumber);
				if(viewnumber-1 >= replaycount || viewnumber == 0){
					printf("Error, replay not found");
				}else{
					play_replay(List[viewnumber-1]);
					printf("Continue viewing replays? (y/n):");
					if(decicion == '\n'){scanf("%c", &decicion);} //clearing decision because bugs and stuff
					scanf("%c", &decicion);
					if(decicion == 'n'){viewing = false;}
				}
			}
			turncount = 0;
			b = init_board();
			turn = 'X';
			won = false;
		}else{
			done = true;
		}
	}
	
}