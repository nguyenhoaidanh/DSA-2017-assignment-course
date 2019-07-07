#include <iostream>

#include "dsaLib.h"
#include "requestLib.h"
#include "dbLib.h"

using namespace std;



/// This function displays the content of database
void display(L1List<VM_Record>& bList) {
    cout.flush();
    bList.traverse(printVMRecord);
}

int main(int narg, char** argv) {
    L1List<VM_Request>  requestList;
    L1List<VM_Record>   db;
	clock_t begin = clock();
    loadRequests("requests.txt", requestList);
    
	loadVMDB("data50k.csv", db);
    cout << fixed << setprecision(12);// preset for floating point numbers

    process(requestList, db);

    cout << resetiosflags(ios::showbase) << setprecision(-1);
	clock_t end = clock(); //ghi lại thời gian lúc sau
	cout << "\nTime run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
	system("pause");
    return 0;
}