#ifndef DSA171A2_DBLIB_H
#define DSA171A2_DBLIB_H
#include <string>
#include <string.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <functional>
#include "dsaLib.h"
#include "requestLib.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define ID_MAX_LENGTH   16
struct VM_Record {
    char    id[ID_MAX_LENGTH];
    time_t  timestamp;
    double  longitude, latitude;
    // default constructor
    VM_Record() {
        id[0] = 0;
    }
    VM_Record(const char* busID) {
        strcpy(id, busID);
    }
    // copy constructor
    VM_Record(VM_Record& bus) : timestamp(bus.timestamp), longitude(bus.longitude), latitude(bus.latitude) {
        strcpy(id, bus.id);
    }
	bool operator>(VM_Record vm)
	{
		return timestamp>vm.timestamp;
	}
	bool operator<(VM_Record vm)
	{
		return timestamp<vm.timestamp;
	}
	bool operator==(VM_Record vm)
	{
		return timestamp==vm.timestamp;
	}
	
};
//
struct NODE
{
	char id[ID_MAX_LENGTH];
	AVLTree<VM_Record> avl;
	bool out;
	double minla, minlo, maxla, maxlo;
	NODE()
	{
		id[0] = 0; minla = 40; minlo = 0; maxla = 0; maxlo = -150; out = false;
	}
	NODE(const char* busID) {
		strcpy(id, busID);
	}
	// copy constructor
	NODE(const NODE& bus)
	{
		out = bus.out;
		avl = bus.avl;
		strcpy(id, bus.id);
		minla = bus.minla;
		minlo = bus.minlo;
		maxla = bus.maxla;
		maxlo = bus.maxlo;
	}
	bool operator>(NODE n)
	{
		return strcmp(id, n.id) > 0;
	}
	bool operator<(NODE n)
	{
		return strcmp(id, n.id) < 0;
	}
	bool operator==(NODE n)
	{
		return strcmp(id, n.id) == 0;
	}
};
///
void    printVMRecord(VM_Record &);
void    strPrintTime(char* des, time_t& t);
bool    parseVMRecord(string, VM_Record &);// dã edit
void    loadVMDB(char*, L1List<VM_Record> &);
double  distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
bool processRequest(VM_Request &, L1List<VM_Record> &, vector<NODE>& , AVLTree<NODE>& , void *);// from processData.cpp
bool initVMGlobalData(void** pGData);
void releaseVMGlobalData(void* pGData);
void process(L1List<VM_Request>& requestList, L1List<VM_Record>& recordList);
#endif //DSA171A2_DBLIB_H
