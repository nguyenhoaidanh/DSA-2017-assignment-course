/*
* =========================================================================================
* Name        : dsaLib.h
* Author      : Duc Dung Nguyen
* Email       : nddung@hcmut.edu.vn
* Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
* Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
* =========================================================================================
*/

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

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

	~L1List() {}

	L1Item<T>* getHead()

	{

		return _pHead;

	}
	void    clean() {}
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T&      at(int i) {
		L1Item<T>*p = this->_pHead;
		for (int j = 0;; j++)
		{

			if (j == i)return p->data;
			p = p->pNext;
		}

	}

	T&      operator[](int i) {
		L1Item<T>*p = this->_pHead;
		for (int j = 0; ; j++)
		{

			if (j == i)return p->data;
			p = p->pNext;
		}
	}

	bool    find(T& a, int& idx) {}
	T*      find(T& a) {}
	T*      findLast(T& a) {}
	int     insert(int i, T& a) {}
	int     remove(int i) //remove node data 
	{
	}
	int     removeAll(T& a) {}

	int     push_back(T& a);
	int     insertHead(T& a);

	int     removeHead();
	int     removeLast();

	void    reverse()
	{
		L1Item<T>*pRun = _pHead;
		L1List<T> temp;
		temp._pHead = NULL;
		while (pRun)
		{
			temp.insertHead(pRun->data);
			pRun = pRun->pNext;
		}
		_pHead = temp._pHead;
	}

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
int L1List<T>::push_back(T &a)
{
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

/************************************************************************
* This section is for AVL tree
************************************************************************/
enum Bfactor { LH = -1, EH = 0, RH = 1 };

template <class T>
struct AVLNode {
	T           _data;
	AVLNode<T>   *_pLeft, *_pRight;
	AVLNode() {}
	Bfactor _bFactor;
	AVLNode(T&a):_data(a),_pLeft(NULL) ,_pRight(NULL),_bFactor(EH ){}
};

template <class T>
class AVLTree {

public:
	AVLNode<T> *_pRoot;
	int AVLsize;
	AVLTree() : _pRoot(NULL), AVLsize(0) {}

	~AVLTree() { destroy(_pRoot); }

	bool find(T& key, T* &ret)
	{	//find theo id
		return find(_pRoot, key, ret);
	}
	bool insert(T& key) { return insert(_pRoot, key); }
	bool remove(T& key) { return remove(_pRoot, key); }
	
	void traverseLNR_Q4(void(*op)(T, double, double, double, time_t, time_t, int &), double lo, double la, double R, time_t time1, time_t time2, int & count)
	{
		traverseLNR_Q4(_pRoot, op, lo, la, R, time1, time2, count);
	}
	
	
	void add_into_vector(vector<T>& v) { add_into_vector(_pRoot, v); }

	AVLNode<T>* getRoot()
	{
		return _pRoot;
	}
	//protected:
public:

	void destroy(AVLNode<T>* &pR)
	{

	}
	bool find(AVLNode<T> *pR, T& key, T* &ret) //find theo id
	{
		if (pR == NULL) return false;


		if (key < pR->_data)
			return find(pR->_pLeft, key, ret);
		if (key > pR->_data)
			return find(pR->_pRight, key, ret);
		if (pR->_data == key)
		{
			ret = &pR->_data;
			return true;
		}
		return false;
	}

	bool insert(AVLNode<T>* &pR, T& a)
	{
		if (pR == NULL)
		{
			pR = new AVLNode<T>();
			pR->_pLeft = pR->_pRight = NULL;
			pR->_data = a;
			pR->_bFactor = EH;
			return true;
		}
		if (a < pR->_data)
		{
			//inserrt left
			if (insert(pR->_pLeft, a) == false)return false;
			return balanceLeft(pR);
		}
		else
		{
			//inserrt right
			if (insert(pR->_pRight, a) == false)return false;
			return balanceRight(pR);
		}
	}

	bool remove(AVLNode<T>* &pR, T& a)
	{
		if (pR == NULL)return false;
		if (a < pR->_data)
		{
			if (remove(pR->_pLeft, a) == false)return false;
			if (pR->_bFactor == LH) { pR->_bFactor = EH; return true; }
			if (pR->_bFactor == EH) { pR->_bFactor = RH; return false; }
			return !balanceRight(pR);
		}
		if (a > pR->_data)
		{
			if (remove(pR->_pRight, a) == false)return false;
			if (pR->_bFactor == RH) { pR->_bFactor = EH; return true; }
			if (pR->_bFactor == EH) { pR->_bFactor = LH; return false; }
			return !balanceLeft(pR);
		}

		if (pR->_pLeft == NULL&&pR->_pRight == NULL) { delete pR; pR = NULL; return true; }
		if (pR->_pLeft == NULL) { AVLNode<T>*p = pR; pR = pR->_pRight; delete p; return true; }
		if (pR->_pRight == NULL) { AVLNode<T>*p = pR; pR = pR->_pLeft; delete p; return true; }
		AVLNode<T>*p = pR->_pRight;
		while (p->_pLeft)p = p->_pLeft;
		pR->_data = p->_data;
		if (remove(pR->_pRight, p->_data))
		{
			if (remove(pR->_pRight, a) == false)return false;
			if (pR->_bFactor == RH) { pR->_bFactor = EH; return true; }
			if (pR->_bFactor == EH) { pR->_bFactor = LH; return false; }
		}
	}

	// su dung cho RQ4
	void traverseLNR_Q4(AVLNode<T> *pR, void(*op)(T, double, double, double, time_t, time_t, int &), double lo, double la, double R, time_t time1, time_t time2, int &count)
	{
		if (pR == NULL)return;

		if (pR->_pLeft)traverseLNR_Q4(pR->_pLeft, op, lo, la, R, time1, time2, count);
		op(pR->_data, lo, la, R, time1, time2, count);
		if (pR->_pRight)traverseLNR_Q4(pR->_pRight, op, lo, la, R, time1, time2, count);
	}
	
	void add_into_vector(AVLNode<T> *pR, vector<T>& v)
	{
		if (pR == NULL)return;
		if (pR->_pLeft)add_into_vector(pR->_pLeft, v);
		v.push_back(pR->_data);
		if (pR->_pRight)add_into_vector(pR->_pRight, v);
	}
	void rotLeft(AVLNode<T>* &pR)
	{
		if (pR == NULL)return;
		if (pR->_pRight == NULL)return;
		AVLNode<T>*p = pR->_pRight;
		pR->_pRight = p->_pLeft;
		p->_pLeft = pR;
		pR = p;
	}

	void rotRight(AVLNode<T>* &pR)
	{
		if (pR == NULL)return;
		if (pR->_pLeft == NULL)return;
		AVLNode<T>*p = pR->_pLeft;
		pR->_pLeft = p->_pRight;
		p->_pRight = pR;
		pR = p;
	}

	void rotLR(AVLNode<T>* &pR)
	{
		rotLeft(pR->_pLeft);
		rotRight(pR);
	}

	void rotRL(AVLNode<T>* &pR)
	{
		rotRight(pR->_pRight);
		rotLeft(pR);
	}

	bool balanceLeft(AVLNode<T>* &pR)
	{
		if (pR->_bFactor == EH) { pR->_bFactor = LH; return true; }
		if (pR->_bFactor == RH) { pR->_bFactor = EH; return false; }
		if (pR->_bFactor == LH)
		{//LL
			rotRight(pR);
			//them vo
			if (pR->_pRight)
				pR->_bFactor = pR->_pRight->_bFactor = EH;
			else pR->_bFactor = EH;

			return false;
		}
		//LR
		rotLR(pR);
		if (pR->_bFactor == LH)
		{
			pR->_bFactor = pR->_pLeft->_bFactor = EH;
			pR->_pLeft->_bFactor = RH; return false;
		}
		pR->_bFactor = pR->_pRight->_bFactor = EH;
		pR->_pLeft->_bFactor = LH;
		return false;
	}

	bool balanceRight(AVLNode<T>* &pR)
	{
		if (pR->_bFactor == EH) { pR->_bFactor = RH; return true; }
		if (pR->_bFactor == LH) { pR->_bFactor = EH; return false; }
		if (pR->_bFactor == RH)
		{//RR
			rotLeft(pR);
			if (pR->_pLeft)
				pR->_bFactor = pR->_pLeft->_bFactor = EH;
			else pR->_bFactor = EH;
			return false;
		}
		//RL
		rotRL(pR);
		if (pR->_bFactor == RH)
		{
			pR->_bFactor = pR->_pRight->_bFactor = EH;
			pR->_pRight->_bFactor = LH; return false;
		}
		pR->_bFactor = pR->_pLeft->_bFactor = EH;
		pR->_pRight->_bFactor = RH;
		return false;
	}
};

#endif //A02_DSALIB_H
