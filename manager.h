/***************************************
 *                                            * 
 * �й�: 20103316                        * 
 * �̸�: ����ȣ                            * 
 *                                            * 
 ***************************************/

#pragma once

#include<iostream>
#include<fstream>

void initialize(WINDOW* Game, WINDOW* Score, WINDOW* User, std::ifstream& File, char* name);
bool playing(WINDOW* Game, WINDOW* Score, WINDOW* User, std::ifstream& File);
void result();


