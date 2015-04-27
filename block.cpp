/***************************************
 *                                            * 
 * 학번: 20103316                        * 
 * 이름: 김윤호                            * 
 *                                            * 
 ***************************************/

#include<curses.h>
#include"block.h"

void initialMapping(int (*map)[24], int(*size)[8], int* mx, int* my){
	int index=0, tempmy=1;
	for(int y=3; y>=0; y-=DOWN){
		for(int x=0; x<8; x+=SIDE){
			if(map[y+*my][x+*mx]>10 && (size[y][x]>0 && size[y][x]<10)){
				index++;
				tempmy--;
				break;
			}
		}
	}
	*my=tempmy;
	mapping(map, size, mx, my);
}

//맵에 블럭을 새기는 함수
void mapping(int (*map)[24], int(*size)[8], int* mx, int* my){
	for(int y=3; y>=0; y-=DOWN){
		for(int x=0; x<8; x+=SIDE){
			(map[y+*my][x+*mx]>=10 && size[y][x]==0) ? 0 : map[y+*my][x+*mx]=size[y][x];
		}
	}
}


Block::Block(){
	for(int y=0; y<4; y+=DOWN){
		for(int x=0; x<8; x+=SIDE){
			size[y][x]=0;
		}
	}
}

//장애물(벽) 판단 함수
bool Block::obstacle(int (*map)[24], int(*size)[8], int* mx, int* my){
	for(int x=0; x<8; x+=SIDE){
		for(int y=0; y<4; y+=DOWN){
			if((size[y][x]>0 && size[y][x]<10) && map[y+*my][x+*mx]>=10){
				return true;
			}
		}
	}
	return false;
}

void Block::left(int (*map)[24], int* mx, int* my){
	*mx-=SIDE;
	if(obstacle(map, size, mx, my)==true){
		*mx+=SIDE;
		return;
	}
}

void Block::right(int (*map)[24], int* mx, int* my){
	*mx+=SIDE;
	if(obstacle(map, size, mx, my)==true){
		*mx-=SIDE;
		return;
	}
}

void Block::down(int (*map)[24], int* mx, int* my){
	*my+=DOWN;
	if(obstacle(map, size, mx, my)==true){
		*my-=DOWN;
		for(int y=0; y<4; y+=DOWN){
			for(int x=0; x<8; x+=SIDE){
				if(map[y+*my][x+*mx]>0 && map[y+*my][x+*mx]<10){
					map[y+*my][x+*mx]+=WALL;
				}
			}
		}
		*my=ESCAPE;
		return;
	}
}

void Block::fall(int (*map)[24], int* mx, int* my){
	while(obstacle(map, size, mx, my)==false){
		*my+=DOWN;
	}
	*my-=DOWN;
	mapping(map, size, mx, my);
	down(map, mx, my);
}

void Block::rotate(int (*map)[24], int* mx, int* my){
	int temp[4][8]={0, };
	//돌릴 도형을 임시 배열로 이동
	for(int y=0; y<3; y+=DOWN){
			for(int x=0; x<6; x+=SIDE){
				temp[y][x]=size[y][x];
			}
	}
	//회전
	for(int y=0; y<3; y+=DOWN){
		for(int x=0; x<6; x+=SIDE){
			size[2-(x/2)][2*y]=temp[y][x];
		}
	}
	while(obstacle(map, size, mx, my)==true){
		if((map[*my+1][*mx]>=10 || map[*my+2][*mx]>=10) || (map[*my+1][*mx+6]>=10 || map[*my+2][*mx+6]>=10) ||
		(map[*my][*mx+4]>=10 || map[*my][*mx+4]>=10) || (map[*my+3][*mx+2]>=10 || map[*my+3][*mx+4]>=10)){
			for(int y=0; y<3; y+=DOWN){
				for(int x=0; x<6; x+=SIDE){
					size[y][x]=temp[y][x];
				}
			}
		}
	}
}

int(*Block::get())[8]{
	return size;
}


OBlock::OBlock() : Block(){
	get()[0][0]=1;
	get()[0][2]=1;
	get()[1][0]=1;
	get()[1][2]=1;
}
void OBlock::rotate(int (*map)[24], int* mx, int* my){

}

LBlock::LBlock() : Block(){
	get()[0][2]=2;
	get()[1][2]=2;
	get()[2][2]=2;
	get()[2][4]=2;
}
JBlock::JBlock() : Block(){
	get()[0][2]=3;
	get()[1][2]=3;
	get()[2][2]=3;
	get()[2][0]=3;
}
SBlock::SBlock() : Block(){
	get()[0][2]=4;
	get()[1][2]=4;
	get()[1][4]=4;
	get()[2][4]=4;
}
ZBlock::ZBlock() : Block(){
	get()[0][2]=5;
	get()[1][2]=5;
	get()[1][0]=5;
	get()[2][0]=5;
}
TBlock::TBlock() : Block(){
	get()[0][2]=6;
	get()[1][0]=6;
	get()[1][2]=6;
	get()[1][4]=6;
}
IBlock::IBlock() : Block(){
	get()[0][2]=7;
	get()[1][2]=7;
	get()[2][2]=7;
	get()[3][2]=7;
}
void IBlock::rotate(int (*map)[24], int* mx, int* my){
	int temp[4][8]={0, };
	//돌릴 도형을 임시 배열로 이동
	for(int y=0; y<4; y+=DOWN){
			for(int x=0; x<8; x+=SIDE){
				temp[y][x]=get()[y][x];
			}
	}
	if(get()[1][6]==7){
		get()[1][6]=0;
		get()[1][4]=0;
		get()[1][0]=0;
		get()[0][2]=7;
		get()[2][2]=7;
		get()[3][2]=7;
	}
	else if(get()[3][2]==7){
		get()[1][6]=7;
		get()[1][4]=7;
		get()[1][0]=7;
		get()[0][2]=0;
		get()[2][2]=0;
		get()[3][2]=0;
	}
	while(obstacle(map, get(), mx, my)==true){
		if((map[*my+1][*mx]>=10 || map[*my+2][*mx]>=10) || (map[*my+1][*mx+6]>=10 || map[*my+2][*mx+6]>=10) ||
		(map[*my][*mx+4]>=10 || map[*my][*mx+4]>=10) || (map[*my+3][*mx+2]>=10 || map[*my+3][*mx+4]>=10)){
			for(int y=0; y<4; y+=DOWN){
				for(int x=0; x<8; x+=SIDE){
					get()[y][x]=temp[y][x];
				}
			}
		}
	}
}



