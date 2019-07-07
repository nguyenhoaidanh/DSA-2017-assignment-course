/*


 * =========================================================================================


 * Name        : dbLib.cpp


 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh


 * Email       : nddung@hcmut.edu.vn


 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University


 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017


 *               This file implements functions used for database management


 * =========================================================================================


 */





#include "dbLib.h"





#include <time.h>


#include <fstream>


#include <string>


#include <iostream>


#include <sstream>


#include <cmath>


#define pi 3.14159265358979323846


#define earthRadiusKm 6371.0





using namespace std;





void    strPrintTime(char* des, time_t& t) {


    tm *pTime = localtime(&t);


    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);


}





void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {


	// TODO: write code to load information from file into db


fstream fileInput(fName, ios::in);


	string temp, Time, id, x1, y1;


	int mo, year;


	struct tm * timeinfo;


	char charTemp;


	NinjaInfo_t ninja;


	getline(fileInput, temp);if(temp=="")return;


	while (!fileInput.eof())


	//for (int i = 1; i <=1500000; i++)


	{


		getline(fileInput, temp, ',');


		if (temp == "")break;


		//if(i<=1000000)continue;


		getline(fileInput, Time, ',');


		//time


		getline(fileInput, id, ',');


		//id


		getline(fileInput, x1, ','); stringstream x(x1); x >> ninja.longitude;


		//long


		getline(fileInput, y1, ','); stringstream y(y1); y >> ninja.latitude;


		//la


		getline(fileInput, temp);


		string b(id);


		if(b.length()<4)

		{while (b.length() < 4)


		{


			b.insert(0, "0");


		}


		id = b;


		for (int i = 0; i < id.length(); i++)


		{


			ninja.id[i] = id[i];


		}


		ninja.id[4] = '\0';}
		else {strncpy(ninja.id,id.data(),ID_MAX_LENGTH-1);}

		stringstream temp1(Time);
		

		time(&ninja.timestamp);


		timeinfo = localtime(&ninja.timestamp);


		temp1 >> mo >> charTemp >> timeinfo->tm_mday >> charTemp >> year >> timeinfo->tm_hour


			>> charTemp >> timeinfo->tm_min >> charTemp >> timeinfo->tm_sec;


		timeinfo->tm_mon = mo - 1;


		timeinfo->tm_year = year - 1900;


		//


		 //timeinfo->tm_hour-=7;


		//


		ninja.timestamp = mktime(timeinfo);


		db.push_back(ninja);


	}


}





bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {


    // TODO: write code to parse information from a string buffer, ignore if you don't use it


    return true;


}








void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {


   void*   pGData = NULL; string dau,cuoi;dau=cuoi="";


if(bList._size!=0)


	{ dau=bList._pHead->data.id;


	 cuoi=bList._pLast->data.id;}


	


	


	string t = "";L1Item<ninjaEvent_t>*p = eventList._pHead;initNinjaGlobalData(&pGData);


	int i = 0;


	while (p)


	{


		if (i != eventList._size - 1)


		{


			t += string(p->data.code);


			t += " ";


		}


		else


		{


			t += string(p->data.code);


			t += "\n";


		}


		p = p->pNext; i++;


	}


	


	while (!eventList.isEmpty())


	{


		if (!processEvent(eventList[0], bList, pGData))cout << eventList[0].code << " is an invalid event\n";


		else 


		{


		


			if (strcmp(eventList[0].code, "0") == 0)


			{ 


				cout << eventList[0].code << ": " << t;


			}


			if (strcmp(eventList[0].code, "1") == 0)


			{if(bList._size==0)cout<<"1: empty"<<endl;else


				cout << "1: " << dau<<endl;


			}


			if (strcmp(eventList[0].code, "2") == 0)


			{if(bList._size==0)cout<<"2: empty"<<endl;else


				cout << "2: " << cuoi<<endl;


			}


		}


		


		eventList.removeHead();


	}


	releaseNinjaGlobalData(pGData);


}








bool initNinjaGlobalData(void** pGData) {


    /// TODO: You should define this function if you would like to use some extra data


    /// the data should be allocated and pass the address into pGData


    return true;


}





void releaseNinjaGlobalData(void* pGData) {


    /// TODO: You should define this function if you allocated extra data at initialization stage


    /// The data pointed by pGData should be released


}








void printNinjaInfo(NinjaInfo_t& b) {


    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));


}





/// This function converts decimal degrees to radians


double deg2rad(double deg) {


    return (deg * pi / 180);


}





///  This function converts radians to decimal degrees


double rad2deg(double rad) {


    return (rad * 180 / pi);


}





/**


 * Returns the distance between two points on the Earth.


 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula


 * @param lat1d Latitude of the first point in degrees


 * @param lon1d Longitude of the first point in degrees


 * @param lat2d Latitude of the second point in degrees


 * @param lon2d Longitude of the second point in degrees


 * @return The distance between the two points in kilometers


 */


double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {


    double lat1r, lon1r, lat2r, lon2r, u, v;


    lat1r = deg2rad(lat1d);


    lon1r = deg2rad(lon1d);


    lat2r = deg2rad(lat2d);


    lon2r = deg2rad(lon2d);


    u = sin((lat2r - lat1r)/2);


    v = sin((lon2r - lon1r)/2);


    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));


}