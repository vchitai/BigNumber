#include "QFloat.h"

QFloat QFloat::BinToQFloat(string b) const
{
	QFloat kq;
	for (int i = 0; i < (int)b.size(); ++i)
		kq.ganBit(i, b[127 - i] - '0');
	return kq;
}

QFloat QFloat::convertToQFloat(string significand, int expo) const
{
	char dau = '0';
	if (significand[0] == '1') {
		dau = '1';
		QInt temp(2, significand);
		significand = temp.layBu2().getBin();
	}

	QInt number(2, significand);
	for (int i = 127; i >= 113; i--)
		if (number.getBit(i)) {
			number = number.shiftRight();
			expo++;
		}
	int cnt = 0;
	while (cnt < 112 && number.getBit(112) != 1) {
		expo--;
		number = number.shiftLeft();
		++cnt;
	}

	if (expo > LIMIT_BIN_EXPO_STANDARD) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	if (expo < LIMIT_BIN_EXPO_OVERFLOW) {
		QFloat res;
		return res;
	}

	QInt temp;
	string phanMu = temp.DecToBin(toString(expo + BIAS));
	while (phanMu.size() > 15) phanMu.erase(0, 1);

	string bin = "";
	bin += dau;
	bin += phanMu;
	for (int i = 111; i >= 0; --i)
		bin += char(number.getBit(i) + '0');

	return BinToQFloat(bin);
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
	int viTriChamHienTai = -1;
	int viTriChamDich = 1;
	for (int i = 0; i < (int)soThapPhan.size(); i++)
		if (soThapPhan[i] == '.')
			viTriChamHienTai = i;
	if (viTriChamHienTai == -1)
		soThapPhan.append(".0");
	else if (viTriChamHienTai != 1) 
	{
		if (soThapPhan[0] == '-') viTriChamDich++;
		for (int i = viTriChamHienTai; i > viTriChamDich; i--)
			swap(soThapPhan[i], soThapPhan[i - 1]);
		if (viTriChamHienTai > 0)
			soMu = congDec(soMu, toString(viTriChamHienTai - viTriChamDich));
	}

	if (soThapPhan[viTriChamDich - 1] == '0')
	{
		int i = viTriChamDich + 1;
		while (i < soThapPhan.length() && soThapPhan[i] == '0') i++;
		string newThapPhan;
		int luyThua = i-viTriChamDich;
		if (soThapPhan[0] == '-')
			newThapPhan.push_back('-');
		if (i < soThapPhan.length()) {
			newThapPhan.push_back(soThapPhan[i]);
			i++;
			newThapPhan.push_back('.');
			if (i < soThapPhan.length()) {
				while (i < soThapPhan.length()) {
					newThapPhan.push_back(soThapPhan[i]);
					i++;
				}
			}
			else
				newThapPhan.push_back('0');
		}
		else {
			newThapPhan.clear();
			newThapPhan.append("0.0");
		}
		soThapPhan = newThapPhan;
		soMu = truDec(soMu, toString(luyThua));
	}
}

void QFloat::chuanHoaThapPhanBin(string& bin) const {
	while (bin.size() < SIGN) {
		bin.append("0");
	}
}

QFloat::QFloat()
{
	coSo = DEC;
	for (int i = 0; i < 16; ++i)
		data[i] = 0;
}

QFloat::QFloat(const QFloat & number)
{
	coSo = number.coSo;
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
		sauDauPhay += thapPhan[k] - '0';
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
QFloat::QFloat(int so, string soThapPhan, string soMu)
{
	setCoSo(so);
	if (coSo == DEC) {
		chuanHoaDec(soThapPhan, soMu);

		if (cmp(soMu, toString(LIMIT_DEC_EXPO_STANDARD)) == 1) {
			coSo = -1;
			return;
		}

		if (cmp(soMu, toString(LIMIT_DEC_EXPO_OVERFLOW)) == -1) {
			coSo = -1;
			return;
		}

		string realValue;
		SoThapPhan value = valueOf(soThapPhan, soMu);
		if (value.thapPhan == 0)
		{
			for (int i = 0; i < 16; ++i)
				data[i] = 0;
			return;
		}
		realValue = DecToBin(value);
		// Nhi phan
		if (realValue.size() != 0) {
			if (realValue[0] != '#')
			{
				for (int i = 0; i < (int)realValue.size(); i++)
					if (realValue[127 - i] == '1')
						ganBit(i, 1);
					else
						ganBit(i, 0);
			}
			else
			{
				coSo = -1;
			}
		}
	}
	else {
		string realValue = soThapPhan;

		for (int i = 0; i < (int)realValue.size(); i++)
			if (realValue[127 - i] == '1')
				ganBit(i, 1);
			else
				ganBit(i, 0);
	}
}

#define DAU_PHAN_MU 2
#define DAU_PHAN_TRI 17

bool KiemTraToan0(string a, int start, int finish)
{
	for (int i = start - 1; i < finish; ++i)
		if (a[i] == '1')
			return 0;
	return 1;
}

bool KiemTraToan1(string a, int start, int finish)
{
	for (int i = start - 1; i < finish; ++i)
		if (a[i] == '0')
			return 0;
	return 1;
}

double Lay30bitsPhanTriToDec(string bin)
{
	double kq = 0;
	double luyThua2 = 1;
	for (int i = 0; i < 30; ++i)
	{
		luyThua2 /= 2;
		if (bin[i + DAU_PHAN_TRI - 1] == '1')
			kq += luyThua2;
	}
	return kq;
}

//15 bit luu so mu bieu dien o dang so Bias
int PhanMuToDec(string bin128)
{
	int kq = 0;
	int luyThua2 = 1;
	for (int i = DAU_PHAN_TRI - 2; i >= DAU_PHAN_MU - 1; --i)
	{
		if (bin128[i] == '1')
			kq += luyThua2;
		luyThua2 *= 2;
	}
	kq -= (luyThua2 / 2 - 1);
	return kq;
}

//Truong
//Chi lay 30 bit dau trong 112 bit bieu dien de tinh ra phan thap phan (goi gia tri la v)
//Sau do tinh 2 ^ luyThua => 10 ^ x, x len nen goi v1 = 10 ^ (phan thap phan cua x)
//Nhan phan thap phan sau khi lay log de nhan voi v (y la v = v1 * v) 
//Luu y: 15 bit luu so mu bieu dien o dang so Bias
SoThapPhan QFloat::BinToDec(string bin) const
{
	SoThapPhan kq;
	//So dang chuan: Gia tri = (dau)1 + phan tri
	if (bin[0] == '0')
		kq.thapPhan = 1;
	else kq.thapPhan = -1;
	if (KiemTraToan0(bin, DAU_PHAN_MU, DAU_PHAN_TRI - 1))
	{
		if (KiemTraToan0(bin, DAU_PHAN_TRI, MAX_BITS))
			//Phan mu == 0 && Phan tri == 0: So zero
		{
			kq.thapPhan = 0;
			kq.luyThua = 0;
			return kq;
		}
		else kq.thapPhan = 0;	//Phan mu == 0 && Phan tri != 0: So dang khong chuan: Gia tri = 0 + phan tri
	}
	else if (KiemTraToan1(bin, DAU_PHAN_MU, DAU_PHAN_TRI - 1))
	{
		if (KiemTraToan0(bin, DAU_PHAN_TRI, MAX_BITS))
			//Phan mu toan 1 && Phan tri == 0: So vo cung
		{
			return kq;
		}
		else
			//Phan mu toan 1 && Phan tri != 0: So bao loi
		{
			return kq;
		}
	}
	if (kq.thapPhan > 0)
		kq.thapPhan += Lay30bitsPhanTriToDec(bin);
	else kq.thapPhan -= Lay30bitsPhanTriToDec(bin);
	kq.luyThua = PhanMuToDec(bin);	//Tinh ra 2^luyThua
	double temp = kq.luyThua * log10(2);	//Tinh ra 10^luyThua. 2^luyThua = 10^luyThua*log(2)
	kq.luyThua = (int)temp;	//Phan luy thua la so nguyen
	kq.thapPhan *= pow(10, temp - (int)temp);	//Nhan phan le cua luy thua vao phan thap phan phia truoc
	while (abs(kq.thapPhan) < 1)
	{
		kq.thapPhan *= 10;
		kq.luyThua -= 1;
	}
	return kq;
}


QFloat & QFloat::operator=(const QFloat & number)
{
	coSo = number.coSo;
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
	int x = (int)(dec.luyThua * log2(10));
	double v = dec.thapPhan * pow(2, y) + 1e-9;

	QInt temp;
	string dayBit = temp.DecToBin(toString((int)v));
	while (dayBit.size() > 0 && dayBit[0] == '0') dayBit.erase(0, 1);
	bool error = true;
	if (dayBit.size() > 0) {
		dayBit.erase(0, 1);
		error = false;
	}
	x += (int)size(dayBit);

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
	while (dayBit.size() < 112) {
		v *= 2;
		dayBit += ('0' + (v > 1 - 1e-9));
		v = v - (int)(v + 1e-9);
	}

	if (error) {
		while (dayBit.size() > 0 && dayBit[0] == '0') {
			dayBit.erase(0, 1);
			x--;
		}
		dayBit.erase(0, 1);
		x--;
		while (dayBit.size() < 112) {
			v *= 2;
			dayBit += ('0' + (v > 1 - 1e-9));
			v = v - (int)(v + 1e-9);
		}
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
	int x = (int)(dec.luyThua * log2(10));
	double v = dec.thapPhan * pow(2, y);

	QInt temp;
	string dayBit = temp.DecToBin(toString((int)v));
	while (dayBit.size() > 0 && dayBit[0] == '0') dayBit.erase(0, 1);
	bool error = true;
	if (dayBit.size() > 0) {
		dayBit.erase(0, 1);
		error = false;
	}
	x += (int)size(dayBit);

	while (x < LIMIT_BIN_EXPO_OVERFLOW) {
		++x;
		dayBit = '0' + dayBit;
	}

	v = v - (int)v;
	while (dayBit.size() < 112) {
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
	string kq = "";
	for (int i = 0; i < MAX_BITS; i++)
		kq += (getBit(MAX_BITS - 1 - i) + '0');
	return kq;
}

//Truong
//ham lay bieu dien cua QFloat hien tai thanh chuoi thap phan (10) 
//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
//Luu y: 15 bit luu so mu bieu dien o dang so Bias

string QFloat::getDec() const
{
	SoThapPhan dec = BinToDec(getBin());
	string phanTri = to_string(dec.thapPhan);
	while (phanTri[phanTri.size() - 1] == '0')
		phanTri.pop_back();
	if (phanTri[phanTri.size() - 1] == '.')
		phanTri.pop_back();
	string phanMu = to_string(dec.luyThua);
	if (phanMu == "0")
		return phanTri;
	return (phanTri+ "e" + phanMu);
}

QFloat QFloat::operator+(const QFloat & number) const
{
	if (this->coSo == -1 || number.coSo == -1) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	QFloat a = *this;
	QFloat b = number;

	if (a.equalTo0())
		return b;
	if (b.equalTo0())
		return a;

	int expo_a = a.getExpo();
	int expo_b = b.getExpo();

	string signi_a = a.getSignificand();
	string signi_b = b.getSignificand();

	if (expo_a > expo_b) {
		swap(expo_a, expo_b);
		swap(signi_a, signi_b);
	}

	if (expo_b - expo_a > 112)
		return b;

	QInt temp_a(2, signi_a);
	QInt temp_b(2, signi_b);
	while (expo_a != expo_b) {
		temp_a = temp_a.shiftRight();
		expo_a++;
	}

	return convertToQFloat((temp_a + temp_b).getBin(), expo_a);
}

QFloat QFloat::operator-(const QFloat & number) const
{
	if (this->coSo == -1 || number.coSo == -1) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	QFloat b = number;
	QFloat a = *this;

	b.ganBit(127, 1 - b.getBit(0));
	return a + b;
}

QFloat QFloat::operator*(const QFloat & number) const
{
	if (this->coSo == -1 || number.coSo == -1) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	if (this->equalTo0() || number.equalTo0()) {
		return QFloat();
	}

	QFloat number1 = *this;
	QFloat number2 = number;

	int expo_a = number1.getExpo();
	int expo_b = number2.getExpo();
	int expo_res = expo_a + expo_b;

	string signi_a = number1.getSignificand();
	string signi_b = number2.getSignificand();

	QInt temp_a(2, signi_a);
	QInt temp_b(2, signi_b);

	int sign_a = number1.getBit(127);
	int sign_b = number2.getBit(127);

	if (sign_a)
		temp_a = temp_a.layBu2();
	if (sign_b)
		temp_b = temp_b.layBu2();

	QInt a;
	int pre_q = 0;
	QInt m = temp_a;
	QInt q = temp_b;

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
	
	string thapPhan = "";

	int i = 127, sl = 31;
	for (; i >= 0 && a.getBit(i) == 0; --i, --sl);
	--i;
	expo_res += sl;

	int cnt = 0;
	for (; cnt < 112 && i >= 0; --i, ++cnt)
		thapPhan += char(a.getBit(i) + '0');

	for (i = 127; cnt < 112 && i >= 0; --i, ++cnt)
		thapPhan += char(a.getBit(i) + '0');
	
	while (thapPhan.size() < 112) {
		thapPhan = thapPhan + '0';		
	}

	if (expo_res > LIMIT_BIN_EXPO_STANDARD) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	if (expo_res < LIMIT_BIN_EXPO_OVERFLOW) {
		return QFloat();
	}

	QInt temp;
	string phanMu = temp.DecToBin(toString(expo_res + BIAS));
	while (phanMu.size() > 15) phanMu.erase(0, 1);

	string bin = "";
	bin += (sign_a != sign_b ? '1' : '0');
	bin += phanMu;
	bin += thapPhan;

	return BinToQFloat(bin);
}

QFloat QFloat::operator/(const QFloat & number) const
{
	if (this->coSo == -1 || number.coSo == -1) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	if (number.equalTo0()) {
		QFloat res;
		res.coSo = -2;
		return res;
	}

	if (this->equalTo0()) {
		return QFloat();
	}

	QFloat number1 = *this;
	QFloat number2 = number;

	int expo_a = number1.getExpo();
	int expo_b = number2.getExpo();
	int expo_res = expo_a - expo_b;

	string signi_a = number1.getSignificand();
	string signi_b = number2.getSignificand();

	QInt temp_a(2, signi_a);
	QInt temp_b(2, signi_b);

	int sign_a = number1.getBit(127);
	int sign_b = number2.getBit(127);

	if (sign_a)
		temp_a = temp_a.layBu2();
	if (sign_b)
		temp_b = temp_b.layBu2();

	while (cmp(temp_a.getBin(), temp_b.getBin()) == -1) {
		temp_a = temp_a.shiftLeft();
		expo_res--;
	}

	QInt q = temp_a;
	QInt m = temp_b;
	QInt a;
	
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

	string thapPhan = q.getBin();	
	while (thapPhan.size() > 0 && thapPhan[0] == '0') thapPhan.erase(0, 1);
	if (thapPhan.size() > 0)
		thapPhan.erase(0, 1);
	expo_res += (int)thapPhan.size();
	
	while (thapPhan.size() < 112) {
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
			thapPhan += '0';
		}
		else {
			q.ganBit(0, 1);
			thapPhan += '1';
		}
	}
	
	if (expo_res > LIMIT_BIN_EXPO_STANDARD) {
		QFloat res;
		res.coSo = -1;
		return res;
	}

	if (expo_res < LIMIT_BIN_EXPO_OVERFLOW) {
		return QFloat();
	}

	QInt temp;
	string phanMu = temp.DecToBin(toString(expo_res + BIAS));
	while (phanMu.size() > 15) phanMu.erase(0, 1);

	string bin = "";
	bin += (sign_a != sign_b ? '1' : '0');
	bin += phanMu;
	bin += thapPhan;

	return BinToQFloat(bin);
}

string QFloat::getValue()
{
	switch (coSo)
	{
	case BIN: return getBin(); break;
	case DEC: return getDec(); break;
	default: return string(); break;
	}
}

bool QFloat::equalTo0() const
{
	int number_0 = 0;
	for (int i = 126; i >= 0; --i)
		number_0 += 1 - this->getBit(i);
	return (number_0 == 127);
}

int QFloat::getExpo() const
{
	int res = 0;
	for (int i = 126; i >= 112; --i) {
		res = (res << 1) + this->getBit(i);
	}
	return res - BIAS;
}

string QFloat::getSignificand() const
{
	string res = "";
	for (int i = 127; i >= 113; --i)
		res = res + '0';
	res = res + '1';

	for (int i = 111; i >= 0; --i)
		res = res + char(this->getBit(i) + '0');

	if (this->getBit(127)) {
		QInt temp(2, res);
		res = temp.layBu2().getBin();
	}

	return res;
}

string QFloat::getOutBin(string bin)
{
	while (bin.size() > 0 && bin[0] == '0') bin.erase(0, 1);
	if (bin.size() == 0) bin = "0";
	return bin;
}

string QFloat::getOutHex(string bin)
{
	while (bin.size() > 0 && bin[0] == '0') bin.erase(0, 1);
	if (bin.size() == 0) bin = "0";
	return bin;
}