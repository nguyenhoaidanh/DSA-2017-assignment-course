/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	fstream fileInput(fName, ios::in);
	string temp,temp1;
	getline(fileInput,temp,';');
	stringstream t(temp);
	while (!t.eof())
	{
			t >> temp1;
			ninjaEvent_t e;
			strncpy(e.code, temp1.data(), EVENT_CODE_SIZE - 1);
			eList.push_back(e);
	} 
}
