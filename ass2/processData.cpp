#include<iostream>
#include <vector>
#include <functional>
#include <math.h>
#include "requestLib.h"
#include "dbLib.h"
using namespace std;

#define GPS_DISTANCE_ERROR 0.005

bool initVMGlobalData(void** pGData) {

	return true;


}

void releaseVMGlobalData(void* pGData) {



	// TODO: do your cleanup, left this empty if you don't have any dynamically allocated data



}

void LNR_checkControled(AVLNode<VM_Record>* pR, double lo, double la, double R, time_t time1, time_t time2, int& thoa)



{



	if (thoa == 1)return;



	if (pR == NULL)return;



	if (pR->_pLeft)LNR_checkControled(pR->_pLeft, lo, la, R, time1, time2, thoa);



	if (pR->_data.timestamp >= time1&&pR->_data.timestamp <= time2)



	{



		if (distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) <= R&&distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) >= 0)



		{



			thoa = 1; //id nay co nam trong vung kiem soat



			return;



		}



	}



	if (thoa == 1)return;



	if (pR->_pRight)LNR_checkControled(pR->_pRight, lo, la, R, time1, time2, thoa);



	if (thoa == 1)return;



}

void LNR_countNumberControled(NODE node, double lo, double la, double R, time_t time1, time_t time2, int& count)



{



	int thoa = 0;



	LNR_checkControled(node.avl.getRoot(), lo, la, R, time1, time2, thoa);



	if (thoa == 1)count++;



}

void countRQ5(AVLNode<VM_Record>* pR, AVLNode<VM_Record>* &pRre, double la, double lo, double R, int &count)



{	//dem so lan di vao tram cua id nao do



	if (pR == NULL)return;



	if (pR->_pLeft) countRQ5(pR->_pLeft, pRre, la, lo, R, count);



	if (pR == pRre&&distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) <= R) {



		pRre = pR; count++;



	}



	if (distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) <= R



		&&distanceEarth(la, lo, pRre->_data.latitude, pRre->_data.longitude) > R) {



		count++; pRre = pR;



	}



	pRre = pR;



	if (pR->_pRight) countRQ5(pR->_pRight, pRre, la, lo, R, count);



}

void LNR_check_R1_to_R2(AVLNode<VM_Record>* pR, double lo, double la, double R1, double R2, time_t time1, time_t time2, int& thoa, double&ret)



{ //check xem co cach tam kiem xoa tu R1 den R2 km hay khong 







	if (pR == NULL)return;



	if (pR->_pLeft)LNR_check_R1_to_R2(pR->_pLeft, lo, la, R1, R2, time1, time2, thoa, ret);



	if (pR->_data.timestamp >= time1&&pR->_data.timestamp <= time2)



	{



		if (distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) >= R1&&



			distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude) <= R2)



		{



			if (ret < distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude))ret = distanceEarth(la, lo, pR->_data.latitude, pR->_data.longitude);



			thoa = 1; //id nay co nam cach tram R1 -> R2 km







		}



	}







	if (pR->_pRight)LNR_check_R1_to_R2(pR->_pRight, lo, la, R1, R2, time1, time2, thoa, ret);







}

void sort_distance_vs_station(vector<string>& ns, vector<double>& d, double la, double lo)



{



	int n = ns.size(); double tem; string temp;



	if (n != d.size())cout << "List string va list d khong bang size";



	if (n <= 1)return;



	for (int i = 0; i < n - 1; i++)



	{



		for (int j = i + 1; j < n; j++)



		{



			if (d[i] < d[j])



			{



				tem = d[j]; temp = ns[j];



				d[j] = d[i]; ns[j] = ns[i];



				d[i] = tem; ns[i] = temp;



			}



		}



	}



}

bool request1(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL)



{//|| request.params[2].length() != 6

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}



	if (request.params[0] == "" || request.params[1] == "")

	{

		cout << "1: -1" << endl; return true;

	}







	//print request



	cout << request.code << ": ";



	// xu li thoi gian



	struct tm * timeinfo;



	time_t TIME;



	time(&TIME);



	timeinfo = localtime(&TIME);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;

	if (request.params[2].length() >= 6)

	{

		stringstream t(request.params[2].substr(0, 2));			t >> timeinfo->tm_hour;



		stringstream t1(request.params[2].substr(2, 2));		t1 >> timeinfo->tm_min;



		stringstream t2(request.params[2].substr(4, 2));		t2 >> timeinfo->tm_sec;

	}

	if (request.params[2].length() == 5)

	{

		stringstream t(request.params[2].substr(0, 2));			t >> timeinfo->tm_hour;



		stringstream t1(request.params[2].substr(2, 2));		t1 >> timeinfo->tm_min;



		stringstream t2(request.params[2].substr(4, 1));		t2 >> timeinfo->tm_sec;

	}

	if (request.params[2].length() == 4)

	{

		stringstream t(request.params[2].substr(0, 2));			t >> timeinfo->tm_hour;



		stringstream t1(request.params[2].substr(2, 2));		t1 >> timeinfo->tm_min;

		timeinfo->tm_sec = 0;

	}

	if (request.params[2].length() == 3)

	{

		stringstream t(request.params[2].substr(0, 2));			t >> timeinfo->tm_hour;



		stringstream t1(request.params[2].substr(2, 1));		t1 >> timeinfo->tm_min;

		timeinfo->tm_sec = 0;

	}

	if (request.params[2].length() == 3)

	{

		stringstream t(request.params[2].substr(0, 2));			t >> timeinfo->tm_hour;

		timeinfo->tm_min = 0;

		timeinfo->tm_sec = 0;

	}

	if (request.params[2].length() == 1)

	{

		stringstream t(request.params[2].substr(0, 1));			t >> timeinfo->tm_hour;

		timeinfo->tm_min = 0;

		timeinfo->tm_sec = 0;

	}

	TIME = mktime(timeinfo);



	VM_Record * ret1 = NULL; VM_Record * ret2 = NULL;



	VM_Record vm1, vm2;



	//vm1 vm2 chua id, Time can tim	



	vm1.timestamp = TIME;



	vm2.timestamp = TIME;



	strncpy(vm1.id, request.params[0].data(), ID_MAX_LENGTH - 1);



	strncpy(vm2.id, request.params[1].data(), ID_MAX_LENGTH - 1);



	NODE KEY1, KEY2;



	NODE *RET1 = NULL;



	NODE *RET2 = NULL;



	strncpy(KEY1.id, vm1.id, ID_MAX_LENGTH - 1);



	strncpy(KEY2.id, vm2.id, ID_MAX_LENGTH - 1);



	if ((!AVL.find(KEY1, RET1)) || (!AVL.find(KEY2, RET2)))cout << -1 << endl;



	else



	{







		if (RET1->avl.find(vm1, ret1) && RET2->avl.find(vm2, ret2))



		{



			if (ret1->longitude - ret2->longitude >= 0)cout << "E ";



			else cout << "W ";



			if (ret1->latitude - ret2->latitude >= 0)cout << "N ";



			else cout << "S ";



			cout << distanceEarth(ret1->latitude, ret1->longitude, ret2->latitude, ret2->longitude) << endl;



		}



		else cout << -1 << endl;



	}



	return true;



}

bool request2(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL, vector<NODE>& Data89)



{





	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] != 'W')if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] != 'E' || request.sizePram <= 1)return false;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}

	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] == 'W'&&request.params[0] == "")

	{
		cout << "2: " << AVL.AVLsize << endl; return true;
	}

	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] == 'E'&&request.params[0] == "")

	{
		cout << "2: 0" << endl; return true;
	}



	//print request



	cout << request.code << ": ";



	int dem = 0;	double lo;



	stringstream tem(request.params[0]);



	tem >> lo;



















	if (Data89.size() == 0)AVL.add_into_vector(Data89);



	for (int i = 0; i < Data89.size(); i++)



	{







		if (Data89[i].out == false && request.params[1] == "W" && Data89[i].maxlo <= lo)dem++;



		if (Data89[i].out == false && request.params[1] == "E" && Data89[i].minlo >= lo)dem++;



	}










	cout << dem << endl;



	return true;



}

bool request3(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL, vector<NODE>& Data89)



{



	//if (request.sizePram != 2 || request.params[1].length() != 1)return false;



	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] != 'S')if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] != 'N' || request.sizePram <= 1)return false;

	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] == 'N'&&request.params[0] == "")

	{
		cout << "3: " << AVL.AVLsize << endl; return true;
	}

	if (request.params[request.sizePram - 1][(request.params[request.sizePram - 1]).length() - 1] == 'S'&&request.params[0] == "")

	{
		cout << "3: 0" << endl; return true;
	}



	//print request



	cout << request.code << ": ";



	int dem = 0;	double la;



	stringstream tem(request.params[0]);



	tem >> la;











	if (Data89.size() == 0)AVL.add_into_vector(Data89);



	for (int i = 0; i < Data89.size(); i++)



	{







		if (Data89[i].out == false && request.params[1] == "S" && Data89[i].maxla <= la)dem++;



		if (Data89[i].out == false && request.params[1] == "N" && Data89[i].minla >= la)dem++;



	}



	//AVL.NLR_countOnlyH(la, dem, request.params[1]);



	cout << dem << endl;



	return true;



}

bool request4(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL)



{



	double la, lo, R;



	int count = 0;



	int H1, H2;



	stringstream t(request.params[0]), t1(request.params[1]), t2(request.params[2]), t3(request.params[3]), t4(request.params[4]);



	t >> lo;	t1 >> la;	t2 >> R;	t3 >> H1;	t4 >> H2;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}

	if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "" || request.params[3] == "")

	{

		cout << "4: 0" << endl; return true;

	}

	if (request.sizePram != 5)return false;





	cout << request.code << ": ";



	//xu li thoi gian



	struct tm * timeinfo;



	time_t time1;



	time(&time1);



	timeinfo = localtime(&time1);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;



	timeinfo->tm_hour = H1;



	timeinfo->tm_min = timeinfo->tm_sec = 0;



	time1 = mktime(timeinfo);



	time_t time2 = time1 + (H2 - H1) * 3600; //*************************note ? 



	void(*pF)(NODE, double, double, double, time_t, time_t, int &) = LNR_countNumberControled;



	AVL.traverseLNR_Q4(pF, lo, la, R, time1, time2, count);



	cout << count << endl;



	return true;



}

bool request5(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL)



{



	///////////////////Cau nay sai rui vi ra moi g?i la vao lai lan sau



	double la, lo, R;



	int count = 0;



	stringstream t1(request.params[1]), t2(request.params[2]), t3(request.params[3]);



	t1 >> lo;	t2 >> la;	t3 >> R;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}

	if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "")

	{

		cout << "5: -1" << endl; return true;

	}



	if (request.sizePram != 4)return false;



	cout << request.code << ": ";//R < 0 ||



	NODE KEY;



	NODE *RET = NULL;



	strncpy(KEY.id, request.params[0].data(), ID_MAX_LENGTH - 1);



	if (AVL.find(KEY, RET))



	{



		AVLNode<VM_Record>* pRre = RET->avl.getRoot();



		while (pRre->_pLeft)



		{



			pRre = pRre->_pLeft;



		}



		countRQ5(RET->avl.getRoot(), pRre, la, lo, R, count);



		cout << count << endl;



	}



	else cout << -1 << endl;



	return true;



}

bool request6(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL)



{



	double la, lo;



	int num, timetemp;



	stringstream t(request.params[0]), t1(request.params[1]), t2(request.params[2]), t3(request.params[3]);



	t >> lo;	t1 >> la;	t2 >> num;	t3 >> timetemp;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}

	if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "")

	{

		cout << "6: - -1" << endl; return true;

	}



	if (request.sizePram != 4)return false;



	//print request



	cout << request.code << ":";



	//time



	struct tm * timeinfo;



	time_t time2;



	time(&time2);



	timeinfo = localtime(&time2);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;



	timeinfo->tm_hour = timetemp / 100;



	timeinfo->tm_min = timetemp % 100;



	timeinfo->tm_sec = 0;  //Note



	time2 = mktime(timeinfo);



	time_t time1 = time2 - 900;//tru 15ph //check am??



							   //



	vector<NODE> listNODE;



	AVL.add_into_vector(listNODE);



	vector<NODE> list2km;



	vector<NODE> list300m;



	vector<string> list500m;



	int count2km = 0; //dem truoc 15ph, R 2km co bao nhieu xe



	for (int i = 0; i < listNODE.size(); i++)



	{

		int thoa = 0;



		LNR_checkControled(listNODE[i].avl.getRoot(), lo, la, 2.0, time1, time2, thoa);



		if (thoa == 1) { list2km.push_back(listNODE[i]); count2km++; }







	}











	if (count2km < num) {



		//cout << "in all theo 2km < num: ";







		for (int i = 0; i < list2km.size(); i++)



			cout << " " << list2km[i].id;



		cout << " - -1" << endl;







		return true;



	}



	int count300m = 0;//check co >0.75num khong



	for (int i = 0; i < listNODE.size(); i++)



	{

		int thoa = 0;



		LNR_checkControled(listNODE[i].avl.getRoot(), lo, la, 0.3, time1, time2, thoa);



		if (thoa == 1) { list300m.push_back(listNODE[i]); count300m++; }







	}



	if (double(count300m) > 0.75*double(num))



	{







		cout << " -1 -";



		for (int i = 0; i < list2km.size(); i++)



		{



			cout << " " << list2km[i].id;



		}



		cout << endl;



		return true;



	}



	//500m



	int count500m = 0;



	for (int i = 0; i < list2km.size(); i++)



	{

		int thoa = 0;



		LNR_checkControled(list2km[i].avl.getRoot(), lo, la, 0.5, time1, time2, thoa);



		if (thoa != 1) { list500m.push_back(string(list2km[i].id)); count500m++; }

		else cout << " " << list2km[i].id;







	}



	cout << " -";







	if (count500m == 0)



	{



		cout << " -1" << endl; return true;



	}



	for (int i = 0; i < list500m.size(); i++)



	{



		cout << " " << list500m[i];







	}



	cout << endl;







	return true;



}

bool request7(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL)



{



	double la, lo, R;



	int num, timetemp;



	stringstream t(request.params[0]), t1(request.params[1]), t2(request.params[2]), t3(request.params[3]), t4(request.params[4]);



	t >> lo;	t1 >> la;	t2 >> num;	t3 >> R; t4 >> timetemp;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "" || request.params[3] == "")

	{

		cout << "7: -1 - -1" << endl; return true;

	}



	if (request.sizePram != 5)return false;



	//print request



	cout << request.code << ":";



	//time



	struct tm * timeinfo;



	time_t time1;



	time(&time1);



	timeinfo = localtime(&time1);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;



	timeinfo->tm_hour = timetemp / 100;



	timeinfo->tm_min = timetemp % 100;



	timeinfo->tm_sec = 0;  //Note



	time1 = mktime(timeinfo);



	time_t time2 = time1 + 1800;//cong 30ph







	vector<NODE> listNODE;



	AVL.add_into_vector(listNODE);



	vector<NODE> list500m;



	vector<double> d500m;



	int count500m = 0;



	for (int i = 0; i < listNODE.size(); i++)



	{

		int thoa = 0;



		LNR_checkControled(listNODE[i].avl.getRoot(), lo, la, 0.5, time1, time2, thoa);







		if (thoa == 1)



		{

			list500m.push_back(listNODE[i]);



			count500m++;







		}







	}











	//check 500m	



	bool untac = 0;



	if (double(count500m) >= double(num)*0.7)untac = 1;



	if (untac == 0)



	{



		cout << " -1 -";







		int yes = 0;



		for (int i = 0; i < listNODE.size(); i++)



		{



			double d; int thoa = 0;



			LNR_check_R1_to_R2(listNODE[i].avl.getRoot(), lo, la, 0, 2.0, time1, time2, thoa, d);



			if (thoa == 1) { cout << " " << listNODE[i].id; yes = 1; }



		}



		if (yes == 0)cout << " -1";



		cout << endl;



	}



	else



	{















		double ret = -1; int thoa = 0;



		vector<string> SList;



		vector<string> NSList;



		vector<double>d; //List chua khoang cach so voi tram tuong ung voi SList















		for (int i = 0; i < listNODE.size(); i++)



		{



			ret = -1; thoa = 0;



			LNR_checkControled(listNODE[i].avl.getRoot(), lo, la, 1.0, time1, time2, thoa);



			if (thoa == 0)



			{



				LNR_check_R1_to_R2(listNODE[i].avl.getRoot(), lo, la, 1.0, 2.0, time1, time2, thoa, ret);



				if (thoa == 1)



				{



					string t = listNODE[i].id;



					NSList.push_back(t);



					d.push_back(ret);







				}











			}



			else



			{



				string t = listNODE[i].id;



				SList.push_back(t);







			}







		}



		//sap xep theo thu tu uu tien 1km-2km xa nhat	



		sort_distance_vs_station(NSList, d, la, lo);



		int realNSsize = int(0.75*NSList.size());



		while (NSList.size() > realNSsize)//xoa bot 



		{

			SList.push_back(NSList[NSList.size() - 1]);



			NSList.pop_back();



		}







		//sort lai theo id







		for (int i = 0; i < SList.size() - 1; i++)



		{



			for (int j = i + 1; j < SList.size(); j++)



			{



				if (SList[i] > SList[j])



				{



					SList[i].swap(SList[j]);



				}



			}



		}



		//in stuck



		if (SList.size() == 0)cout << " -1";



		else



		{



			for (int i = 0; i < SList.size(); i++)



			{



				cout << " " << SList[i];



			}



		}











		cout << " -";



		//sort lai theo id







		for (int i = 0; i < NSList.size() - 1; i++)



		{



			for (int j = i + 1; j < NSList.size(); j++)



			{



				if (NSList[i] > NSList[j])



				{



					NSList[i].swap(NSList[j]);



				}



			}



		}



		if (NSList.size() == 0)cout << " -1";



		else



		{



			for (int i = 0; i < NSList.size(); i++)



			{



				cout << " " << NSList[i];



			}



		}



		cout << endl;



	}



	return true;



}

bool request8(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL, vector<NODE>& Data89, void *pGData)



{



	double la, lo, R;



	int  timetemp;



	stringstream t(request.params[0]), t1(request.params[1]), t2(request.params[2]), t3(request.params[3]);



	t >> lo;	t1 >> la;	t2 >> R;	t3 >> timetemp;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "")

	{

		cout << "8: 0" << endl; return true;

	}



	if (request.sizePram != 4)return false;



	//print request



	cout << request.code << ":";





	//time



	struct tm * timeinfo;



	time_t Time;



	time(&Time);



	timeinfo = localtime(&Time);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;



	timeinfo->tm_hour = timetemp / 100;



	timeinfo->tm_min = timetemp % 100;



	timeinfo->tm_sec = 0;  //Note



	Time = mktime(timeinfo);



	time_t time2 = Time + 59;



	//



	if (Data89.size() == 0)



	{



		AVL.add_into_vector(Data89);



	}



	int them = 0;



	for (int i = 0; i < Data89.size(); i++)



	{



		int thoa = 0;



		if (Data89[i].out == false)



		{



			LNR_checkControled(Data89[i].avl.getRoot(), lo, la, R, Time, time2, thoa);



			if (thoa == 1)



			{



				them = 1;



				cout << " " << Data89[i].id;



				Data89[i].out = true;



				AVL.remove(Data89[i]);



			}



		}



		else continue;



	}



	if (them == 0)cout << " 0";



	cout << endl;



	return true;



}

bool request9(VM_Request &request, L1List<VM_Record> &recordList, AVLTree<NODE> &AVL, vector<NODE>& Data89, void *pGData)



{



	double la, lo, R;



	int  timetemp;



	stringstream t(request.params[0]), t1(request.params[1]), t2(request.params[2]), t3(request.params[3]);



	t >> lo;	t1 >> la;	t2 >> R;	t3 >> timetemp;

	if (request.params[request.sizePram - 1] == "" || request.params[request.sizePram - 1] == "!") {



		return false;



	}if (request.params[0] == "" || request.params[1] == "" || request.params[2] == "")

	{

		cout << "9: 0" << endl; return true;

	}



	if (request.sizePram != 4)return false;



	//print request



	cout << request.code << ":";



	//time





	struct tm * timeinfo;



	time_t Time;



	time(&Time);



	timeinfo = localtime(&Time);



	timeinfo->tm_mday = 5; //Note



	timeinfo->tm_mon = 12 - 1;



	timeinfo->tm_year = 2016 - 1900;



	timeinfo->tm_hour = timetemp / 100;



	timeinfo->tm_min = timetemp % 100;



	timeinfo->tm_sec = 0;  //Note



	Time = mktime(timeinfo);



	time_t time2 = Time + 59;



	// check va phuc hoi



	if (Data89.size() == 0)



	{



		AVL.add_into_vector(Data89);



	}



	int xoa = 0;



	for (int i = 0; i < Data89.size(); i++)



	{



		int thoa = 0;



		if (Data89[i].out == true)



		{



			LNR_checkControled(Data89[i].avl.getRoot(), lo, la, R, Time, time2, thoa);



			if (thoa == 1)



			{



				xoa = 1;



				cout << " " << Data89[i].id;



				Data89[i].out = false;



				AVL.insert(Data89[i]);



			}



		}



		else continue;



	}



	if (xoa == 0)cout << " " << 0;



	cout << endl;



	return true;



}

bool processRequest(VM_Request &request, L1List<VM_Record> &recordList, vector<NODE>& Data89, AVLTree<NODE>& AVL, void *pGData)



{



	if (request.code[0] == '1') { return request1(request, recordList, AVL); }



	if (request.code[0] == '2') { return request2(request, recordList, AVL, Data89); }



	if (request.code[0] == '3') { return request3(request, recordList, AVL, Data89); }



	if (request.code[0] == '4') { return request4(request, recordList, AVL); }



	if (request.code[0] == '5') { return request5(request, recordList, AVL); }



	if (request.code[0] == '6') { return request6(request, recordList, AVL); }



	if (request.code[0] == '7') { return request7(request, recordList, AVL); }



	if (request.code[0] == '8') { return request8(request, recordList, AVL, Data89, pGData); }



	if (request.code[0] == '9') { return request9(request, recordList, AVL, Data89, pGData); }



	return false;



}

