/***************************************
 *                                            * 
 * ÇÐ¹ø: 20103316                        * 
 * ÀÌ¸§: ±èÀ±È£                            * 
 *                                            * 
 ***************************************/

#include"map.h"

Map::Map(){
	score=0;
	for(int y=0; y<20; y++){
		for(int x=0; x<24; x++){
			map[y][x]=0;
		}
	}
	for(int x=0; x<24; x++){
		map[0][x]=WALL;
		map[19][x]=WALL;
	}
	for(int y=1; y<19; y++){
		map[y][0]=WALL;
		map[y][22]=WALL;
	}
}

int (*Map::getMap())[24]{
	return map;
}

int Map::getScore(){
	return score;
}


void Map::deleteLine(){
	int yCheck=18;
	while(yCheck!=0){
		int index=1;
		//ÁÙÀÌ ²Ë Ã¡´ÂÁö Ã¼Å©
		while(index==1){
			for(int x=2; x<22; x+=SIDE){
				if(map[yCheck][x]==0){
					index=0;
				}
			}
			//ÁÙ Á¦°Å
			if(index==1){
				for(int y=yCheck; y>0; y-=DOWN){
					for(int x=2; x<22; x+=SIDE){
						map[y][x]=map[y-1][x];
					}
				}
				for(int x=2; x<22; x+=SIDE){
					map[1][x]=0;
				}
				score+=1;
			}
		}
		yCheck--;
	}
	return;
}

void Map::mapFlush(){
	for(int y=1; y<19; y++){
		for(int x=2; x<22; x++){
			if(map[y][x]<10){
				map[y][x]=0;
			}
		}
	}
}

bool Map::fullCheck(){
	for(int x=2; x<22; x+=SIDE){
		if(map[1][x]>10)
			return true;
	}
	return false;
}
