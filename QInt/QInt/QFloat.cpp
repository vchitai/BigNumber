#include "QFloat.h"

//gan bit tai vi tri pos = value
void QFloat::ganBit(int pos, int value)
{
	int i = pos / 8;
	int j = pos % 8;

	data[i] &= ~(1 << j);
	data[i] |= (value << j);
}

//ham so sanh tren he 10, ho tro hai ham cong va tru tren co so 10
int QFloat::cmp(string a, string b)
{
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	return (a == b ? 0 : (a > b ? 1 : -1));
}

//a + b (tinh o he co so 10)
//Luu y: ca a va b deu phai cung la so nguyen duong
string QFloat::congDec(string a, string b)
{
	int sum = 0, carry = 0;
	string c = "";
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	for (int i = a.size() - 1; i >= 0; --i) {
		sum = (a[i] - '0') + (b[i] - '0') + carry;
		carry = sum / 10;
		c = char('0' + sum % 10) + c;
	}
	if (carry > 0) c = '1' + c;
	return c;
}

// a - b (tinh o he co so 10)
//Luu y: ca a va b deu phai cung la so nguyen duong
string QFloat::truDec(string a, string b)
{
	int dau = 1;
	if (cmp(a, b) == -1) {
		dau = -1;
		swap(a, b);
	}
	int borrow = 0;
	string c = "";
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	for (int i = a.size() - 1; i >= 0; --i) {
		int sum = a[i] - b[i] - borrow;
		if (sum < 0) {
			sum = sum + 10;
			borrow = 1;
		}
		else
			borrow = 0;
		c = char(sum + '0') + c;
	}

	while (c.size() > 0 && c[0] == '0') {
		c.erase(0, 1);
	}
	if (dau == -1) c = '-' + c;
	return c;
}

string QFloat::toString(int dec) {
	string res;
	while (dec > 0) {
		res.push_back('0' + dec % 10);
		dec = dec / 10;
	}

	return res;
}

//Tai
//ham chuan hoa gia tri nhap vao ve dang a.bcd * 10 ^ x.
//ket qua luu thang vao soThapPhan, soMu (truyen kieu tham bien)
//luu y cac truong hop sau:
//1: khong co dau '.', them vao cuoi xau ".0"
//2: dang abcd.efgh * 10 ^ x => a.bcdefgh * 10^y (y != x)
//3: dang 0.000abc * 10 ^ x => a.bc * 10^y (y != x)
//soMu nho nen chuyen soMu ve dang so nguyen roi cong tru tren soMu luon
void QFloat::chuanHoaDec(string & soThapPhan, string & soMu)
{
	int cham = -1;
	for (int i = 0; i < soThapPhan.size(); i++)
		if (soThapPhan[i] == '.')
			cham = i;
	if (cham == -1)
		soThapPhan.append(".0");
	else if (cham != 1) {
		int lastOne = 1;
		if (soThapPhan[0] == '-') lastOne++;
		for (int i = cham; i > lastOne; i--)
			swap(soThapPhan[i], soThapPhan[i - 1]);
		soMu = congDec(soMu, toString(cham - 1));
	}
}

void QFloat::chuanHoaThapPhanBin(string& bin) {
	while (bin.size() < SIGN) {
		bin.append("0");
	}
}

QFloat::QFloat()
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0;
}

QFloat::QFloat(const QFloat & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
}

SoThapPhan QFloat::valueOf(string thapPhan, string mu) {
	SoThapPhan res;
	res.thapPhan = 0;
	int j = 0;
	int dau = 0;
	if (thapPhan[j] == '-') {
		j++;
		dau = 1;
	}
	double sauDauPhay = 0;
	for (; j < thapPhan.size(); j++) {
		if (thapPhan[j] == '.')
			break;
		else {
			res.thapPhan *= 10;
			res.thapPhan += thapPhan[j] - '0';
		}
	}
	for (int k = thapPhan.size() - 1; k > j; k--) {
		sauDauPhay += thapPhan[k];
		sauDauPhay /= 10;
	}
	res.thapPhan += sauDauPhay;
	if (dau == 1)
		res.thapPhan = -res.thapPhan;

	dau = 0;
	int i = 0;
	if (mu[i] == '-') {
		i++;
		dau = 1;
	}
	res.luyThua = 0;
	for (; i < mu.size(); i++) {
		res.luyThua *= 10;
		res.luyThua += mu[i] - '0';
	}
	if (dau == 1)
		res.luyThua = -res.luyThua;
}
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
QFloat::QFloat(string soThapPhan, string soMu)
{
	chuanHoaDec(soThapPhan, soMu);
	if (cmp(soMu, toString(LIMIT_DEC_EXPO_OVERFLOW)) == -1 || cmp(soMu, toString(LIMIT_DEC_EXPO_STANDARD)) == 1)
		coSo = -1;
	else if (cmp(soMu, toString(LIMIT_DEC_EXPO_OVERFLOW)) == 1 && cmp(soMu, toString(-LIMIT_DEC_EXPO_STANDARD)) == -1)
		coSo = -coSo;
	
	string realValue;
	switch (coSo)
	{
	case 10:
		realValue = DecToBin(valueOf(soThapPhan,soMu));
	default:
		break;
	}
}


//Truong
//Chi lay 30 bit dau trong 112 bit bieu dien de tinh ra phan thap phan (goi gia tri la v)
//Sau do tinh 2 ^ luyThua => 10 ^ x, x len nen goi v1 = 10 ^ (phan thap phan cua x)
//Nhan phan thap phan sau khi lay log de nhan voi v (y la v = v1 * v) 
//Luu y: 15 bit luu so mu bieu dien o dang so Bias
SoThapPhan QFloat::BinToDec(string bin)
{
	return SoThapPhan();
}


QFloat & QFloat::operator=(const QFloat & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	return *this;
}

QFloat::~QFloat()
{
}

//Tai
//Ham chuyen tu dec sang day bin
//Ham QFloat co goi ham nay thi sau khi chuan hoa, 2 string trong QFloat co the chuyen ve SoThapPhan de luu
//Luu y: 15 bit luu so mu bieu dien o dang so Bias
//Dang chuan
string QFloat::DecToBin(SoThapPhan dec)
{
	char dau = '0';
	if (dec.thapPhan < 0) {
		dau = '1';
		dec.thapPhan = -dec.thapPhan;
	}

	QInt temp;
	string phanThapPhan = temp.DecToBin(toString((int)floor(dec.thapPhan)));
	int dich = phanThapPhan.size()-1;
	double sauDauPhay = dec.thapPhan - floor(dec.thapPhan);
	int i = 0;
	while (i < SIGN && sauDauPhay != 1.0) {
		sauDauPhay = sauDauPhay * 2;
		phanThapPhan.push_back('0' + (int)floor(sauDauPhay));
	}

	int mu = dec.luyThua*log2(10)+dich;
	string phanMu = temp.DecToBin(toString(mu + BIAS));
	double soDu = dec.luyThua*log2(10) - mu;

	string bin;
	bin.push_back(dau);
	bin.append(phanMu); 
	bin.append(phanThapPhan);

	return bin;
}

//Dang khong chuan
string QFloat::DecToBinU(SoThapPhan dec)
{
	char dau = '0';
	if (dec.thapPhan < 0) {
		dau = '1';
		dec.thapPhan = -dec.thapPhan;
	}
	dec.thapPhan /= 10.0;
	dec.luyThua += 1;

	QInt temp;
	double sauDauPhay = dec.thapPhan;
	string phanThapPhan;
	int i = 0;
	while (i < SIGN && sauDauPhay != 1.0) {
		sauDauPhay = sauDauPhay * 2;
		phanThapPhan.push_back('0' + (int)floor(sauDauPhay));
	}

	int mu = dec.luyThua*log2(10);
	string phanMu = temp.DecToBin(toString(2*BIAS+1));
	double soDu = dec.luyThua*log2(10) - mu;

	string bin;
	bin.push_back(dau);
	bin.append(phanMu);
	bin.append(phanThapPhan);

	return bin;
}

//Lay bit tai vi tri pos
char QFloat::getBit(int pos)
{
	int i = pos / 8;
	int j = pos % 8;
	return ((data[i] >> j) & 1);
}

//Truong
//ham lay bieu dien cua QFloat hien tai thanh chuoi nhi phan (2)
//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
//string luu bit cao nhat tai vi tri 0
//Luu y: 15 bit luu so mu bieu dien o dang so Bias
string QFloat::getBin()
{
	return string();
}

//Truong
//ham lay bieu dien cua QFloat hien tai thanh chuoi thap phan (10) 
//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
//Luu y: 15 bit luu so mu bieu dien o dang so Bias

string QFloat::getDec()
{
	return string();
}

QFloat QFloat::operator+(const QFloat & number)
{
	return QFloat();
}

QFloat QFloat::operator-(const QFloat & number)
{
	return QFloat();
}

QFloat QFloat::operator*(const QFloat & number)
{
	return QFloat();
}

QFloat QFloat::operator/(const QFloat & number)
{
	return QFloat();
}
