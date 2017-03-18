#pragma once

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

//Truong define may cai gioi han vo day
#define LIMIT_DEC_EXPO_OVERFLOW -4965
#define BIN 2
#define DEC 10
#define EXPO 15
#define HEX 16
#define SIGN 112
#define MAX_BITS 128
#define LIMIT_DEC_EXPO_STANDARD 4931
#define BIAS 16383

//Bieu dien so thap phan: thapPhan * 10 ^ luyThua
struct SoThapPhan {
	double thapPhan;
	int luyThua;
};

class QNumber
{
protected:
	//Mang luu 128 bit trong so lon
	//bit 0: la bit 0 cua data[0]
	//bit 1: la bit 1 cua data[0]
	//bit 7: la bit 7 cua data[0]
	//bit 8: la bit 0 cua data[1]
	//...
	char data[16];

	//coSo luu tru co so dang luu tru
	//2 : co so 2
	//10: co so 10
	//16: co so 16
	int coSo;
protected:
	//ham so sanh tren he 10, ho tro hai ham cong va tru tren co so 10
	static int cmp(string a, string b);

	//a + b (tinh o he co so 10)
	//Luu y: ca a va b deu phai cung la so nguyen duong
	static string congDec(string a, string b);

	// a - b (tinh o he co so 10)
	//Luu y: ca a va b deu phai cung la so nguyen duong
	static string truDec(string a, string b);

	//gan bit tai vi tri pos = value
	void ganBit(int pos, int value);
public:
	QNumber();
	virtual string getValue() = 0;
	virtual void setCoSo(int so);
	virtual int getCoSo();
	virtual ~QNumber();
};

