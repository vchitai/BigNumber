#include "QFloat.h"

QFloat QFloat::BinToQFloat(string b) const
{
	QFloat kq;
	for (int i = 0; i < (int)b.size(); ++i)
		kq.ganBit(0, b[i] - '0');
	return kq;
}

string QFloat::toString(int dec) const {
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
	for (int i = 0; i < (int)soThapPhan.size(); i++)
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
	for (; j < (int)thapPhan.size(); j++) {
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
	for (; i < (int)mu.size(); i++) {
		res.luyThua *= 10;
		res.luyThua += mu[i] - '0';
	}
	if (dau == 1)
		res.luyThua = -res.luyThua;
	return res;
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
		realValue = DecToBin(valueOf(soThapPhan, soMu));
	default:
		break;
	}
}


//Truong
//Chi lay 30 bit dau trong 112 bit bieu dien de tinh ra phan thap phan (goi gia tri la v)
//Sau do tinh 2 ^ luyThua => 10 ^ x, x len nen goi v1 = 10 ^ (phan thap phan cua x)
//Nhan phan thap phan sau khi lay log de nhan voi v (y la v = v1 * v) 
//Luu y: 15 bit luu so mu bieu dien o dang so Bias
SoThapPhan QFloat::BinToDec(string bin) const
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
string QFloat::DecToBin(SoThapPhan dec) const
{
	char dau = '0';
	if (dec.thapPhan < 0) {
		dau = '1';
		dec.thapPhan = -dec.thapPhan;
	}

	//SoThapPhan dec => v * 2 ^ x
	double y = dec.luyThua * log2(10) - (int)(dec.luyThua * log2(10));
	int x = (int)dec.luyThua * log2(10);
	double v = dec.thapPhan * pow(2, y);

	QInt temp;
	string dayBit = temp.DecToBin(toString((int)v));
	while (dayBit[0] == '0') dayBit.erase(0, 1);
	dayBit.erase(0, 1);
	x += size(dayBit);

	if (abs(v) < 1e-10 || x < LIMIT_BIN_EXPO_OVERFLOW - 112) {
		string s = "";
		for (int i = 0; i < 128; ++i)
			s = s + '0';
		return s;
	}

	if (x < LIMIT_BIN_EXPO_OVERFLOW) {
		return DecToBinU(dec);
	}

	if (x > LIMIT_BIN_EXPO_STANDARD) {
		string s = "";
		for (int i = 0; i < 128; ++i)
			s = s + '#';
		return s;
	}

	v = v - (int)v;
	while (dayBit.size() < 112 && abs(v - 1) > 1e-9) {
		v *= 2;
		dayBit += ('0' + (v > 1 - 1e-9));
		v = v - (int)(v + 1e-9);
	}
	chuanHoaThapPhanBin(dayBit);

	string phanMu = temp.DecToBin(toString(x + BIAS));
	while (phanMu.size() > 15) phanMu.erase(0, 1);

	string bin = "";
	bin += dau;
	bin += phanMu;
	bin += dayBit;

	return bin;
}

//Dang khong chuan
string QFloat::DecToBinU(SoThapPhan dec) const
{
	char dau = '0';
	if (dec.thapPhan < 0) {
		dau = '1';
		dec.thapPhan = -dec.thapPhan;
	}

	//SoThapPhan dec => v * 2 ^ x
	double y = dec.luyThua * log2(10) - (int)(dec.luyThua * log2(10));
	int x = (int)dec.luyThua * log2(10);
	double v = dec.thapPhan * pow(2, y);

	QInt temp;
	string dayBit = temp.DecToBin(toString((int)v));
	while (dayBit[0] == '0') dayBit.erase(0, 1);
	x += size(dayBit);

	while (x < LIMIT_BIN_EXPO_OVERFLOW) {
		++x;
		dayBit = '0' + dayBit;
	}

	v = v - (int)v;
	while (dayBit.size() < 112 && abs(v - 1) > 1e-9) {
		v *= 2;
		dayBit += ('0' + (v > 1 - 1e-9));
		v = v - (int)(v + 1e-9);
	}
	chuanHoaThapPhanBin(dayBit);

	string phanMu = temp.DecToBin(toString(x + BIAS));
	while (phanMu.size() > 15) phanMu.erase(0, 1);

	string bin = "";
	bin += dau;
	bin += phanMu;
	bin += dayBit;

	return bin;
}

//Lay bit tai vi tri pos
char QFloat::getBit(int pos) const
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
string QFloat::getBin() const
{
	return string();
}

//Truong
//ham lay bieu dien cua QFloat hien tai thanh chuoi thap phan (10) 
//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
//Luu y: 15 bit luu so mu bieu dien o dang so Bias

string QFloat::getDec() const
{
	return string();
}

QFloat QFloat::operator+(const QFloat & number) const
{
	SoThapPhan a = this->BinToDec(this->getBin());
	SoThapPhan b = number.BinToDec(number.getBin());

	if (a.luyThua > b.luyThua)
		swap(a, b);

	if (a.luyThua + 10 < b.luyThua)
		return BinToQFloat(DecToBin(b));

	b.thapPhan *= pow(10, b.luyThua - a.luyThua);
	b.luyThua = a.luyThua;

	SoThapPhan kq;
	kq.thapPhan = a.thapPhan + b.thapPhan;
	kq.luyThua = a.luyThua;

	int cnt = 0;
	while (cnt++ < 10 && abs(kq.thapPhan) >= 10.0) {
		kq.thapPhan /= 10;
		kq.luyThua += 1;
	}

	cnt = 0;
	while (cnt++ < 10 && abs(kq.thapPhan) < 0) {
		kq.thapPhan *= 10;
		kq.luyThua -= 1;
	}

	if (abs(kq.thapPhan) < 1e-10) {
		kq.thapPhan = 0;
		kq.luyThua = 0;
	}

	QFloat ketQua;
	string temp = DecToBin(kq);
	if (temp[0] == '#')
		ketQua.coSo = -1;
	else
		ketQua = BinToQFloat(temp);

	return ketQua;
}

QFloat QFloat::operator-(const QFloat & number) const
{
	QFloat b = number;
	QFloat a = *this;

	b.ganBit(0, 1 - b.getBit(0));
	return a + b;
}

QFloat QFloat::operator*(const QFloat & number) const
{
	SoThapPhan a = this->BinToDec(this->getBin());
	SoThapPhan b = number.BinToDec(number.getBin());

	SoThapPhan kq;
	kq.thapPhan = a.thapPhan * b.thapPhan;
	kq.luyThua = a.luyThua + b.luyThua;

	int cnt = 0;
	while (cnt++ < 30 && abs(kq.thapPhan) >= 10.0) {
		kq.thapPhan /= 10;
		kq.luyThua += 1;
	}

	cnt = 0;
	while (cnt++ < 30 && abs(kq.thapPhan) < 0) {
		kq.thapPhan *= 10;
		kq.luyThua -= 1;
	}

	if (abs(kq.thapPhan) < 1e-10) {
		kq.thapPhan = 0;
		kq.luyThua = 0;
	}

	QFloat ketQua;
	string temp = DecToBin(kq);
	if (temp[0] == '#')
		ketQua.coSo = -1;
	else
		ketQua = BinToQFloat(temp);

	return ketQua;
}

QFloat QFloat::operator/(const QFloat & number) const
{
	SoThapPhan a = this->BinToDec(this->getBin());
	SoThapPhan b = number.BinToDec(number.getBin());

	if (abs(b.thapPhan) < 1e-10) {
		QFloat ketQua;
		ketQua.coSo = -2;
		return ketQua;
	}

	SoThapPhan kq;
	kq.thapPhan = a.thapPhan / b.thapPhan;
	kq.luyThua = a.luyThua - b.luyThua;

	int cnt = 0;
	while (cnt++ < 30 && abs(kq.thapPhan) >= 10.0) {
		kq.thapPhan /= 10;
		kq.luyThua += 1;
	}

	cnt = 0;
	while (cnt++ < 30 && abs(kq.thapPhan) < 0) {
		kq.thapPhan *= 10;
		kq.luyThua -= 1;
	}

	if (abs(kq.thapPhan) < 1e-10) {
		kq.thapPhan = 0;
		kq.luyThua = 0;
	}

	QFloat ketQua;
	string temp = DecToBin(kq);
	if (temp[0] == '#')
		ketQua.coSo = -1;
	else
		ketQua = BinToQFloat(temp);

	return ketQua;
}

string QFloat::getValue()
{
	switch (coSo)
	{
	case BIN: return getBin(); break;
	case DEC: return getDec(); break;
	default: 
		break;
	}
}