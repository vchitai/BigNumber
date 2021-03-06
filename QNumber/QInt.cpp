#include "QInt.h"

const vector <string> QInt::khoiTaoLuyThua2() {
	vector <string> res;
	res.clear();

	res.push_back("1");
	for (int i = 1; i < MAX_BITS; ++i) {
		res.push_back(congDec(res[i - 1], res[i - 1]));
	}

	return res;
}

const vector <string> QInt::luyThua2 = QInt::khoiTaoLuyThua2();

QInt::QInt()
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0;
	coSo = DEC;
}

QInt::QInt(int so, string input) {
	setCoSo(so);
	// Kiem tra tran so
	string realValue;

	switch (coSo)
	{
	case BIN: realValue = chuanHoaBin(input); break;
	case DEC: realValue = DecToBin(input); break;
	case HEX: realValue = chuanHoaBin(HexToBin(input)); break;
	default: break;
	}

	if (realValue == "#") {
		setCoSo(-1);
		return;
	}

	if (realValue.size() != 0) {
		for (int i = 0; i < (int)realValue.size(); i++)
			if (realValue[127 - i] == '1')
				ganBit(i, 1);
			else
				ganBit(i, 0);
	}

}

QInt::QInt(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap phan (10)
string QInt::BinToDec(string bin)
{
	string kq = "0";
	for (int i = 127; i > 0; i--)
		if (bin[i] == '1')
			kq = congDec(kq, luyThua2[127 - i]);
	if (bin[0] == '1')
		kq = truDec(kq, luyThua2[127]);
	return kq;
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap luc phan (16)
string QInt::BinToHex(string bin)
{
	string binary[16] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };
	string kq = "";
	string t = "";

	for (int i = 0; i < 32; i++)
	{
		t = "";
		for (int k = 0; k < 4; k++)
			t += bin[i * 4 + k];
		int j = 0;
		for (j = 0; j < 16; j++)
			if (t == binary[j])
				break;
		if (j < 10)
			kq += j + '0';
		else kq += j % 10 + 'A';
	}

	return kq;
}

//chuyen tu chuoi thap phan (10) <dec> sang nhi phan (2)
string QInt::DecToBin(string dec)
{
	string bin = "";
	int i = (int)luyThua2.size() - 1;
	int dau = 0;
	if (dec[0] == '-') {
		i--;
		dau = 1;
		for (int i = 0; i < (int)dec.size() - 1; i++)
			dec[i] = dec[i + 1];
		dec.pop_back();
	}
	for (; i >= 0; i--) {
		if (cmp(dec, luyThua2[i]) != -1) {
			dec = truDec(dec, luyThua2[i]);
			bin.append("1");
		}
		else {
			bin.append("0");
		}
	}
	if (cmp(dec, "0") != 0)
		return "#";
	if (dau == 1) {
		QInt res(2, bin);
		bin = res.layBu2().getBin();
	}
	return bin;
}

//chuyen tu chuoi thap luc phan (16) <hex> sang nhi phan (2)
string QInt::HexToBin(string hex)
{
	string bin = "";
	for (int i = 0; i < (int)hex.length(); ++i) {
		switch (hex[i]) {
		case '0': bin.append("0000"); break;
		case '1': bin.append("0001"); break;
		case '2': bin.append("0010"); break;
		case '3': bin.append("0011"); break;
		case '4': bin.append("0100"); break;
		case '5': bin.append("0101"); break;
		case '6': bin.append("0110"); break;
		case '7': bin.append("0111"); break;
		case '8': bin.append("1000"); break;
		case '9': bin.append("1001"); break;
		case 'a':
		case 'A': bin.append("1010"); break;
		case 'b':
		case 'B': bin.append("1011"); break;
		case 'c':
		case 'C': bin.append("1100"); break;
		case 'd':
		case 'D': bin.append("1101"); break;
		case 'e':
		case 'E': bin.append("1110"); break;
		case 'f':
		case 'F': bin.append("1111"); break;
		}
	}
	return bin;
}

//chuan hoa BIN
string QInt::chuanHoaBin(string bin) {
	string res = "";
	for (int i = 0; i < MAX_BITS; i++)
		res.append("0");
	int resSize = (int)res.size();
	int binSize = (int)bin.size();
	for (int i = 0; i < binSize; i++)
		res[resSize - binSize + i] = bin[i];

	return res;
}

//Lay bit tai vi tri pos
char QInt::getBit(int pos) const
{
	int i = pos / 8;
	int j = pos % 8;
	return ((data[i] >> j) & 1);
}

//ham lay bieu dien cua QInt hien tai thanh chuoi nhi phan (2)
//string luu bit cao nhat tai vi tri 0
string QInt::getBin()
{
	string kq = "";
	for (int i = 0; i < 128; i++)
		kq += (getBit(127 - i) + '0');
	return kq;
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap phan (10) 
string QInt::getDec()
{
	return BinToDec(getBin());
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap luc phan (16)
string QInt::getHex()
{
	return BinToHex(getBin());
}

//lay so bu 2
QInt QInt::layBu2() const
{
	QInt res;
	res.coSo = this->coSo;

	for (int i = 0; i < 16; ++i)
		res.data[i] = ~data[i];

	int p = 0;
	while (p < 16 && res.data[p] == -1) {
		res.data[p] = 0;
		p = p + 1;
	}

	if (p < 16) res.data[p] = res.data[p] + 1;

	return res;
}

//thuc hien phep dich bit qua trai
QInt QInt::shiftLeft() const
{
	QInt res = *this;

	int preBit = 0;
	for (int i = 0; i < 16; ++i) {
		int current_bit = ((res.data[i] >> 7) & 1);
		res.data[i] <<= 1;
		res.data[i] |= preBit;
		preBit = current_bit;
	}
	res.ganBit(127, preBit);

	return res;
}

//thuc hien phep dich bit qua phai
QInt QInt::shiftRight() const
{
	QInt res = *this;

	int preBit = res.getBit(127);
	for (int i = 15; i >= 0; --i) {
		int current_bit = (res.data[i] & 1);
		res.data[i] >>= 1;
		res.data[i] &= ~(1 << 7);
		res.data[i] |= (preBit << 7);
		preBit = current_bit;
	}

	return res;
}

QInt QInt::shiftLeft(int d) const
{
	QInt res = *this;
	for (int i = 1; i <= d; ++i)
		res = res.shiftLeft();
	return res;
}

QInt QInt::shiftRight(int d) const
{
	QInt res = *this;
	for (int i = 1; i <= d; ++i)
		res = res.shiftRight();
	return res;
}

QInt QInt::ror() const
{
	QInt res = *this;
	int temp = res.getBit(0);
	res = res.shiftRight();
	res.ganBit(127, temp);
	return res;
}

QInt QInt::rol() const
{
	QInt res = *this;
	int temp = res.getBit(127);
	int temp2 = res.getBit(126);
	res = res.shiftLeft();
	res.ganBit(0, temp);
	res.ganBit(127, temp2);
	return res;
}

bool * QInt::DecToBin(QInt x)
{
	string s = x.getBin();
	bool * res = new bool[128];
	
	for (int i = 0; i < 128; ++i)
		res[i] = (s[i] == '0' ? false : true);
	return res;
}

QInt QInt::BinToDec(bool * bit)
{
	string temp = "";
	for (int i = 0; i < 128; ++i)
		temp = temp + (bit[i] ? '1' : '0');
	return QInt(2, temp);
}

char * QInt::BinToHex(bool * bit)
{
	string temp = "";
	for (int i = 0; i < 128; ++i)
		temp = temp + (bit[i] ? '1' : '0');
	return DecToHex(QInt(2, temp));
}

char * QInt::DecToHex(QInt x)
{
	string temp = x.getHex();
	char* res = new char[temp.size()];
	for (int i = 0; i < (int)temp.size(); ++i)
		res[i] = temp[i];
	return res;
}

QInt QInt::operator+(const QInt & number) const
{
	QInt ketQua;
	ketQua.coSo = number.coSo;

	int carry = 0, pre_carry = 0;
	for (int i = 0; i < 128; ++i) {
		int sum = this->getBit(i) + number.getBit(i) + carry;
		pre_carry = carry;
		carry = (sum / 2);
		ketQua.ganBit(i, sum % 2);
	}

	if (carry != pre_carry)
		ketQua.coSo = -1;

	return ketQua;
}

QInt QInt::operator-(const QInt & number) const
{
	return (*this + number.layBu2());
}

QInt QInt::operator*(const QInt & number) const
{
	if (this->coSo == -1 || number.coSo == -1) {
		QInt res;
		res.setCoSo(-1);
		return res;
	}

	QInt a;
	int pre_q = 0;
	QInt m = number;
	QInt q = *this;

	for (int i = 128; i > 0; --i) {
		int q0 = q.getBit(0);
		if (pre_q != q0)
			a = (pre_q == 0 ? a - m : a + m);

		int last_bit = a.getBit(0);
		a = a.shiftRight();
		q = q.shiftRight();
		q.ganBit(127, last_bit);
		pre_q = q0;
	}

	int number_bit_0 = 0;
	for (int i = 0; i < 128; ++i)
		number_bit_0 += (1 - a.getBit(i));

	if (number_bit_0 != 0 && number_bit_0 != 128) {
		q.coSo = -1;
		return q;
	}

	if (number_bit_0 == 0) {
		q = q.layBu2();
		if (q.getBit(127) == 1) {
			q.coSo = -1;
			return q;
		}
		else
			return q.layBu2();
	}

	if (number_bit_0 == 128) {
		if (q.getBit(127) == 0)
			return q;
		else {
			q.coSo = -1;
			return q;
		}
	}

	return q;
}

QInt QInt::operator/(const QInt & number) const
{
	int sign_a = this->getBit(127);
	int sign_b = number.getBit(127);

	QInt q = *this;
	QInt m = number;
	QInt a;

	int number_bit_0 = 0;
	for (int i = 0; i < 128; ++i)
		number_bit_0 += (1 - number.getBit(i));
	if (number_bit_0 == 128) {
		q.coSo = -2;
		return q;
	}

	if (sign_a)
		q = q.layBu2();
	if (sign_b)
		m = m.layBu2();

	for (int i = 128; i > 0; --i) {
		int mb = q.getBit(127);
		int temp = q.getBit(126);
		a = a.shiftLeft();
		q = q.shiftLeft();
		q.ganBit(127, temp);
		a.ganBit(0, mb);

		a = a - m;
		if (a.getBit(127) == 1) {
			a = a + m;
			q.ganBit(0, 0);
		}
		else {
			q.ganBit(0, 1);
		}
	}

	if (sign_a != sign_b)
		q = q.layBu2();

	return q;
}

QInt QInt::operator~() const
{
	QInt kq;
	for (int i = 0; i < 128; ++i)
		kq.ganBit(i, 1 - this->getBit(i));
	return kq;
}

QInt & QInt::operator=(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
	return *this;
}

string QInt::getOutBin(string bin)
{
	while (bin.size() > 0 && bin[0] == '0') bin.erase(0, 1);
	if (bin.size() == 0) bin = "0";
	return bin;
}

string QInt::getOutHex(string bin)
{
	while (bin.size() > 0 && bin[0] == '0') bin.erase(0, 1);
	if (bin.size() == 0) bin = "0";
	return bin;
}

string QInt::getValue() {
	switch (coSo)
	{
	case BIN: return getOutBin(getBin()); break;
	case DEC: return getDec(); break;
	case HEX: return getOutHex(getHex()); break;
	default: return string();
		break;
	}
}

QInt::~QInt()
{
}