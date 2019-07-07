#include "dbLib.h"
#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdlib.h>

#define __PI 3.14159265358979323846

#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {

	tm *pTime = localtime(&t);

	strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);

}

void loadVMDB(char* fName, L1List<VM_Record> &db) {

	ifstream inFile(fName);

	string temp, Time, id, x1, y1;

	VM_Record record;

	struct tm * timeinfo;

	if (inFile)

	{

		getline(inFile, temp);// skip the first line

		while ((!inFile.eof()))

		{

			getline(inFile, temp, ',');

			if (temp == "")break;

			getline(inFile, Time, ',');	//time

			time(&record.timestamp);

			timeinfo = localtime(&record.timestamp);

			timeinfo->tm_mon = (Time[0] - 48) * 10 + Time[1] - 48 - 1;

			timeinfo->tm_mday = (Time[3] - 48) * 10 + Time[4] - 48;

			timeinfo->tm_year = (Time[6] - 48) * 1000 + (Time[7] - 48) * 100 + (Time[8] - 48) * 10 + Time[9] - 48 - 1900;

			timeinfo->tm_hour = (Time[11] - 48) * 10 + Time[12] - 48;

			timeinfo->tm_min = (Time[14] - 48) * 10 + Time[15] - 48;

			timeinfo->tm_sec = (Time[17] - 48) * 10 + Time[18] - 48;

			timeinfo->tm_sec = (Time[17] - 48) * 10 + Time[18] - 48;

			record.timestamp = mktime(timeinfo);

			getline(inFile, id, ',');	//id

			strncpy(record.id, id.data(), ID_MAX_LENGTH - 1);

			getline(inFile, x1, ','); record.longitude = atof(x1.c_str());	//long

			getline(inFile, y1, ','); record.latitude = atof(y1.c_str());	//la

			getline(inFile, temp);

			db.push_back(record);
		}

		inFile.close();
	}

	else {

		cout << "The file is not found!";
	}

}

bool parseVMRecord(string line, VM_Record &record) {

	// TODO: write code to parse a record from given line

	return true;

}

void process(L1List<VM_Request>& requestList, L1List<VM_Record>& rList) {

	void*   pGData = NULL;

	initVMGlobalData(&pGData);

	//create AVL and push data into it

	AVLTree<NODE> AVL; //main AVL tree

	NODE key; //de tim kiem id co ton tai trong cay chua

	NODE* ret; //de luu dia chi neu tim thay key

	L1Item<VM_Record>*pRun = rList.getHead(); AVL.AVLsize = 0;

	while (pRun)

	{

		strncpy(key.id, pRun->data.id, ID_MAX_LENGTH - 1);

		if (AVL.find(key, ret))

		{

			//insert vm record vao nut cua cay con ret

			if (pRun->data.latitude > ret->maxla)ret->maxla = pRun->data.latitude;

			if (pRun->data.latitude < ret->minla)ret->minla = pRun->data.latitude;

			if (pRun->data.longitude > ret->maxlo)ret->maxlo = pRun->data.longitude;

			if (pRun->data.longitude < ret->minlo)ret->minlo = pRun->data.longitude;

			ret->avl.insert(pRun->data);

		}

		else

		{

			AVL.AVLsize++;

			NODE newnode;

			AVLTree<VM_Record> subTree;

			strncpy(newnode.id, pRun->data.id, ID_MAX_LENGTH - 1);

			newnode.minla = newnode.maxla = pRun->data.latitude;

			newnode.minlo = newnode.maxlo = pRun->data.longitude;

			subTree.insert(pRun->data);

			newnode.avl = subTree;

			AVL.insert(newnode); //insert NODE moi

		}

		pRun = pRun->pNext;

	}

	vector<NODE> Data89;

	//xu ly request

	while (!requestList.isEmpty()) {

		if (!processRequest(requestList[0], rList, Data89, AVL, pGData))
		{

			cout << requestList[0].code;
			//truong hop 1 2 3 4 ...
			if (requestList[0].params[requestList[0].sizePram - 1] == "!")cout << " is an invalid event\n";

			else {
				//truong hop 1_ 2_ 3_ ... 2_..._ thua dau _ cui
				if (requestList[0].params[requestList[0].sizePram - 1] == ""&&requestList[0].sizePram == 1)cout << "_ is an invalid event\n";

				else
				//in binh thuong ra
				{
					for (int i = 0; i < requestList[0].sizePram; i++)

					{

						cout << "_" << requestList[0].params[i];

					}

					cout << " is an invalid event\n";
				}
			}

		}

		requestList.removeHead();

	}

	releaseVMGlobalData(pGData);

}

void printVMRecord(VM_Record &b) {

	printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));

}

/// This function converts decimal degrees to radians

inline double deg2rad(double deg) {

	return (deg * __PI / 180);

}

///  This function converts radians to decimal degrees

inline double rad2deg(double rad) {

	return (rad * 180 / __PI);

}

double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {

	double lat1r, lon1r, lat2r, lon2r, u, v;

	lat1r = deg2rad(lat1d);

	lon1r = deg2rad(lon1d);

	lat2r = deg2rad(lat2d);

	lon2r = deg2rad(lon2d);

	u = sin((lat2r - lat1r) / 2);

	v = sin((lon2r - lon1r) / 2);

	return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}