/***************************************
 *                                            * 
 * ÇÐ¹ø: 20103316                        * 
 * ÀÌ¸§: ±èÀ±È£                            * 
 *                                            * 
 ***************************************/

#pragma once
#include"map.h"

void initialMapping(int (*map)[24], int(*size)[8], int* mx, int* my);
void mapping(int (*map)[24], int(*size)[8], int* mx, int* my);


class Block{
private:
	int size[4][8];
public:
	Block();
	~Block(){};
public:
	bool obstacle(int (*map)[24], int(*size)[8], int* mx, int* my);
	void left(int (*map)[24], int* mx, int* my);
	void right(int (*map)[24], int* mx, int* my);
	void down(int (*map)[24], int* mx, int* my);
	void fall(int (*map)[24], int* mx, int* my);
	virtual void rotate(int (*map)[24], int* mx, int* my);
	int (*get())[8];
};


class OBlock : public Block{
private:
	
public:
	OBlock();
	~OBlock();
	virtual void rotate(int (*map)[24], int* mx, int* my);
};

class LBlock : public Block{
private:
	
public:
	LBlock();
	~LBlock();
};

class JBlock : public Block{
private:
	
public:
	JBlock();
	~JBlock();
};

class SBlock : public Block{
private:
	
public:
	SBlock();
	~SBlock();
};

class ZBlock : public Block{
private:
	
public:
	ZBlock();
	~ZBlock();
};

class TBlock : public Block{
private:
	
public:
	TBlock();
	~TBlock();
};

class IBlock : public Block{
private:
	
public:
	IBlock();
	~IBlock();
	virtual void rotate(int (*map)[24], int* mx, int* my);
};