#pragma once
#include "QInt.h"

//QFloat: bieu dien so thuc lon 128 bit
class QFloat : public QNumber
{
private:
	//doi so de khoi tao
	SoThapPhan valueOf(string thapPhan, string mu);

	//ham chuan hoa gia tri nhap vao ve dang a.bcd * 10 ^ x.
	//ket qua luu thang vao soThapPhan, soMu (truyen kieu tham bien)
	void chuanHoaDec(string &soThapPhan, string &soMu);

	void chuanHoaThapPhanBin(string &bin) const;

	//dua day bit b vao so QFloat
	QFloat BinToQFloat(string b) const;

	QFloat convertToQFloat(string significand, int expo) const;
public:
	QFloat();
	QFloat(const QFloat &number);

	//Chuyen so dang (soThapPhan * 10 ^ soMu) ve dang bieu dien nhi phan
	QFloat(int so, string soThapPhan, string soMu);

	//Ham chuyen tu day bin sang SoThapPhan
	SoThapPhan BinToDec(string bin) const;

	//Ham chuyen tu dec sang day bin
	//Dang Chuan
	string DecToBin(SoThapPhan dec) const;
	//Dang Khong Chuan
	string DecToBinU(SoThapPhan dec) const;

	//Lay bit tai vi tri pos
	char getBit(int pos) const;

	//ham lay bieu dien cua QFloat hien tai thanh chuoi nhi phan (2)
	//string luu bit cao nhat tai vi tri 0
	string getBin() const;

	//ham lay bieu dien cua QFloat hien tai thanh chuoi thap phan (10) 
	string getDec() const;

	//lay gia tri cua QFloat hien tai, bieu dien theo coSo hien tai
	string getValue();

	//kiem tra QFloat co bang khong
	bool equalTo0() const;

	//chuyen tu nhi phan sang thap phan theo yeu cau
	QFloat BinToDec(bool *bit);

	//chuyen tu thap phan sang nhi phan theo yeu cau
	bool* DecToBin(QFloat x);

	//lay gia tri thap phan cua phan mu
	int getExpo() const;

	string getSignificand() const;

	//Cac ham phep tinh tren QInt (thuc hien tren co so 2)
	QFloat operator + (const QFloat& number) const;
	QFloat operator - (const QFloat& number) const;
	QFloat operator * (const QFloat& number) const;
	QFloat operator / (const QFloat& number) const;

	QFloat& operator = (const QFloat& number);

	string getOutBin(string bin);

	~QFloat();
};

