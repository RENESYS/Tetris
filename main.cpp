/***************************************
 *                                            * 
 * ÇÐ¹ø: 20103316                        * 
 * ÀÌ¸§: ±èÀ±È£                            * 
 *                                            * 
 ***************************************/

#include<curses.h>
#include<time.h>
#include"manager.h"
using namespace std;

void main(){
	std::ifstream Command;
	Command.open("input.txt");
	char name[20];
	Command>>name;
	if(Command.fail() || name==NULL){
		cout<<"WELCOME TO TETRIS"<<endl;
		cout<<"Type your name and press ENTER"<<endl<<endl;
		cout<<"NAME : ";
		cin>>name;
	} 
	bool quit=false;
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	resize_term(25, 50);
	WINDOW* Game=newwin(20, 22, 2, 2);
	WINDOW* Score=newwin(4, 10, 4, 30);
	WINDOW* User=newwin(4, 10, 10, 30);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_CYAN, COLOR_BLACK);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	initialize(Game, Score, User, Command, name);
	int seed=-1;
		Command>>seed;
	seed==-1 ? srand((int)time(NULL)) : srand(seed);
	while(!quit){
		quit=playing(Game, Score, User, Command);
	}
	result();
	delwin(User);
	delwin(Score);
	delwin(Game);
	Command.close();
	endwin();
}

//user 0 g t l l l l d l d r d r r r r d q
