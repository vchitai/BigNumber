#pragma once
#include "QInt.h"

//QFloat: bieu dien so thuc lon 128 bit
class QFloat : public QNumber
{
private:
	//chuyen sang String
	string toString(int dec) const;
	//doi so de khoi tao
	SoThapPhan valueOf(string thapPhan, string mu);

	//Tai
	//ham chuan hoa gia tri nhap vao ve dang a.bcd * 10 ^ x.
	//ket qua luu thang vao soThapPhan, soMu (truyen kieu tham bien)
	//luu y cac truong hop sau:
	//1: khong co dau '.', them vao cuoi xau ".0"
	//2: dang abcd.efgh * 10 ^ x => a.bcdefgh * 10^y (y != x)
	//3: dang 0.000abc * 10 ^ x => a.bc * 10^y (y != x)
	//soMu nho nen chuyen soMu ve dang so nguyen roi cong tru tren soMu luon
	void chuanHoaDec(string &soThapPhan, string &soMu);

	void chuanHoaThapPhanBin(string &bin) const;

	QFloat BinToQFloat(string b) const;
public:
	QFloat();
	QFloat(const QFloat &number);

	//Tai
	//Chuyen so dang (soThapPhan * 10 ^ soMu) ve dang bieu dien nhi phan
	//Dau tien phai chuan hoa so nhap vao ve dang: a.bcd * 10 ^ x, goi ham chuan hoa tren
	//Kiem tra xem so nhap vao
	//1: O dang chua
	//2: O dang khong chuan
	//3: bi tran so
	//Cach chuyen: Sau khi chuan hoa co dang a.bcd * 10 ^ x
	//Ap dung may cong thuc log de tinh, luu y chuyen a.bcd thanh so roi nhan voi phan le cua 10 ^ x sau khi chuyen thanh log
	//Luu y: 15 bit luu so mu bieu dien o dang so Bias
	QFloat(int so, string soThapPhan, string soMu);

	//Truong
	//Chi lay 30 bit dau trong 112 bit bieu dien de tinh ra phan thap phan (goi gia tri la v)
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

	string getValue();

	//Cac ham phep tinh tren QInt (thuc hien tren co so 2)
	QFloat operator + (const QFloat& number) const;
	QFloat operator - (const QFloat& number) const;
	QFloat operator * (const QFloat& number) const;
	QFloat operator / (const QFloat& number) const;

	QFloat& operator = (const QFloat& number);

	~QFloat();
};

