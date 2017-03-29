#include "Calculator.h"

//Khoi tao mac dinh ans = 0
Calculator::Calculator()
{
	ans = new QInt();
	initQIntMenu();
	initQFloatMenu();
	DoiSangHeDec();
}

void Calculator::xuLyFloatInput(string input, string &thapPhan, string &mu)
{
	int i = 0;
	thapPhan.clear();
	mu.clear();
	while (i < input.length() && input[i] != 'E' &&input[i] != 'e') {
		thapPhan.push_back(input[i]);
		i++;
	}
	i++;
	while (i < input.length()) {
		mu.push_back(input[i]);
		i++;
	}
}

//Chuyen che do
void Calculator::changeMode() {
	mode = 1 - mode;
	if (ans != NULL)
		delete ans;
	if (mode)
		ans = new QFloat();
	else
		ans = new QInt();
	DoiSangHeDec();
}

//Khoi tao menu
void Calculator::initQIntMenu() {
	if (QintMenu.size() > 0)
		return;
	QintMenu.push_back(Command('R', "Nhap du lieu tu file"));
	QintMenu.push_back(Command('S', "Chuyen sang QFloat"));
	QintMenu.push_back(Command('N', "Chuyen sang he BIN"));
	QintMenu.push_back(Command('H', "Chuyen sang he HEX"));
	QintMenu.push_back(Command('T', "Chuyen sang he DEC"));
	QintMenu.push_back(Command('+', "Cong"));
	QintMenu.push_back(Command('-', "Tru"));
	QintMenu.push_back(Command('*', "Nhan"));
	QintMenu.push_back(Command('/', "Chia"));
	QintMenu.push_back(Command('Q', "Thoat"));
}

void Calculator::initQFloatMenu() {
	if (QfloatMenu.size() > 0)
		return;
	QfloatMenu.push_back(Command('R', "Nhap du lieu tu file"));
	QfloatMenu.push_back(Command('S', "Chuyen sang QInt"));
	QfloatMenu.push_back(Command('N', "Chuyen sang he BIN"));
	QfloatMenu.push_back(Command('T', "Chuyen sang he DEC"));
	QfloatMenu.push_back(Command('+', "Cong"));
	QfloatMenu.push_back(Command('-', "Tru"));
	QfloatMenu.push_back(Command('*', "Nhan"));
	QfloatMenu.push_back(Command('/', "Chia"));
	QfloatMenu.push_back(Command('Q', "Thoat"));
}

//In Menu
void Calculator::printMenu(vector<Command> cm) {
	for (int i = 0; i < (int)cm.size(); i++)
		cout << "\t" << cm[i].commandId << ". " << cm[i].description << endl;
}

void Calculator::callMenu() {
	cout << "\t" << xuatAns() << endl;
	cout << "Current Using: " << (mode == MODE_QINT ? "QINT" : "QFLOAT") << endl;
	switch (mode)
	{
	case MODE_QINT:
		cout << "Current Numeral System: " << (coSo == BIN ? "BIN" : (coSo == DEC ? "DEC" : "HEX")) << endl;
		printMenu(QintMenu);
		break;
	case MODE_QFLOAT:
		cout << "Current Numeral System: " << (coSo == BIN ? "BIN" : "DEC") << endl;
		printMenu(QfloatMenu);
		break;
	default:
		break;
	}
}

//Xu ly lenh
bool Calculator::handleQIntCommand(string input)
{
	if (input.size() == 1)
	{
		switch (input[0])
		{
		case 'R':
		case 'r':
			handleQIntFile();
			break;
		case 'S':
		case 's':
			changeMode();
			break;
		case 'T':
		case 't':
			DoiSangHeDec();
			break;
		case 'N':
		case 'n':
			DoiSangHeBin();
			break;
		case 'H':
		case 'h':
			DoiSangHeHex();
			break;
		case '+': {
			QInt soHang = nhapSoHangInt();
			CongInt(soHang);
			break;
		}
		case '-': {
			QInt soHang = nhapSoHangInt();
			TruInt(soHang);
			break;
		}
		case '*': {
			QInt soHang = nhapSoHangInt();
			NhanInt(soHang);
			break;
		}
		case '/': {
			QInt soHang = nhapSoHangInt();
			ChiaInt(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return true;
		default:
			if (isQIntConvertValid(input)) {
				delete ans;
				ans = new QInt(nhapInt(input));
			}
			break;
		}
		return false;
	}
	else
	{
		if (isQIntConvertValid(input)) {
			delete ans;
			ans = new QInt(nhapInt(input));
			if (ans->getCoSo() == -1) {
				delete ans;
				Error.push_back(ERROR_BUFFER_OVERFLOW);
				ans = new QInt();
			}
		}
		return false;
	}
}

bool Calculator::handleQFloatCommand(string input)
{
	if (input.size() == 1)
	{
		switch (input[0])
		{
		case 'R':
		case 'r':
			handleQFloatFile();
			break;
		case 'S':
		case 's':
			changeMode();
			break;
		case 'T':
		case 't':
			DoiSangHeDec();
			break;
		case 'N':
		case 'n':
			DoiSangHeBin();
			break;
		case '+': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case '-': {
			QFloat soHang = nhapSoHangFloat();
			TruFloat(soHang);
			break;
		}
		case '*': {
			QFloat soHang = nhapSoHangFloat();
			NhanFloat(soHang);
			break;
		}
		case '/': {
			QFloat soHang = nhapSoHangFloat();
			ChiaFloat(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return true;
		default:
			if (isQFloatConvertValid(input)) {
				delete ans;
				ans = new QFloat(nhapFloat(input));
			}
			break;
		}
		return false;
	}
	else
	{
		if (isQFloatConvertValid(input)) {
			delete ans;
			ans = new QFloat(nhapFloat(input));
			if (ans->getCoSo() == -1) {
				delete ans;
				Error.push_back(ERROR_BUFFER_OVERFLOW);
				ans = new QFloat();
			}
		}
		return false;
	}
}

bool Calculator::isQIntConvertValid(string input) {
	switch (coSo)
	{
	case BIN:
		for (int i = 0; i < (int)input.size(); i++)
			if (input[i] != '0' && input[i] != '1')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	case DEC:
	{
		int i = 0;
		if (input[i] == '-')
			i++;
		for (; i < (int)input.size(); i++)
			if (input[i] < '0' || input[i] > '9')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	}
	case HEX:
		for (int i = 0; i < (int)input.size(); i++)
			if ((input[i] < '0' || input[i] > '9') && (input[i] < 'A' || input[i] > 'F') && (input[i] < 'a' || input[i] > 'f'))
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	default:
		Error.push_back(ERROR_INVALID_INPUT);
		return false;
		break;
	}
	return true;
}

bool Calculator::isQFloatConvertValid(string input) {
	switch (coSo)
	{
	case BIN:
	{
		if (input.length() < MAX_BITS)
		{
			Error.push_back(ERROR_INVALID_INPUT);
			return false;
		}
		for (int i = 0; i < (int)input.size(); i++)
		{
			if (input[i] != '0' && input[i] != '1')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		}
		break;
	}
	case DEC:
	{
		int dot = 0;
		int E = 0;
		int i = 0;
		int size = input.length();
		if (input[i] == '-') i++;
		for (; i < size; i++)
		{
			if (input[i] == '-')
			{
				if (input[i - 1] == 'E' || input[i - 1] == 'e')
				{
					continue;
				}
				else
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
			}
			if (input[i] == '.')
			{
				dot++;
				if (i == 0 || i == size - 1)
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (input[i - 1]<'0' || input[i - 1]>'9' || input[i + 1]<'0' || input[i + 1]>'9')
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (dot > 1)
					break;
				else
					continue;
			}
			if (input[i] == 'E' || input[i] == 'e')
			{
				E++;
				if (i == 0 || i == size - 1)
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if ((input[i - 1]<'0' || input[i - 1]>'9' || input[i + 1]<'0' || input[i + 1]>'9') && input[i + 1] != '-')
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (E > 1)
					break;
				else
					continue;
			}
			if (input[i] < '0' || input[i] > '9')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		}
		if (E > 1 || dot > 1)
		{
			Error.push_back(ERROR_INVALID_INPUT);
			return false;
		}
		break;
	}
	default:
		Error.push_back(ERROR_INVALID_INPUT);
		return false;
		break;
	}
	return true;
}

QInt Calculator::nhapSoHangInt() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isQIntConvertValid(input2)) {
		return QInt(coSo, input2);
	}
	else {
		return QInt();
	}
}

QFloat Calculator::nhapSoHangFloat() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isQFloatConvertValid(input2)) {
		string thapPhan;
		string mu;
		if (coSo == DEC) {
			xuLyFloatInput(input2, thapPhan, mu);
		}
		else if (coSo == BIN) {
			thapPhan = input2;
			mu = "";
		}
		return QFloat(coSo, thapPhan, mu);
	}
	else {
		return QFloat();
	}
}

string Calculator::xuatLoi() {
	string res;
	if (!Error.empty()) {
		switch (Error[Error.size()-1])
		{
		case ERROR_INVALID_INPUT:
			res = string("Invalid Input");
			break;
		case ERROR_DIVIDE_BY_0:
			res = string("Division by 0");
			break;
		case ERROR_BUFFER_OVERFLOW:
			res = string("Buffer Overflow");
			break;
		case ERROR_CANT_OPEN_FILE_INPUT:
			res = string("Can't open file input");
			break;
		case ERROR_CANT_OPEN_FILE_OUTPUT:
			res = string("Can't open file output");
			break;
		case SUCCESSFULLY_WROTE_TO_FILE:
			res = string("Successfully wrote to file");
			break;
		default:
			break;
		}
		Error.pop_back();
	}
	return res;
}

string Calculator::xuatAns() {
	return ans->getValue();
}

//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
QInt Calculator::nhapInt(string input)
{
	return QInt(coSo, input);
}

QFloat Calculator::nhapFloat(string input) {
	string thapPhan;
	string mu;
	if (coSo == DEC) {
		xuLyFloatInput(input, thapPhan, mu);
	}
	else if (coSo == BIN) {
		thapPhan = input;
		mu = "";
	}
	return QFloat(coSo, thapPhan, mu);
}

//Cac Ham DoiSangHeSo() doi coSo trong QInt
void Calculator::DoiSangHeBin()
{
	coSo = BIN;
	ans->setCoSo(coSo);
}

void Calculator::DoiSangHeDec()
{
	coSo = DEC;
	ans->setCoSo(coSo);
}

void Calculator::DoiSangHeHex()
{
	coSo = HEX;
	ans->setCoSo(coSo);
}

//Cac Ham tinh toan yeu cau:
//	nhap vao mot doi so
//	tinh kq
//	ans <- kq
void Calculator::CongInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp + soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::TruInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp - soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::NhanInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp * soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::ChiaInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp / soHang;
	if (tmp.getCoSo() == -2) {
		Error.push_back(ERROR_DIVIDE_BY_0);
		delete ans;
		ans = new QInt();
	}
	else if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::CongFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp + soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::TruFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp - soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::NhanFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp * soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::ChiaFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp / soHang;
	if (tmp.getCoSo() == -2) {
		Error.push_back(ERROR_DIVIDE_BY_0);
		delete ans;
		ans = new QFloat();
	}
	else if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

//Khoi dong may tinh
void Calculator::start()
{
	string command;
	bool exit = false;
	do
	{
		system("cls");
		system("Color FC");
		while (Error.size()>0)
			cout << xuatLoi() << endl;
		callMenu();
		cout << "Input Command: ";
		cin >> command;
		if (mode == MODE_QINT)
			exit = handleQIntCommand(command);
		else
			exit = handleQFloatCommand(command);
	} while (!exit);
}

Calculator::Calculator(const Calculator &calc)
{
	coSo = calc.coSo;
	mode = calc.mode;
	QintMenu = calc.QintMenu;
	QfloatMenu = calc.QfloatMenu;
	Error = calc.Error;
	if (mode == MODE_QINT) {
		if (ans != NULL)
			delete ans;
		ans = new QInt(*((QInt*)(calc.ans)));
	}
	else {
		if (ans != NULL)
			delete ans;
		ans = new QFloat(*((QFloat*)(calc.ans)));
	}
}

Calculator& Calculator::operator = (const Calculator& calc)
{
	coSo = calc.coSo;
	mode = calc.mode;
	QintMenu = calc.QintMenu;
	QfloatMenu = calc.QfloatMenu;
	Error = calc.Error;
	if (mode == MODE_QINT) {
		if (ans != NULL)
			delete ans;
		ans = new QInt(*((QInt*)(calc.ans)));
	}
	else {
		if (ans != NULL)
			delete ans;
		ans = new QFloat(*((QFloat*)(calc.ans)));
	}

	return (*this);
}

Calculator::~Calculator()
{
	if (ans != NULL)
		delete ans;
}

vector<string> Calculator::splitString(string s, string delimiter)
{
	string ss = s;
	vector<string> res;
	int pos = 0;
	string tmp;
	while ((pos = ss.find(delimiter)) != string::npos) {
		tmp = ss.substr(0, pos);
		res.push_back(tmp);
		ss.erase(0, pos + delimiter.length());
	}
	res.push_back(ss);

	return res;
}

void Calculator::handleFile(ifstream& ifile, ofstream& ofile)
{
	ifile.open(FILE_IN);
	if (!ifile.is_open()) {
		string fileName;
		cout << "Input input filename: ";
		cin >> fileName;
		ifile.close();
		ifile.open(fileName);
	}
	if (ifile.is_open()) {
		ifstream checker;
		checker.open(FILE_OUT);
		if (checker.is_open())
		{
			checker.close();
			ofile.open(FILE_OUT);
		}
		else {
			string fileName;
			cout << "Input output filename: ";
			cin >> fileName;
			ofile.close();
			ofile.open(fileName);
			if (!ofile.is_open()) {
				Error.push_back(ERROR_CANT_OPEN_FILE_OUTPUT);
				return;
			}
		}
	}
	else {
		Error.push_back(ERROR_CANT_OPEN_FILE_INPUT);
	}
}

void Calculator::handleQIntFile()
{
	ifstream ifile;
	ofstream ofile;
	handleFile(ifile, ofile);
	if (Error.empty()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			string delim = " ";
			s = normalizeString(s);
			vector<string> token = splitString(s, delim);
			if (token.size() < 3 || token.size() > 4)
				continue;

			if (token[0] == "2")
				DoiSangHeBin();
			else if (token[0] == "10")
				DoiSangHeDec();
			else if (token[0] == "16")
				DoiSangHeHex();
			else
				continue;

			if (token.size() == 3) {
				if (token[1] == "ror") {
					if (isQIntConvertValid(token[2])) {
						QInt term1(coSo, token[2]);
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						// Goi ham ror QInt res = term1.ror;
						//ofile << res.getValue();
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
				else if (token[1] == "~") {
					if (isQIntConvertValid(token[2])) {
						QInt term1(coSo, token[2]);
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						QInt res = ~term1;
						ofile << res.getValue();
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
				else if (token[1] == "10" || token[1] == "16" || token[1] == "2") {
					if (isQIntConvertValid(token[2])) {
						QInt term1(coSo, token[2]);
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						string res;
						if (token[1] == "10")
							res = term1.getDec();
						else if (token[1] == "16")
							res = term1.getOutHex(term1.getHex());
						else if (token[1] == "2")
							res = term1.getOutBin(term1.getBin());
						ofile << res << endl;
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
				else
					break;
			}

			if (token.size() == 4) {
				if (token[2] == "*" || token[2] == "+" || token[2] == "-" || token[2] == "/" || token[2] == ">>" || token[2] == "<<") {
					if (isQIntConvertValid(token[1]) && isQIntConvertValid(token[3])) {
						QInt term1(coSo, token[1]);
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						QInt term2(coSo, token[3]);
						if (term2.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						QInt res;
						if (token[2] == "+") {
							res = term1 + term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "-") {
							res = term1 - term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "*") {
							res = term1 * term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "/") {
							res = term1 / term2;
							if (term1.getCoSo() == -2) {
								Error.push_back(ERROR_DIVIDE_BY_0);
								continue;
							}
						}
						else if (token[2] == ">>") {
							int x = valueOf(token[3]);
							if (x == -1)
								continue;
							else {
								res = term1;
								for (int i = 0; i < x; i++)
									res = res.shiftRight();
							}
						}
						else if (token[2] == "<<") {
							int x = valueOf(token[3]);
							if (x == -1)
								continue;
							else {
								res = term1;
								for (int i = 0; i < x; i++)
									res = res.shiftLeft();
							}
						}
						ofile << res.getValue() << endl;
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
			}
			if (!Error.empty()) {
				ofile << xuatLoi() << endl;
			}
		}
		ifile.close();
		ofile.close();
		DoiSangHeDec();
		Error.push_back(SUCCESSFULLY_WROTE_TO_FILE);
	}
	if (ifile.is_open())
		ifile.close();
}

void Calculator::handleQFloatFile()
{
	ifstream ifile;
	ofstream ofile;
	handleFile(ifile, ofile);
	if (Error.empty()) {
		while (!ifile.eof()) {
			string s;
			getline(ifile, s);
			string delim = " ";
			s = normalizeString(s);
			vector<string> token = splitString(s, delim);
			if (token.size() < 3 || token.size() > 4)
				continue;

			if (token[0] == "2")
				DoiSangHeBin();
			else if (token[0] == "10")
				DoiSangHeDec();
			else
				continue;

			if (token.size() == 3) {
				if (token[1] == "10" || token[1] == "2") {
					if (isQFloatConvertValid(token[2])) {
						QFloat term1(nhapFloat(token[2]));
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						string res;
						if (token[1] == "10")
							res = term1.getDec();
						else if (token[1] == "2")
							res = term1.getOutBin(term1.getBin());
						ofile << res << endl;
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
				else
					break;
			}

			if (token.size() == 4) {
				if (token[2] == "*" || token[2] == "+" || token[2] == "-" || token[2] == "/") {
					if (isQFloatConvertValid(token[1]) && isQFloatConvertValid(token[3])) {
						QFloat term1(nhapFloat(token[2]));
						if (term1.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						QFloat term2(nhapFloat(token[2]));
						if (term2.getCoSo() == -1) {
							Error.push_back(ERROR_BUFFER_OVERFLOW);
							continue;
						}
						QFloat res;
						if (token[2] == "+") {
							res = term1 + term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "-") {
							res = term1 - term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "*") {
							res = term1 * term2;
							if (term1.getCoSo() == -1) {
								Error.push_back(ERROR_BUFFER_OVERFLOW);
								continue;
							}
						}
						else if (token[2] == "/") {
							res = term1 / term2;
							if (term1.getCoSo() == -2) {
								Error.push_back(ERROR_DIVIDE_BY_0);
								continue;
							}
						}
						ofile << res.getValue() << endl;
					}
					else {
						Error.push_back(ERROR_INVALID_INPUT);
						continue;
					}
				}
			}
			if (!Error.empty()) {
				ofile << xuatLoi() << endl;
			}
		}
		ifile.close();
		ofile.close();
		DoiSangHeDec();
		Error.push_back(SUCCESSFULLY_WROTE_TO_FILE);
	}
	if (ifile.is_open())
		ifile.close();
}