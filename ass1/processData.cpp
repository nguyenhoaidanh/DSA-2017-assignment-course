#include "eventLib.h"
#include "dbLib.h"
struct point

{
	double x, y;
};
bool diChuyen(double Ya, double Xa, double Yc, double Xc)

{

	if (distanceEarth(Ya, Xa, Yc, Xc) > 5.0 / 1000.0)

		return true;

	else return false;

}

double sumQuangDuongDichuyen(char ninja[], L1Item<NinjaInfo_t>*start)

{

	double sum = 0;

	int thoa = -1;

	int find = 0; int thoat = 0;

	L1Item<NinjaInfo_t>*p = start; L1Item<NinjaInfo_t>*p1 = p;



	while (p)

	{

		thoa = 0;

		if (strcmp(ninja, p->data.id) == 0)// find lan dàu

		{



			find = 1;

			p1 = p->pNext;

			while (p1)

			{



				if (strcmp(ninja, p1->data.id) == 0) // l?n k? ti?p

				{

					sum += distanceEarth(p->data.latitude, p->data.longitude, p1->data.latitude, p1->data.longitude);

					p = p1; thoa = 1; break;





				}



				p1 = p1->pNext;

			}

		}

		if (p1 == NULL)break;

		if (thoa != 1)p = p->pNext;

	}

	if (find == 0)return -1;

	else return sum;

}

int sumThoiGianDichuyen(char ninja[], L1Item<NinjaInfo_t>*start)

{

	int sum = 0;

	int thoa = -1;

	int find = 0; int thoat = 0;

	L1Item<NinjaInfo_t>*p = start; L1Item<NinjaInfo_t>*p1 = p;

	while (p)

	{

		thoa = 0;

		if (strcmp(ninja, p->data.id) == 0)// find lan dàu

		{

			find = 1;

			p1 = p->pNext; L1Item<NinjaInfo_t>*pPre = p;

			while (p1)

			{

				if (strcmp(ninja, p1->data.id) == 0) // l?n k? ti?p

				{

					if (diChuyen(p->data.latitude, p->data.longitude, p1->data.latitude, p1->data.longitude))

					{

						sum += p1->data.timestamp - pPre->data.timestamp;

						p = p1; thoa = 1; break;

					}

					pPre = p1;

				}



				p1 = p1->pNext;

			}

		}

		if (p1 == NULL)break;

		if (thoa != 1)p = p->pNext;

	}

	if (find == 0)return -1;

	else return sum;

}

int sumThoiGianDungLai(char ninja[], L1Item<NinjaInfo_t>*start)

{

	int sum = 0;

	int thoa = -1;

	int find = 0;

	L1Item<NinjaInfo_t>*p = start;
	L1Item<NinjaInfo_t>*p1 = p;
	L1Item<NinjaInfo_t>*pDau = start->pNext; if (pDau == NULL)return 0;
	while (pDau) { if (strcmp(ninja, pDau->data.id) == 0)break; pDau = pDau->pNext; }
	if (pDau == NULL)return 0;
	if (!diChuyen(start->data.latitude, start->data.longitude, pDau->data.latitude, pDau->data.longitude)) { sum += pDau->data.timestamp - start->data.timestamp; }
	L1Item<NinjaInfo_t>*pre = p;

	while (p)

	{

		thoa = 0;

		if (strcmp(ninja, p->data.id) == 0)// find lan dàu

		{

			find = 1;

			p1 = p->pNext;

			while (p1)

			{

				if (strcmp(ninja, p1->data.id) == 0) // l?n k? ti?p

				{

					if (diChuyen(p->data.latitude, p->data.longitude, p1->data.latitude, p1->data.longitude))

					{
						pre = p1;

						p = p1; thoa = 1; break;

					}

					else
					{
						if (p == start&&p1 == pDau) { pre = p1; p1 = p1->pNext; continue; }
						sum += p1->data.timestamp - pre->data.timestamp; pre = p1;
					}




				}

				p1 = p1->pNext;

			}

		}

		if (p1 == NULL)break;

		if (thoa != 1)p = p->pNext;

	}

	if (find == 0)return -1;

	else { return sum; }

}

bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {

	int n = nList._size;



	if (strcmp(event.code, "0") == 0)



	{



		return true;



	}



	//////////////////// 1



	else if (strcmp(event.code, "1") == 0)



	{



		// id d?u







		return true;



	}



	/////////////////////////2



	else if (strcmp(event.code, "2") == 0)



	{// id ninja cu?i







		return true;



	}



	/////////////////////////3



	else if (strcmp(event.code, "3") == 0)



	{//so luong ninja tham gia cuoc thi



		cout << "3: ";



		L1List<NinjaInfo_t> list;



		L1Item<NinjaInfo_t>*p = nList._pHead;



		while (p)



		{



			L1Item<NinjaInfo_t>*p1 = list._pHead;



			int find = 0;



			while (p1)



			{



				if (strcmp(p->data.id, p1->data.id) == 0)



				{



					find = 1; break;



				}



				p1 = p1->pNext;



			}



			if (find == 0)



			{



				NinjaInfo_t p2;



				strncpy(p2.id, p->data.id, ID_MAX_LENGTH - 1);



				list.insertHead(p2);



			}



			p = p->pNext;



		}



		cout << list._size << endl;



		return true;



	}



	///////////////////////////4



	else if (strcmp(event.code, "4") == 0)



	{



		cout << "4: "; char maxId[ID_MAX_LENGTH];



		strncpy(maxId, nList[0].id, ID_MAX_LENGTH - 1);



		L1Item<NinjaInfo_t>*p = nList._pHead;



		while (p)



		{



			if (strcmp(p->data.id, maxId) > 0) { strncpy(maxId, p->data.id, ID_MAX_LENGTH - 1); }



			p = p->pNext;



		}



		cout << (maxId) << endl;



		return true;



	}



	///////////////////9



	else if (strcmp(event.code, "9") == 0)



	{



		cout << "9: ";

		if (nList._pHead == NULL) { cout << -1 << endl; return true; }

		double sumMax = -1.0;



		string idx;



		char** arr = new char*[n];



		int sizeArr = 0;



		int find;



		L1Item<NinjaInfo_t>*p = nList._pHead;



		while (p)



		{



			find = 0;



			for (int z = sizeArr - 1; z >= 0; z--)



			{



				if (strcmp(arr[z], p->data.id) == 0)



				{



					find = 1;



					break;



				}



			}



			if (find != 1)



			{



				arr[sizeArr] = p->data.id;



				sizeArr++;



				double sum = 0;



				sum = sumQuangDuongDichuyen(p->data.id, p);



				if (sum > sumMax) { sumMax = sum; idx = p->data.id; }



			}



			p = p->pNext;



		}



		cout << (idx) << endl;



		return true;



	}



	/////////////////10



	else if (strcmp(event.code, "10") == 0)



	{



		cout << "10: ";

		if (nList._pHead == NULL) { cout << -1 << endl; return true; }

		int sumMax = -1;



		string idx;



		char** arr = new char*[n];



		int sizeArr = 0;



		int find;



		L1Item<NinjaInfo_t>*p = nList._pHead;



		while (p)



		{



			find = 0;



			for (int z = sizeArr - 1; z >= 0; z--)



			{



				if (strcmp(arr[z], p->data.id) == 0)



				{



					find = 1;



					break;



				}



			}



			if (find != 1)



			{



				arr[sizeArr] = p->data.id;



				sizeArr++;



				int sum = 0;



				sum = sumThoiGianDichuyen(p->data.id, p);



				if (sum > sumMax) { sumMax = sum; idx = p->data.id; }



			}



			p = p->pNext;



		}



		cout << (idx) << endl;



		return true;



	}



	//////////////////12



	else if (strcmp(event.code, "12") == 0)



	{



		cout << "12: ";

		if (nList._pHead == NULL) { cout << -1 << endl; return true; }

		int sumMax = -1;



		string idx;



		char** arr = new char*[n];



		int sizeArr = 0;



		int find;



		L1Item<NinjaInfo_t>*p = nList._pHead;



		while (p)



		{



			find = 0;



			for (int z = sizeArr - 1; z >= 0; z--)



			{



				if (strcmp(arr[z], p->data.id) == 0)



				{



					find = 1;



					break;



				}



			}



			if (find != 1)



			{



				arr[sizeArr] = p->data.id;



				sizeArr++;



				int sum = 0;



				sum = sumThoiGianDungLai(p->data.id, p);



				if (sum > sumMax) { sumMax = sum; idx = p->data.id; }



			}



			p = p->pNext;



		}



		cout << (idx) << endl;



		return true;



	}



	//////////14



	else if (strcmp(event.code, "14") == 0)

	{

		cout << "14: ";
		if (nList._pHead == NULL) { cout << -1 << endl; return true; }
		L1Item<NinjaInfo_t>*idx = NULL;
		char** arr1 = new char*[n];
		int sizeArr1 = 0;
		char** arr = new char*[n];
		int sizeArr = 0;
		int find; int yes = 0; int thoa = -1;
		L1Item<NinjaInfo_t>*p = nList._pHead;
		while (p)
		{
			find = 0;
			for (int z = sizeArr - 1; z >= 0; z--)
			{
				if (strcmp(arr[z], p->data.id) == 0)
				{
					find = 1;
					break;
				}
			}
			if (find != 1)
			{
				point Point[86400];
				int numPoint = 0;
				arr[sizeArr] = p->data.id;
				sizeArr++;
				////////////////////////
				int thoat = 0;
				idx = p;
				L1Item<NinjaInfo_t>*diemcui = NULL;
				L1Item<NinjaInfo_t>*pR = p->pNext;
				while (pR)
				{
					if (strcmp(idx->data.id, pR->data.id) == 0)diemcui = pR;
					pR = pR->pNext;
				}
				if (diemcui == NULL) { p = p->pNext; continue; }

				Point[numPoint].x = p->data.latitude; Point[numPoint].y = p->data.longitude; numPoint++;


				while (idx)
				{
					int thoat2 = 0;
					if (strcmp(idx->data.id, p->data.id) == 0)
					{
						if (!diChuyen(Point[numPoint - 1].x, Point[numPoint - 1].y, idx->data.latitude, idx->data.longitude))
						{
							idx = idx->pNext; continue;
						}
						Point[numPoint].x = idx->data.latitude; Point[numPoint++].y = idx->data.longitude;


						if (numPoint >= 3)
						{
							for (int i = numPoint - 3; i >= 0; i--)
							{



								if (!diChuyen(Point[i].x, Point[i].y, Point[numPoint - 1].x, Point[numPoint - 1].y) &&
									(!(i == 0 && idx == diemcui)))
								{

									arr1[sizeArr1++] = p->data.id; yes = 1; thoat2 = 1;  break;
								}



							}
						}
					}


					idx = idx->pNext; if (idx == diemcui)break; if (thoat2 == 1)break;
				}
			}
			p = p->pNext;
		}

		if (yes == 0)cout << -1 << endl;
		else
			for (int i = 0; i < sizeArr1; i++)
			{
				if (i != sizeArr1 - 1)

					cout << (arr1[i]) << " ";

				else

					cout << (arr1[i]) << endl;

			}

		return true;

	}

	/////////////////////5



	else if (strlen(event.code) > 1 && event.code[0] == '5')



	{



		char des[100];



		cout << event.code << ": ";
		if (strlen(event.code) < 5 || nList._pHead == NULL) { cout << -1 << endl; return true; }


		char ninja[ID_MAX_LENGTH];

		string a = event.code;
		a.erase(0, 1);
		strncpy(ninja, a.data(), ID_MAX_LENGTH - 1);





		L1Item<NinjaInfo_t>*p1 = nList._pHead;



		while (p1)



		{



			if (strcmp(ninja, p1->data.id) == 0)break;



			p1 = p1->pNext;



			if (p1 == NULL) { cout << -1 << endl; return true; }



		}















		int find = 0;



		L1Item<NinjaInfo_t>*p2 = p1->pNext;

		if (p2 == NULL) {
			strPrintTime(des, p1->data.timestamp);



			cout << des << endl; return true;
		}



		while (p2)



		{



			if (strcmp(ninja, p2->data.id) == 0)break;



			p2 = p2->pNext;

			if (p2 == NULL) {
				strPrintTime(des, p1->data.timestamp);



				cout << des << endl; return true;
			}



		}











		if (diChuyen(p1->data.latitude, p1->data.longitude,



			p2->data.latitude, p2->data.longitude))



		{



			find = 1;



			strPrintTime(des, p1->data.timestamp);



			cout << des << endl; return true;



		}



		///////////////////////







		bool run = 0;



		L1Item<NinjaInfo_t>*p = p1->pNext;



		while (p)



		{



			if (strcmp(ninja, p->data.id) == 0)//ninja dc tim



			{







				find = 1;



				if (diChuyen(p1->data.latitude, p1->data.longitude,



					p->data.latitude, p->data.longitude))



				{
					run = 1;



					break;



				}



			}



			p = p->pNext;



		}







		if (find != 0)



		{
			if (run == 0) { cout << "empty" << endl; return true; }



			strPrintTime(des, p->data.timestamp);



			cout << des << endl;



		}



		else



			cout << -1 << endl;



		return true;



	}



	//////////////////////// 6



	else if (strlen(event.code) > 1 && event.code[0] == '6')



	{


		int k = 0; //k co diem dung
		cout << event.code << ": ";

		if (strlen(event.code) < 5 || nList._pHead == 0) { cout << -1 << endl; return true; }

		char ninja[ID_MAX_LENGTH];
		string a = event.code;
		a.erase(0, 1);
		strncpy(ninja, a.data(), ID_MAX_LENGTH - 1);




		int thoa = -1;



		int find = 0;



		L1Item<NinjaInfo_t>** arr = new L1Item<NinjaInfo_t>*[86400];



		int size = 0;



		L1Item<NinjaInfo_t>*pDau = nList._pHead; bool dau = 1;



		L1Item<NinjaInfo_t>*p = nList._pHead; L1Item<NinjaInfo_t>*p1 = p;



		while (p)



		{



			thoa = 0;



			if (strcmp(ninja, p->data.id) == 0)// find lan dàu



			{
				if (dau == 1) { pDau = p; dau = 0; }



				find = 1;



				p1 = p->pNext;



				while (p1)



				{



					if (strcmp(ninja, p1->data.id) == 0) // l?n k? ti?p



					{/////////////////////////



						if (diChuyen(p->data.latitude, p->data.longitude, p1->data.latitude, p1->data.longitude))



						{



							arr[size++] = p;



							p = p1; thoa = 1; break;



						}
						else k = 1;



					}



					p1 = p1->pNext;



				}



			}



			if (p1 == NULL)break;



			if (thoa != 1) { p = p->pNext; }



		}



		L1Item<NinjaInfo_t>*kq = NULL;



		if (find == 0)cout << -1 << endl;



		else



		{



			if (size == 0)

			{
				L1Item<NinjaInfo_t>*pRun = pDau->pNext;

				while (pRun)

				{

					if (strcmp(ninja, pRun->data.id) == 0)

					{
						char des[100];

						strPrintTime(des, pDau->data.timestamp);

						cout << des << endl;

						return true;

					}

					pRun = pRun->pNext;

				}

				cout << "Non-stop" << endl; return true;



			}

			if (k == 0) { cout << "Non-stop" << endl; return true; }









			L1Item<NinjaInfo_t>*pRun = arr[size - 1]->pNext;



			//kiem tra:



			// "|"	 | ....      1



			//  |	"|"	|     0 



			int aHayb = 0;



			while (pRun)



			{



				if (strcmp(pRun->data.id, ninja) == 0)



				{







					if (diChuyen(arr[size - 1]->data.latitude, arr[size - 1]->data.longitude, pRun->data.latitude, pRun->data.longitude))



					{



						break;



					}



				}



				pRun = pRun->pNext;



			}pRun = pRun->pNext;



			while (pRun)



			{



				if (strcmp(pRun->data.id, ninja) == 0)



				{



					aHayb = 1; break;



				}



				pRun = pRun->pNext;



			}







			if (aHayb == 1)



			{



				pRun = arr[size - 1]->pNext; kq = pRun;



				while (pRun)



				{



					if (strcmp(pRun->data.id, ninja) == 0)



					{



						if (diChuyen(arr[size - 1]->data.latitude, arr[size - 1]->data.longitude, pRun->data.latitude, pRun->data.longitude)) { kq = pRun; break; }







					}



					pRun = pRun->pNext;



				}











			}



			else



			{



				int i;



				for (i = size - 1; i >= 0; i--)



				{



					int yes = 0;



					pRun = arr[i]->pNext;



					while (pRun)



					{
						if (strcmp(pRun->data.id, ninja) == 0)



						{
							if (diChuyen(arr[i]->data.latitude, arr[i]->data.longitude, pRun->data.latitude, pRun->data.longitude))



								break; else { kq = arr[i]; yes = 1; break; }
						}







						pRun = pRun->pNext;



					}



					if (yes == 1)break;



				}











			}



			char des[100];



			strPrintTime(des, kq->data.timestamp);



			cout << des << endl;



		}



		return true;



	}



	//////////////////7



	else if (strlen(event.code) > 1 && event.code[0] == '7')



	{



		cout << event.code << ": ";
		if (strlen(event.code) < 5 || nList._pHead == NULL) { cout << -1 << endl; return true; }


		char ninja[ID_MAX_LENGTH];



		string a = event.code;
		a.erase(0, 1);
		strncpy(ninja, a.data(), ID_MAX_LENGTH - 1);



		int thoa = -1;



		int dem = 0; int find = 0;



		int thoat = 0; bool onetime = 1;



		L1Item<NinjaInfo_t>*p = nList._pHead;







		L1Item<NinjaInfo_t>*pP = nList._pHead;



		while (pP)



		{
			if (strcmp(pP->data.id, ninja) == 0) { break; }



			pP = pP->pNext; if (pP == NULL) { cout << -1 << endl; return true; }



		}



		L1Item<NinjaInfo_t>*pP1 = pP->pNext; if (pP1 == NULL) { cout << 0 << endl; return true; }



		while (pP1)



		{
			if (strcmp(pP1->data.id, ninja) == 0) { onetime = 0; break; }



			pP1 = pP1->pNext; if (pP1 == NULL) { cout << 0 << endl; return true; }



		}



		bool daudichuyen = 0;



		if (!diChuyen(pP->data.latitude, pP->data.longitude, pP1->data.latitude, pP1->data.longitude)) { onetime = 0; dem++; }



		else daudichuyen = 1;



		L1Item<NinjaInfo_t>*p1 = p;







		bool truocdichuyen = daudichuyen;



		while (p)



		{



			thoa = 0;



			if (strcmp(p->data.id, ninja) == 0)// find lan dàu



			{
				onetime = 0;



				find = 1;



				p1 = p->pNext;



				while (p1)



				{



					if (strcmp(p1->data.id, ninja) == 0) // l?n k? ti?p



					{







						if (diChuyen(p->data.latitude, p->data.longitude, p1->data.latitude, p1->data.longitude))



						{











							p = p1; truocdichuyen = 1; thoa = 1; break;



						}



						else



						{



							if (p == pP&&p1 == pP1) { p1 = p1->pNext; continue; }



							if (truocdichuyen == 1) { dem++; truocdichuyen = 0; }



						}











					}



					p1 = p1->pNext;



				}



			}



			if (p1 == NULL)break;



			if (thoa != 1)p = p->pNext;



		}



















		if (find == 0)cout << -1 << endl;



		else



		{ //if(onetime==1){cout<<1<<endl;return true;}



			cout << dem << endl;



		}



		return true;



	}



	//////////////////////////////8



	else if (strlen(event.code) > 1 && event.code[0] == '8')



	{



		cout << event.code << ": ";

		if (strlen(event.code) < 5 || nList._pHead == NULL) { cout << -1 << endl; return true; }

		char ninja[ID_MAX_LENGTH];



		string a = event.code;
		a.erase(0, 1);
		strncpy(ninja, a.data(), ID_MAX_LENGTH - 1);



		double sum = sumQuangDuongDichuyen(ninja, nList._pHead);



		if (sum != -1)cout << sum << endl;



		else cout << -1 << endl;



		return true;



	}



	//////////////////11



	else if (strlen(event.code) > 2 && event.code[0] == '1'&&event.code[0] == event.code[1])


	{
		cout << event.code << ": ";
		if (nList._pHead == NULL) { cout << -1 << endl; return true; }
		char ninja[ID_MAX_LENGTH]; string t = event.code; t.erase(0, 2);
		strncpy(ninja, t.data(), ID_MAX_LENGTH - 1); char id[ID_MAX_LENGTH];
		int find = 0;
		L1Item<NinjaInfo_t>*p1 = nList._pHead;
		int ti = 0;
		while (p1)
		{
			if (strcmp(p1->data.id, ninja) < 0)
			{
				strncpy(id, p1->data.id, ID_MAX_LENGTH - 1); ti = 1; break;
			}
			p1 = p1->pNext;
		}

		if (ti == 0)
		{
			cout << -1 << endl; return true;
		}
		L1Item<NinjaInfo_t>*p = nList._pHead;
		while (p)

		{







			if (strcmp(ninja, p->data.id) > 0 && strcmp(p->data.id, id) >= 0)



			{



				find = 1; strncpy(id, p->data.id, ID_MAX_LENGTH - 1);



			}







			p = p->pNext;



		}







		if (find == 0)cout << -1 << endl;



		else



			if (n != 1) {//Xoa ninja ra khoi cuoc thi		
						 //Xoa dau 

				L1Item<NinjaInfo_t>*pDel = NULL;
				while (nList._pHead != NULL&&strcmp(nList._pHead->data.id, id) == 0)
				{
					pDel = nList._pHead; nList._pHead = nList._pHead->pNext; n--; delete pDel; pDel = NULL;
				}
				if (nList._pHead == NULL) { cout << id << endl; return true; }
				pDel = nList._pHead;
				L1Item<NinjaInfo_t>*pPre = NULL;
				while (pDel)
				{
					if (strcmp(pDel->data.id, id) == 0)
					{
						pPre->pNext = pDel->pNext; n--;
						delete pDel; pDel = pPre->pNext;
						continue;
					}
					pPre = pDel;
					pDel = pDel->pNext;
				}
				nList._pLast = pPre;
				nList._pLast->pNext = NULL;
				cout << (id) << endl;
				return true;
			}
			else { cout << (id) << endl; n = 0; nList._pHead = nList._pLast = NULL; return true; }
			return true;



	}



	////////////////////13



	else if (strlen(event.code) >= 2 && event.code[0] == '1'&& event.code[1] == '3')



	{

		if (strlen(event.code) == 2)return false;





		return true;



	}



	return false;

}