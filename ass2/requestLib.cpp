#include "requestLib.h"
void loadRequests(char* fName, L1List<VM_Request> &rList)
{

	ifstream file(fName);

	if (file)

	{

		string temp, temp1, code, params;

		int  pos;

		getline(file, temp, ';');

		stringstream t(temp);

		while (!t.eof())

		{

			t >> temp1; VM_Request vm;

			

			bool t = 0; //t=1 => cuoi la _

			if (temp1[temp1.length() - 1] == '_') { temp1.erase(temp1.length() - 1, 1); t = 1; }

			pos = temp1.find("_");

			if (pos == -1 && t == 0) {//truong hop 1       2    ....
				strncpy(vm.code, temp1.data(), REQUEST_CODE_SIZE - 1);
				vm.params[vm.sizePram++] = "!"; rList.push_back(vm); continue;
			}

			if (pos == -1 && t == 1) { //truong hop 1_ 2_ 3_   ....
				strncpy(vm.code, temp1.data(), REQUEST_CODE_SIZE - 1);
				vm.params[vm.sizePram++] = ""; rList.push_back(vm); continue;
			}

			//copy code

			code = temp1.substr(0, pos);		strncpy(vm.code, code.data(), REQUEST_CODE_SIZE - 1);

			temp1.erase(0, pos + 1);

			pos = temp1.find("_");


			while (pos != -1)

			{	//lap copy param

				params = temp1.substr(0, pos);

				vm.params[vm.sizePram++] = params;

				temp1.erase(0, pos + 1);

				pos = temp1.find("_");

			}

			//lay param last

			params = temp1.substr(0, pos);

			vm.params[vm.sizePram++] = params;

			if (t)vm.params[vm.sizePram++] = "";//Cui thua dau "_" thi them "" vao cui

			rList.push_back(vm);

		}

	}

	else cout << "File request not found";

	file.close();

}