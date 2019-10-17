#include <stdlib.h>        
#include <stdio.h>
#include <unistd.h>

void intro();
void menu();
void gameover(int score);
void movement(int *snakeX, int *snakeY, int input, int snakeSize, int *head, int *tail, int *wActive, int *aActive, int *sActive, int *dActive, int *Bmovement);
void headTail(int *head,int *tail, int snakeSize);
void collision(int *snakeX, int *snakeY, int *snakeSize, int *fruitX, int *fruitY, int *tail, int *head, int *game);

int main() {
	//default grid size
	int gridSize=10;
	char grid[gridSize][gridSize];
	
	//default input 
	char input='X';
	
	//snake
	int snakeX[99]={};
	int snakeY[99]={};
	int snakeSize=1;
	snakeX[0]=2;
	snakeY[0]=2;
	int head=0;
	int tail=0;
	
	//fruit
	int fruitX = 4;
	int fruitY = 4;
	
	//boolean false/true
	int snake=0;
	int fruit=0;
	int Bmovement=0;
	//checks that next button push is not opposite direction from last button push
	int wActive=0;
	int aActive=0;
	int sActive=0;
	int dActive=0;
	
	//switch mode
	int game=0;
	
	intro();
	while(game<5){
		switch(game){
			case 0:
				menu();
				int test=0;
				do{
					input = getch();
					input = toupper((int)input);
				} while(input-48 < 1 || input-48 > 2);
				game = input-48;
				break;
			case 1:
				do{
					if(game==1){
						input = getch();
						input = toupper((int)input);
						system("cls");
						movement(snakeX,snakeY,input,snakeSize, &head, &tail, &wActive, &aActive, &sActive, &dActive, &Bmovement);
						if(Bmovement==1){
							collision(snakeX,snakeY,&snakeSize,&fruitX,&fruitY, &tail, &head, &game);
							headTail(&head,&tail, snakeSize);
						}
						//grid ReCreate
						for(int i=0;i<gridSize;i++){
							for(int t=0;t<gridSize;t++){
								snake=0;
								fruit=0;
								for(int p=0;p<snakeSize;p++){
									if(t==snakeX[p] && i==snakeY[p]){	
										grid[i][t]='X';
										snake=1;
										break;
									}
								}
								if(fruitX==t && fruitY==i){
									grid[i][t]='A';
									fruit=1;
								}
								if(snake==0 && fruit==0){
									grid[i][t]='-';
								}
							}
						}
						for(int i=0;i<gridSize;i++){
							for(int t=0;t<gridSize;t++){
								printf(" %c ",grid[i][t]);
							}
							printf("\n");
						}
						Bmovement=0;
					}
				} while(game == 1);
				gameover(snakeSize);
				sleep(3);
				game=0;
			case 2:
				game=5;
		}
	}
}

void intro(){
		printf("||===================================|| \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||             WELCOME TO            || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||===================================|| \n");
		sleep(3);
		system("cls");
		printf("||===================================|| \n");
		printf("|| ||===| ||   || ||==|| || // ||=== || \n");
		printf("|| ||     ||   || ||  || ||//  ||    || \n");
		printf("|| ||===| ||\\  || ||==|| ||\\   ||=== || \n");
		printf("||     || || \\ || ||  || || \\  ||    || \n");
		printf("|| |===|| ||  \\|| ||  || ||  \\ ||=== || \n");
		printf("||                2018               || \n");
		printf("||===================================|| \n");
		sleep(3);
		system("cls");
		printf("||===================================|| \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||                 BY                || \n");
		printf("||           VILLE LAUKKOSKI         || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||===================================|| \n");
		sleep(3);
}
void menu(){
		system("cls");
		printf("||===================================|| \n");
		printf("||                                   || \n");
		printf("||               MENU                || \n");
		printf("||          1) PLAY GAME             || \n");
		printf("||          2) EXIT                  || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||===================================|| \n");
}
void gameover(int score){
		system("cls");
		printf("||===================================|| \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||             GAME OVER             || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||===================================|| \n");
		sleep(3);
		system("cls");
		printf("||===================================|| \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		if(score<10){
			printf("||             Score: 0%d             || \n",score);
		} else {
			printf("||             Score: %d             || \n",score);
		}
		printf("||            START AGAIN?           || \n");
		printf("||                                   || \n");
		printf("||                                   || \n");
		printf("||===================================|| \n");
}
void movement(int *snakeX, int *snakeY, int input, int snakeSize, int *head, int *tail, int *wActive, int *aActive, int *sActive, int *dActive, int *Bmovement){
	//Going up (W)
	if (input==87 && *sActive==0){
		*Bmovement=1;
		if(snakeY[*head]!=0){                                      
			snakeY[*tail]=snakeY[*head]-1;
		} else{
			snakeY[*tail]=9;
		}
		snakeX[*tail]=snakeX[*head];
		//active button
		*wActive=1;
		*aActive=0;
		*sActive=0;
		*dActive=0;
	}
	//Going down (S)
	if (input==83 && *wActive==0){
		*Bmovement=1;
		if(snakeY[*head]!=9){
			snakeY[*tail]=snakeY[*head]+1;
		} else{
			snakeY[*tail]=0;
		}
		snakeX[*tail]=snakeX[*head];
		//active button
		*wActive=0;
		*aActive=0;
		*sActive=1;
		*dActive=0;
	}
	//Going left (A)
	if (input==65 && *dActive==0){
		*Bmovement=1;
		if(snakeX[*head]!=0){
			snakeX[*tail]=snakeX[*head]-1;
		} else{
			snakeX[*tail]=9;
		}
		snakeY[*tail]=snakeY[*head];
		//active button
		*wActive=0;
		*aActive=1;
		*sActive=0;
		*dActive=0;
	}
	//Going right (D)
	if (input==68 && *aActive==0){
		*Bmovement=1;
		if(snakeX[*head]!=9){
			snakeX[*tail]=snakeX[*head]+1;
		} else {
			snakeX[*tail]=0;
		}
		snakeY[*tail]=snakeY[*head];
		//active button
		*wActive=0;
		*aActive=0;
		*sActive=0;
		*dActive=1;
	}
}
//main mission to move tail and head values
void headTail(int *head,int *tail, int snakeSize){
	if(*head<snakeSize-1){
		*head=*head+1;
	} else{
		*head=0;
	}
	if(*tail<snakeSize-1){
		*tail=*tail+1;
	} else{
		*tail=0;
	}
}
void collision(int *snakeX, int *snakeY, int *snakeSize, int *fruitX, int *fruitY, int *tail, int *head, int *game){
	//self & fruit collision while snake is bigger than 1 block
	if(*snakeSize!=1){
		if (*fruitX==snakeX[*head] && *fruitY==snakeY[*head]){
			int valuesX[99]={};
			int valuesY[99]={};
			for(int n=0;n<(*snakeSize-*tail);n++){
				valuesX[n]=snakeX[*tail+n];
				valuesY[n]=snakeY[*tail+n];
			}
			snakeX[*tail]=*fruitX;
			snakeY[*tail]=*fruitY;
			for(int n=0;n<(*snakeSize-*tail);n++){
				snakeX[(1+*tail+n)]=valuesX[n];
				snakeY[(1+*tail+n)]=valuesY[n];
			}
			*head=*tail;
			*tail=*tail+1;	
			*fruitX=rand() % 10;
			*fruitY=rand() % 10;
			*snakeSize=*snakeSize+1;
		} else{
			for(int i=0;i<*snakeSize;i++){
				if(*head!=i){
					if(snakeX[*head]==snakeX[i] && snakeY[i]==snakeY[*head]){
						*game=0;
						break;
					}
				}
			}	
		}
	//self & fruit collision while snake is 1 block long
	} else {
			if (*fruitX==snakeX[0] && *fruitY==snakeY[0]){
				//add new snake piece
				snakeX[*snakeSize]=*fruitX;
				snakeY[*snakeSize]=*fruitY;
				*snakeSize=*snakeSize+1;
				*head=*head+1;
				//new fruit location
				*fruitX=rand() % 10;
				*fruitY=rand() % 10;
			}
		}
}