/***************************************
 *                                            * 
 * ÇÐ¹ø: 20103316                        * 
 * ÀÌ¸§: ±èÀ±È£                            * 
 *                                            * 
 ***************************************/

#pragma once

#define DOWN 1
#define SIDE 2
#define WALL 10
#define ESCAPE -10

class Map{
private:
	int map[20][24];
	int score;
public:
	Map();
	~Map(){};
	int (*getMap())[24];
	int getScore();
	void deleteLine();
	void mapFlush();
	bool fullCheck();
};