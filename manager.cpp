/***************************************
 *                                            * 
 * ÇÐ¹ø: 20103316                        * 
 * ÀÌ¸§: ±èÀ±È£                            * 
 *                                            * 
 ***************************************/

#include<cstdlib>
#include<curses.h>
#include"manager.h"
#include"block.h"


Map gamemap;

Block* makeBlock();
void display(WINDOW* Game, WINDOW* Score, WINDOW* User);
int getcmd(std::ifstream& File);


void initialize(WINDOW* Game, WINDOW* Score, WINDOW* User, std::ifstream& Command, char* name){
	wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	mvprintw(0, 16, " T  E  T  R  I  S ");							
	wborder(Game, '|','|','-','-','+','+','+','+');
	wborder(User, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(Score, '|', '|', '-', '-', '+', '+', '+', '+');	
	wattron(Score, COLOR_PAIR(3));
	mvwprintw(Score, 1, 1, "SCORE");
	wattroff(Score, COLOR_PAIR(3));
	wattron(User, COLOR_PAIR(3));
	mvwprintw(User, 1, 1, "PLAYER");
	mvwprintw(User, 2, 1, "%s", name);
	wattroff(User, COLOR_PAIR(3));
	refresh();
	display(Game, Score, User);
}


void display(WINDOW* Game, WINDOW* Score, WINDOW* User){
	for(int y=1; y<19; y+=DOWN){
		for(int x=2; x<22; x+=SIDE){
			if(gamemap.getMap()[y][x]==0){
				wattron(Game, COLOR_PAIR(1));
				mvwaddwstr(Game, y, x-1, L"¡à¡à");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(1));
			}
			else if(gamemap.getMap()[y][x]%10==1){
				wattron(Game, COLOR_PAIR(3));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(3));
			}
			else if(gamemap.getMap()[y][x]%10==2){
				wattron(Game, COLOR_PAIR(4));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(4));
			}
			
			else if(gamemap.getMap()[y][x]%10==3){
				wattron(Game, COLOR_PAIR(5));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(5));
			}
			else if(gamemap.getMap()[y][x]%10==4){
				wattron(Game, COLOR_PAIR(6));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(6));
			}
			else if(gamemap.getMap()[y][x]%10==5){
				wattron(Game, COLOR_PAIR(7));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(7));
			}
			else if(gamemap.getMap()[y][x]%10==6){
				wattron(Game, COLOR_PAIR(8));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(8));
			}
			else if(gamemap.getMap()[y][x]%10==7){
				wattron(Game, COLOR_PAIR(9));
				mvwaddwstr(Game, y, x-1, L"¡á¡á");
				wrefresh(Game);
				wattroff(Game, COLOR_PAIR(9));
			}
		}
	}
	wattron(Score, COLOR_PAIR(3));
	mvwprintw(Score, 2, 1, "%d", gamemap.getScore());
	wattroff(Score, COLOR_PAIR(3));
	wrefresh(User);		
	wrefresh(Score);
}


bool playing(WINDOW* Game, WINDOW* Score, WINDOW* User, std::ifstream& Command){
	Block* block=makeBlock();
	int ch, mx=10, my=1;
	initialMapping(gamemap.getMap(), block->get(), &mx, &my);
	display(Game, Score, User);
	while(my!=ESCAPE){
		Command.eof()==false ? ch=getcmd(Command) : ch=getch();
		switch(ch){
		case KEY_LEFT:
			block->left(gamemap.getMap(), &mx, &my);
			break;
		case KEY_RIGHT: 
			block->right(gamemap.getMap(), &mx, &my);
			break;
		case KEY_UP:
			block->rotate(gamemap.getMap(), &mx, &my);
			break;
		case KEY_DOWN:
			block->down(gamemap.getMap(), &mx, &my);
			break;
		case 32:	//Space bar
			block->fall(gamemap.getMap(), &mx, &my);
			break;
		case 113:		//Q key
			delete block;
			return true;
		}
		gamemap.mapFlush();
		mapping(gamemap.getMap(), block->get(), &mx, &my);
		display(Game, Score, User);
	}
	delete block;
	gamemap.deleteLine();
	if(gamemap.fullCheck()==true)
		return true;
	return false;
}

void result(){
	attron(COLOR_PAIR(2));
	mvwprintw(stdscr, 20, 27, " G A M E   O V E R ");
	attroff(COLOR_PAIR(2));
	mvwprintw(stdscr, 21, 27, "Your Score : %d", gamemap.getScore());
	mvwprintw(stdscr, 23, 10, "Press any key to exit TETRIS");
	getch();
}

Block* makeBlock(){
	int sel=rand()%7;
	switch(sel){
	case 0:{
		Block* o=new OBlock();
		return o;
		}
	case 1:{
		Block* l=new LBlock();
		return l;
		}
	case 2:{
		Block* j=new JBlock();
		return j;
		}
	case 3:{
		Block* s=new SBlock();
		return s;
		}
	case 4:{
		Block* z=new ZBlock();
		return z;
		}
	case 5:{
		Block* t=new TBlock();
		return t;
		}
	case 6:{
		Block* i=new IBlock();
		return i;
		}
	}
	return 0;
}

int getcmd(std::ifstream& File){
	char cmdchar;
	File>>cmdchar;
	switch(cmdchar){
	case 'l':
		return KEY_LEFT;
	case 'r':
		return KEY_RIGHT;
	case 't':
		return KEY_UP;
	case 'g':
		return KEY_DOWN;
	case 'd':
		return 32;
	case 'q':
		return 113;
	}
	return 0;
}




