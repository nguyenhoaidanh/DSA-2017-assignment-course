#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H
 #include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>


using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:
	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}
	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T> *pNext;
	L1Item() : pNext(NULL) {}
	L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
public:
	L1Item<T>   *_pHead;// The head pointer of linked list
	L1Item<T>   *_pLast;
	size_t      _size;// number of elements in this list

	L1List() : _pHead(NULL), _pLast(NULL), _size(0) {}
	~L1List() {};
	void  clean()
	{
		return;
	}
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T&      at(int i);
	T&      operator[](int i);

	bool    find(T a, int& idx);
	bool    findId(char a[]);
	int     insert(int i, T& a);
	int     remove(int i);
	int     push_back(T& a);
	int     insertHead(T& a);
	int     removeHead();
	int     removeLast();
	void    reverse();
	void    traverse(void(*op)(T&)) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, void*), void* pParam) {
		L1Item<T>   *p = _pHead;
		while (p) {
			op(p->data, pParam);
			p = p->pNext;
		}
	}
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
	if (_pHead == NULL) {
		_pHead = new L1Item<T>(a);
		_pLast = _pHead;
	}
	else {
		
		_pLast->pNext = new L1Item<T>(a);
		_pLast = _pLast->pNext;
	}
	_size++;
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
	L1Item<T>   *p = new L1Item<T>(a);
	p->pNext = _pHead;
	_pHead = p;
	_size++;
	return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
	if (_pHead) {
		L1Item<T>* p = _pHead;
		_pHead = p->pNext;
		delete p;
		_size--;
		return 0;
	}
	return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
	if (_pHead) {
		if (_pHead->pNext) {
			L1Item<T>* prev = _pHead;
			L1Item<T>* pcur = prev->pNext;
			while (pcur->pNext) {
				prev = pcur;
				pcur = pcur->pNext;
			}
			delete pcur;
			prev->pNext = NULL;
		}
		else {
			delete _pHead;
			_pHead = NULL;
		}
		_size--;
		return 0;
	}
	return -1;
}
template <class T>
int L1List<T>::remove(int i) // i =0 to size
{
	if (_pHead) {
		if (i == 0)
		{
			L1Item<T>* pDel = _pHead;
			_pHead = _pHead->pNext;
			delete pDel; pDel = NULL;
			_size--;
		}
		else {
			L1Item<T>*p = _pHead;
			L1Item<T>*pPre = NULL;
			for (int j = 1; j < i; j++)
			{
				pPre = p;
				p = p->pNext;

			}
			pPre->pNext = p->pNext;
			delete p; p = NULL;
			_size--;
		}
		return 0;
	}
	else return -1;
}
template <class T>
int L1List<T>::insert(int i, T& a) //chen sau vi tri index i (0->size) , i=0 => chen dau
{
	
	return -1;
}
template <class T>
void L1List<T>::reverse()
{
	L1List<T>* ListTemp = new L1List<T>;
	L1Item<T>*p = this->_pHead;
	while (p)
	{
		ListTemp->insertHead(p->data);
		p = p->pNext;
	}
	L1Item<T>*p1 = ListTemp->_pHead;
	L1Item<T>*p2 = this->_pHead;

	while (p1)
	{
		p2->data = p1->data;
		p2 = p2->pNext;
		p1 = p1->pNext;
	}
}
template <class T>
bool L1List<T>::findId(char a[])
{
	L1Item<T>* p=this->_pHead;
	for (int i = 0;; i++)
	{
		if (p == NULL)break;
		if (strcmp(p->data.id,a)==0)
		{
			return true ; break;
		}
		p = p->pNext;
	}
	return false;
}

template <class T>
bool L1List<T>::find(T a, int& idx)
{
	L1Item<T>*p = this->_pHead;
	for (int i = 0;; i++)
	{
		if (p == NULL)break;
		if (p->data == a)
		{
			return true; idx = i; break;
		}
		p = p->pNext;
	}
	return false;
}
template <class T>
T& L1List<T>::at(int i)
{
	L1Item<T>*p = this->_pHead;
	for (int j = 0;; j++)
	{
		if (p == NULL)break;
		if (j == i)return p->data;
		p = p->pNext;
	}
}
template <class T>
T&  L1List<T>:: operator[](int i)
{
	L1Item<T>*p = this->_pHead;
	for (int j = 0; ; j++)
	{
	
		if (j == i)return p->data;
		p = p->pNext;
	}
}
#endif //A01_LISTLIB_H