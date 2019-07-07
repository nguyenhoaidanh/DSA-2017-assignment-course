#ifndef DSA171A2_REQUESTLIB_H
#define DSA171A2_REQUESTLIB_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include "dsaLib.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define REQUEST_CODE_SIZE     40
#define MAX_PARAM_SIZE         20
using namespace std;
struct VM_Request {
	char        code[REQUEST_CODE_SIZE];
	string      params[MAX_PARAM_SIZE];
	int			sizePram;
	VM_Request() {
		*code = '0';// default event is "0"
		code[1] = 0;
		sizePram = 0;
	}
	VM_Request(char* str) {
		strncpy(code, str, REQUEST_CODE_SIZE - 1);
	}
	VM_Request(string& str) {
		strncpy(code, str.data(), REQUEST_CODE_SIZE - 1);
	}
	VM_Request(VM_Request& a) { // copy constructor
		memcpy(code, a.code, REQUEST_CODE_SIZE);
		sizePram = a.sizePram;
		for (int i = 0; i < a.sizePram; i++)
		{
			params[i] = a.params[i];
		}
	}
	bool operator==(VM_Request &b) {
		return strcmp(code, b.code) == 0;
	}
};
void loadRequests(char* fName, L1List<VM_Request> &);
#endif //DSA171A2_REQUESTLIB_H
