#include "User.h"
string path_user = "user.txt";
string User::login_user;
string User::password_user;
list<string> login;
list<string> password;
vector<string> listfile;
int pu = 3;

void User::Load_User()
{
	ifstream file(path_user);

	if (!file.is_open())
	{
		cout << "Не удалось открыть файл " << path_user << endl;

	}
	else
	{
		string lgn, psswrd, s;
		int col;
		file >> col;
		int i = 0;
		while (i < col)
		{
			file >> lgn;
			file >> psswrd;
			login.push_back(DeShifr(lgn));
			password.push_back(DeShifr(psswrd));
			i++;
		}
		file.close();
	}
}

int User::Check(string lgn, string psswrd)
{

	while (pu > 0)
	{
		for (auto i = login.cbegin(), j = password.cbegin(); i != login.cend(); ++i, j++)
		{
			if (*i == lgn && *j == psswrd) { User::login_user = lgn; User::password_user = psswrd; return 1; }
		}
		system("cls"); pu--;
		cout << "Неправильынй логин или пароль. Осталось попыток: " << pu << endl; return 2;
	}
}

void User::Register()
{
	list<string> tmplogin;
	list<string> tmppass;
	
	string lgn, psswrd, fio, adress, phone;
	cout << "\t\t Регистраци:" << endl;
	cout << "Введите логин:" << endl;
	cin >> lgn;
	cout << "Введите пароль:" << endl;
	cin >> psswrd;
	cout << "Введите ФИО:" << endl;
	cin.ignore(); getline(cin, fio);
	cout << "Введите домашний адрес:" << endl;
	getline(cin, adress);
	cout << "Введите телефон:" << endl;
	getline(cin, phone);
	
	ifstream file;
	file.open(path_user);
	if (!file.is_open())
	{
		cout << "Не удалось открыть файл " << path_user << endl;
	}
	else
	{
		string lgn2, psswrd2;
		int col;
		file >> Count_User;
		int i = 0;
		
		if (Count_User == 0)
		{
		}
		else
		{
			while (i < Count_User)
			{
				file >> lgn2;
				file >> psswrd2;
				tmplogin.push_back(lgn2);
				tmppass.push_back(psswrd2);
				i++;
			}
		}
		tmplogin.push_back(Shifr(lgn));
		tmppass.push_back(Shifr(psswrd));
		
		file.close();

	}
	ofstream fout(path_user);

	if (Count_User == 0)
	{
		Count_User++;
		fout << Count_User << endl;
		fout << Shifr(lgn) << endl;
		fout << Shifr(psswrd) << endl;
		fout.close();
	}
	else
	{
		Count_User++;
		fout << Count_User << endl;
		for (auto i = tmplogin.cbegin(), j = tmppass.cbegin(); i != tmplogin.cend(); ++i, ++j)
		{
			fout << *i << endl;
			fout << *j << endl;
		}
		fout.close();
	}
	ofstream ffout;
	string path2 = lgn + ".txt";
	ffout.open(path2);
	if (!ffout.is_open())
	{
		cout << "Не удалось открыть файл " << path2 << endl;
	}
	else
	{
		ffout << fio << endl;
		ffout << adress << endl;
		ffout << phone << endl;
	}
	ffout.close();
	system("cls");
	cout << "Вы успешно зарегистрировались в системе!" << endl;
}

string User::GetLogin()
{
	return login_user;
}

void User::LoadDataUser()
{
	string path = login_user + ".txt";
	ifstream file(path);

	if (!file.is_open())
	{
		cout << "Не удалось открыть файл " << path << endl;

	}
	else
	{
		string s;
		while (getline(file, s))
		{
			FIO = s;
			getline(file,HomeAdress);
			getline(file,Phone);
		}
		file.close();
	}
}

//************************************************************************************************************************************

void Answer::Save()
{
	string path = login_user + "-passed.txt";
	
	
	ifstream fin(path);
	//fout.open(path, fstream::app);
	if (!fin.is_open())
	{
		fin.open(path);
		ofstream fout(path);
		fout << category << endl;
		fout << NameTest << endl;
		fout << ball << endl;
		fout << correct << endl;
		fout << incorrect << endl;
		fout.close();
	}
	else
	{
		ofstream fout(path, fstream::app);
		fout << category << endl;
		fout << NameTest << endl;
		fout << ball << endl;
		fout << correct << endl;
		fout << incorrect << endl;
		fout.close();
	}
	//listfile.push_back(path);
	fin.close();
}

void Answer::LoadPassedTest()
{
	string path = login_user + "-passed.txt";
	vector<string> category, nametest, ball, correct, incorrect;

	ifstream file(path);
	//fout.open(path, fstream::app);
	if (!file.is_open())
	{
		cout << "error" << endl;
	}
	else
	{
		
		string cat, name, b, cor, incor;

		while (getline(file, cat))
		{
			getline(file, name);
			getline(file, b);
			getline(file, cor);
			getline(file, incor);
			category.push_back(cat);
			nametest.push_back(name);
			ball.push_back(b);
			correct.push_back(cor);
			incorrect.push_back(incor);
		}
	}
	file.close();

	
	for (int i = 0; i < category.size(); i++)
	{
		float a1 = stof(correct[i]);
		float b1 = stof(incorrect[i]);
		float ab = a1 + b1;
		float c1 = (a1 / ab) * 100;

		cout << "Категория: " << category[i] << endl;
		cout << "Тест: " << nametest[i] << endl;
		cout << "Оценка: " << ball[i] << endl;
		cout << "Правильных ответов: " << correct[i] << endl;
		cout << "Неправильных ответов: " << incorrect[i] << endl;
		cout << "Процент ответов: " << c1 << "%" << endl << endl;

	}

}


