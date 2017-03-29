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

	//Sau do tinh 2 ^ luyThua => 10 ^ x, x len nen goi v1 = 10 ^ (phan thap phan cua x)
	//Nhan phan thap phan sau khi lay log de nhan voi v (y la v = v1 * v) 
	//Luu y: 15 bit luu so mu bieu dien o dang so Bias
	SoThapPhan BinToDec(string bin) const;

	//Tai
	//Ham chuyen tu dec sang day bin
	//Ham QFloat co goi ham nay thi sau khi chuan hoa, 2 string trong QFloat co the chuyen ve SoThapPhan de luu
	//Luu y: 15 bit luu so mu bieu dien o dang so Bias
	//Dang Chuan
	string DecToBin(SoThapPhan dec) const;
	//Dang Khong Chuan
	string DecToBinU(SoThapPhan dec) const;

	//Lay bit tai vi tri pos
	char getBit(int pos) const;

	//Truong
	//ham lay bieu dien cua QFloat hien tai thanh chuoi nhi phan (2)
	//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
	//string luu bit cao nhat tai vi tri 0
	//Luu y: 15 bit luu so mu bieu dien o dang so Bias
	string getBin() const;

	//Truong
	//ham lay bieu dien cua QFloat hien tai thanh chuoi thap phan (10) 
	//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
	//Luu y: 15 bit luu so mu bieu dien o dang so Bias
	string getDec() const;

	//lay gia tri cua QFloat hien tai, bieu dien theo coSo hien tai
	string getValue();

	//kiem tra QFloat co bang khong
	bool equalTo0() const;

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
	string getOutHex(string bin);

	~QFloat();
};

