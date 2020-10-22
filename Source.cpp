#include <iostream>
#include <string>
#include<list>
#include <math.h>
#include "Admin.h"
#include "User.h"
#include <stdio.h>
#include <cstdio>
Admin a; User u;

using namespace std;
int main_choose, main_user;
void UserTest();
void UserMainMenu(string login, string fio, string adress, string phone);
void ShowWelcome(int iItem);
int Welcome();
void WelcomeNext(int k = Welcome());
string Pass();
void ShowAdminMainMenu(int iItem);
int AdminMainMenu();
void AdminTestMenu(int kk);
void AdminAddTestMenu(int c);





int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	
	WelcomeNext(Welcome());

	
		return 0;

}

void UserTest()
{
	switch (main_user)
	{
	case 1:
	{
		system("cls");
		Category* cat = new Category;
		TestList* t = new TestList;
		Test* tt = new Test;
		
		cat->Load();
		t->Load();

		UserTestList uu;
		uu.LoadUserTestList();
		uu.PrintUserTestList();

	    Pass:
		cout << endl << endl << "0 - назад" << endl;
		cout << "Сдать тест номер: ";
		
		int cc;
		cin >> cc;
		
		if(cc == 0) { UserMainMenu(u.GetLogin(), u.GetFio(), u.GetHomeAdress(), u.GetPhone()); }
		if (uu.GetStatus(cc) == "Сдан") { cout << "Тест уже сдан. Для пересдачи обратитесь к администратору!" << endl; goto Pass; }

		tt->Load(cc);
		system("cls");
		int i = 0;
		Answer* answw = new Answer;
		answw->Set(tt->Category(), tt->NameTest());
		cout << "Категория: " << tt->Category() << endl;
		cout << "Тест: " << tt->NameTest() << endl << endl;
		while (i < tt->Size())
		{
			system("cls");
			tt->Print_Test(i);
			char answ;
			answ:
			cout << "Введите правильный ответ: "; cin >> answ;
			if (answ > 68 || answ < 65)
			{
				cout << "Неверно. Правильный ответ должен быть A, B, C иди D" << endl; goto answ;
			}
			answw->AddAnswer(answ);
			if (answw->Check(answ, i, cc)) { cout << "Правильный ответ!" << endl; answw->Ball(tt->GetGetBall(i)); }
			else cout << "Неправильный ответ!" << endl;
			i++;
			Sleep(1000);

		}
		//answw->Show();
		system("cls");
		cout << "Оценка: " << answw->ball << endl;
		cout << "Правильных ответов: " << answw->correct << "\t Неправильных ответов: " << answw->incorrect << endl;
		float a1 = answw->correct;
		float b1 = answw->answer.size();
		float c1 = (a1 / b1)*100;
		cout << "Процент правильных: " << c1 << "%" << endl;
		answw->Save();
		uu.SetPassed(cc);
		uu.SaveUserTestList();
		system("pause");
		UserMainMenu(u.GetLogin(), u.GetFio(), u.GetHomeAdress(), u.GetPhone());
		break;

	}
	case 2: 
	{
		system("cls");
		Answer* answw = new Answer;
		answw->LoadPassedTest();

		system("pause");
		UserMainMenu(u.GetLogin(), u.GetFio(), u.GetHomeAdress(), u.GetPhone());
		break;

	}
	case 0: 
	{
		WelcomeNext(Welcome());
	}
	default:
		break;
	}
}
void UserMainMenu(string login, string fio, string adress, string phone)
{
	system("cls");
	cout << "Логин: " << login << "\t Статус: Пользователь" << endl << endl;
	cout << "Ф.И.О: " << fio << endl;
	cout << "Домашний адрес: " << adress << endl;
	cout << "Телефон: " << phone << endl << endl << endl;

	cout << "1 - Сдать тест" << endl;
	cout << "2 - Посмотреть предыдущие результаты тестирования " << endl;

	cout << endl << endl << "0 - Выйти из аккаунта" << endl;
	cin >> main_user;
	UserTest();
}
void ShowWelcome(int iItem)
{
	system("cls");
	iItem == 1 ? cout << ">" : cout << " "; cout << "1 - Войти" << endl;
	iItem == 2 ? cout << ">" : cout << " "; cout << "2 - Зарегестрироваться" << endl;
}
int Welcome()
{
	int iItem = 1;//Отвечает какой пункт меню активен в данный момент
	int nLast = 2;//Отвечает какой индекс у последнего пункта меню
	ShowWelcome(iItem);

	while (TRUE)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			if (0 < iItem - 1)
				iItem = iItem - 1;
			else
				iItem = nLast;
			ShowWelcome(iItem);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			if (iItem < nLast)
				iItem = iItem + 1;
			else
				iItem = 1;
			ShowWelcome(iItem);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			ShowWelcome(iItem);
			switch (iItem)
			{
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			}
		}
	}
	

}
void WelcomeNext(int k)
{
	system("cls");
	switch (k)
	{
	case 1:
	{
		a.Load_Admin();
		u.Load_User();
		string lgn, psswrd;
		do
		{
			cout << "Введите логин:" << endl;
			cin >> lgn;
			cout << "Введите пароль:" << endl;
			psswrd = Pass();
		} while (a.Check(lgn, psswrd) == 2 && u.Check(lgn, psswrd) == 2);
		if (a.Check(lgn, psswrd) == 1)
		{
			AdminTestMenu(AdminMainMenu());
		}
		else if (u.Check(lgn, psswrd) == 1)
		{
			u.LoadDataUser();
			UserMainMenu(u.GetLogin(), u.GetFio(), u.GetHomeAdress(), u.GetPhone());
		}
		break;
	}
	case 2:
	{
		u.Register();
		system("pause");
		system("cls");
		WelcomeNext();
		break;
	}

	default:
		break;
	}
}
string Pass()
{
	char c;
	const int pas_len = 10;
	char password[pas_len];
	int len = 0;

	for (int i = 0; i < pas_len - 1; ++i)
	{
		c = _getch();
		password[i] = c;
		if (c == 13)
		{
			len = pas_len - i;
			password[pas_len - len] = '\0'; break;
		}
		if (c == '\b')
		{
			i--; continue;
		}
		_putch('*');
	}

	password[pas_len - 1] = '\0';
	string a = password;
	return a;

}

void ShowAdminMainMenu(int iItem)
{
	system("cls");
	cout << "Логин: " << a.GetLogin() << "\t Статус: Админ" << endl << endl << endl;

	iItem == 1 ? cout << ">" : cout << " "; cout << "Управление тестированием" << endl;
	iItem == 2 ? cout << ">" : cout << " "; cout << "Просмотр статистики" << endl;
	iItem == 3 ? cout << ">" : cout << " "; cout << "Управление пользователями" << endl;
	iItem == 4 ? cout << ">" : cout << " "; cout << "Выйти из аккаунта" << endl;
}
int AdminMainMenu()
{
	int iItem = 1;//Отвечает какой пункт меню активен в данный момент
	int nLast = 4;//Отвечает какой индекс у последнего пункта меню
	ShowAdminMainMenu(iItem);
	while (TRUE)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			if (0 < iItem - 1)
				iItem = iItem - 1;
			else
				iItem = nLast;
			ShowAdminMainMenu(iItem);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			if (iItem < nLast)
				iItem = iItem + 1;
			else
				iItem = 1;
			ShowAdminMainMenu(iItem);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);//Отжимаем кнопку
			ShowAdminMainMenu(iItem);
			switch (iItem)
			{
			case 1: 
				return  1;
				break; 
			case 2: 
				return  2;
				break; 
			case 3:
				return  3;
				break;
			
			case 4:
				return  0;
				break;
			
			}
		}
	}
	
}
void AdminTestMenu(int kk)
{
	system("cls");
	switch (kk)
	{
	case 0:
	{
		system("cls");

		WelcomeNext(Welcome());
		break;
	}
	case 1:
	{
		system("cls");
		cout << "1 - Добавить тест" << endl;
		cout << "2 - Показать все тесты" << endl;
		cout << "3 - Добавить категорию" << endl;
		cout << "4 - Показать все категории" << endl << endl;
		cout << "0 - Назад" << endl;
		int testmenu_choose;
		cin >> testmenu_choose;
		AdminAddTestMenu(testmenu_choose);
		break;
	}
	case 2:
	{
		system("cls");
		vector<string> login_users, password_users;
		int col = 0;
		ifstream file("user.txt");

		if (!file.is_open())
		{
			cout << "Не удалось открыть файл " << "user.txt" << endl;

		}
		else
		{
			string lgn, psswrd;
			file >> col;
			int i = 0;
			while (i < col)
			{
				file >> lgn;
				file >> psswrd;
				login_users.push_back(a.DeShifr(lgn));
				password_users.push_back(a.DeShifr(psswrd));
				i++;
			}
			file.close();
		}

		int x = 0;
		
		for (int i = 0; i < login_users.size(); i++)
		{
			cout << i + 1 << ") " << login_users[i] << endl;
		}
	AAA:
		cout << "0 - назад" << endl;
		cout << "Посмотреть статистику тестов пользователя под номером: "; int p0; cin >> p0;
		if (p0 == 0) { AdminMainMenu(); }
		if (p0 > login_users.size() || p0 < 0) { cout << "Неправильный ввод. Введи правильно!" << endl; goto AAA; }

		system("cls");
			
		User* uu = new User;
		uu->SetLgnPsw(login_users[p0 - 1], password_users[p0 - 1]);
		cout << "Пользователь: " << login_users[p0 - 1] << endl << endl;
		Answer* answw = new Answer;
		answw->LoadPassedTest();
		delete uu;

		system("pause");
		AdminTestMenu(2);
		break;
	}
	case 3:
	{
		system("cls");
		cout << "1 - Создать пользователя" << endl;
		cout << "2 - Удалить пользователя" << endl;
		cout << "3 - Изменить данные пользователя" << endl;
		cout << "4 - Изменить логин и пароль админа" << endl;
		cout << "0 - назад" << endl;
		int w;
		cin >> w;
		if( w == 0) AdminMainMenu();
		switch (w)
		{
		case 1:
		{
			system("cls");
			u.Register();
			system("pause");
			AdminTestMenu(3);
		}
		case 2:
		{
			system("cls");
			vector<string> tmplogin;
			vector<string> tmppass;
			int count;

			ifstream file;
			file.open("user.txt");
			if (!file.is_open())
			{
				cout << "Не удалось открыть файл " << "user.txt" << endl;
			}
			else
			{
				string lgn2, psswrd2;
				int col;
				file >> count;
				int i = 0;

				while (i < count)
				{
					file >> lgn2;
					file >> psswrd2;
					tmplogin.push_back(a.DeShifr(lgn2));
					tmppass.push_back(a.DeShifr(psswrd2));
					i++;

				}
				file.close();
			}
			
			for (int i = 0; i < tmplogin.size(); i++)
			{
				cout << i+1 << ") " << tmplogin[i] << endl;
			}

			cout << "Удалить пользователя под номером: "; int del; cin >> del;

			string path2 = tmplogin[del-1] + ".txt";
			const char* dell = path2.c_str();
			auto it = tmplogin.begin();
			advance(it, del - 1);
			tmplogin.erase(it);
			auto it2 = tmppass.begin();
			advance(it2, del - 1);
			tmppass.erase(it2);
			count--;

			ofstream fout("user.txt");

			
			fout << count << endl;
			for (auto i = tmplogin.cbegin(), j = tmppass.cbegin(); i != tmplogin.cend(); ++i, ++j)
			{
				fout << a.Shifr(*i) << endl;
				fout << a.Shifr(*j) << endl;
			}
			fout.close();
			
			remove(dell);


			system("pause");
			AdminTestMenu(3);
		}
		case 4:
		{
			system("cls");
			
			
			
			ofstream fout("admin.txt");
			string lgn, psswrd;

			cout << "Введите новый логин: "; cin >> lgn;
			cout << "Введите новый пароль: "; cin >> psswrd;
			fout << a.Shifr(lgn) << endl;
			fout << a.Shifr(psswrd) << endl;
			fout.close();
			a.SetAdmin(lgn, psswrd);
			cout << "Данные изменены!" << endl;
			system("pause");
			AdminTestMenu(3);
		}
		case 3:
		{
			vector<string> tmplogin;
			vector<string> tmppass;
			int count;

			ifstream file;
			file.open("user.txt");
			if (!file.is_open())
			{
				cout << "Не удалось открыть файл " << "user.txt" << endl;
			}
			else
			{
				string lgn2, psswrd2;
				int col;
				file >> count;
				int i = 0;

				while (i < count)
				{
					file >> lgn2;
					file >> psswrd2;
					tmplogin.push_back(a.DeShifr(lgn2));
					tmppass.push_back(a.DeShifr(psswrd2));
					i++;

				}
				file.close();
			}

			system("cls");
			for (int i = 0; i < tmplogin.size(); i++)
			{
				cout << i + 1 << ") " << tmplogin[i] << endl;
			}

			cout << "Изменить данные пользователя: "; int us; cin >> us;

			system("cls");
			string fio, adress, phone;
			cout << "Введите ФИО: "; cin.ignore(); getline(cin, fio);
			cout << "Введите адресс: "; getline(cin, adress);
			cout << "Введите телефон: "; getline(cin, phone);
			
			
			ofstream ffout;
			string path2 = tmplogin[us-1] + ".txt";
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
			cout << "Данные изменены!" << endl;
			system("pause");
			AdminTestMenu(3);
		}
		{
		default:
			break;
		}
		}
	}
	default:
		break;
	}

}
void AdminAddTestMenu(int c)
{

	switch (c)
	{
	case 1:
	{
		setlocale(0, "");
		system("cls");
		Category* cat = new Category;
		Test* t = new Test;
		TestList* tl = new TestList;
		tl->Load();
		int i = Category::Count;
		cat->Load();
		cat->Print_Category();
		cout << endl;
		int x;
		double bal;
		cout << "Введите категорию теста(цифрой): "; cin >> x;
		string task, name, a, b, cc, d, answer;
		char aa = 'A';
		cout << "Введите название теста: "; cin.ignore(); getline(cin, name);
		int k = 12;
		while (k > 0)
		{
			cout << "Введите вопрос: "; cin.ignore(); getline(cin, task);
			cout << "Введите вариант ответа А: "; getline(cin, a);
			cout << "Введите вариант ответа B: "; getline(cin, b);
			cout << "Введите вариант ответа C: "; getline(cin, cc);
			cout << "Введите вариант ответа D: "; getline(cin, d);
		Answer:
			cout << "Введите правильный ответ: "; cin >> aa;
			if (aa > 68 || aa < 65)
			{
				cout << "Неверно. Правильный ответ должен быть A, B, C иди D" << endl; goto Answer;
			}
		Again:
			cout << "Введите балл за вопрос: "; cin >> bal;
			if (bal > 12 && bal <= 0) { cout << "Ошибка! Неправильный ввод!" << endl; goto Again; }
			if ((k - bal) < 0)
			{
				cout << "Ошибка! Неправильное введены баллов. Максимально баллов до 12." << endl; goto Again;
			}

			answer = aa;
			t->AddHead(cat->GetName(x), name, task, a, b, cc, d, bal, answer);
			system("cls");
			cout << "Осталось баллов: " << t->GetBal() << endl;
			k = t->GetBal();
		}
		system("cls");
		t->Print_Test();
		t->Save();
		delete cat; delete t;
		system("pause");
		AdminTestMenu(1);
		break;
	}
	case 2:
	{
		system("cls");
		Category* cat = new Category;
		TestList* t = new TestList;
		Test* tt = new Test;
		cat->Load();
		t->Load();
		t->Print_Tests();

		cout << "1 - Посмотреть тест полностью" << endl;
		cout << "2 - удалить тест" << endl;
		cout << "0 - назад" << endl;
		int cc;
		cin >> cc;
		switch (cc)
		{
		case 1:
		{
			cout << "Введите номер теста" << endl;
			int num; cin >> num;
			tt->Load(num);
			system("cls");
			tt->Print_Test();
			system("pause");
			AdminTestMenu(1);
		}
		case 2: 
		{
			cout << "Введите номер теста чтобы удалить: " << endl;
			int num; cin >> num;
			t->DeleteTest(num);
			system("pause");
			AdminTestMenu(1);
		}
		case 0: {AdminTestMenu(1); }
		default:
			break;
		}

		delete cat; delete t;
		system("pause");
		AdminTestMenu(1);
	}
	case 3:
	{
		system("cls");
		Category* cat = new Category;
		cat->Load();
		string name;
		cout << "Введите новую категорию: "; cin.ignore(); getline(cin, name);
		cat->Add(name);
		cout << "Категория добавлена!" << endl;
		cat->Save();
		delete cat;
		system("pause");
		AdminTestMenu(1);
	}
	case 4:
	{
		system("cls");
		Category* cat = new Category;
		cat->Load();
		cat->Print_Category();
		delete cat;
		system("pause");
		AdminTestMenu(1);
	}
	case 0: AdminMainMenu();
		break;
	default:
		break;
	}
}
