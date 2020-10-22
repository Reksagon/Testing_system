#pragma once
#include "Admin.h"
#include <vector>
#include <string>

class User : public Admin
{
protected:
	static string login_user;
	static string password_user;
	int Count_User = 0;
	string FIO;
	string HomeAdress;
	string Phone;
public:
	User() = default;
	void Load_User();
	int Check(string lgn, string psswrd);
	string GetLogin();
	void Register();
	string GetFio()
	{
		return FIO;
	}
	string GetHomeAdress()
	{
		return HomeAdress;
	}
	string GetPhone()
	{
		return Phone;
	}
	void LoadDataUser();
	void UserTest();
	void SetLgnPsw(string l, string p)
	{
		User::login_user = l; User::password_user = p;
	}


};


class Answer : public Test, public User
{
public:
	string category;
	string NameTest;
	vector<char> answer;
	double ball = 0;
	int correct = 0, incorrect = 0;
	string pathfile;
	Answer() = default;
	void AddAnswer(char a)
	{
		answer.push_back(a);
	}
	void Show()
	{
		for (auto &element : answer)
		{
			cout << element << " ";
		}
	}
	void Set(string cat, string name)
	{
		this->category = cat;
		this->NameTest = name;
	}
	void Ball(double b)
	{
		ball += b;
	}
	bool Check(char var, int x, int y)
	{
		Test* tt = new Test;
		tt->Load(y);
		if (var == tt->getAnswer(x)) { correct++; return true; }
		else { incorrect++; return false; }
	}

	void Save();
	void LoadPassedTest();
};

class UserTestList : public TestList, User
{
public:
	vector<string> name_test;
	vector<string> category_test;
	vector<string> status;

	UserTestList() = default;
	void Add(string cat, string name,string status)
	{
		name_test.push_back(name);
		category_test.push_back(cat);
		this->status.push_back(status);
	}

	void LoadUserTestList()
	{
		string path = login_user + "-Test.txt";
		ifstream file(path);
		if (!file.is_open())
		{
			file.open(path);
			TestList* t = new TestList;
			t->Load();
			for (int i = 1; i < t->Count+1; i++)
			{
				name_test.push_back(t->GetName(i));
				category_test.push_back(t->GetCategory(i));
				status.push_back("Не сдан");
			}
			ofstream out(path);
			int i = 0;
			while (i < name_test.size())
			{
				out << category_test[i] << endl;
				out << name_test[i] << endl;
				out << "Не сдан" << endl;
				i++;
			}
			out.close();
		}
		else
		{
			string s;
			while (getline(file, s))
			{
				category_test.push_back(s);
				string name = "";
				getline(file, name);
				name_test.push_back(name);
				string status1 = "";
				getline(file, status1);
				status.push_back(status1);
			}
		}
		file.close();
	}

	void PrintUserTestList()
	{
		for (int i = 0; i < category_test.size(); i++)
		{
			cout << i+1 << ") Категория: " << category_test[i] << endl;
			cout << "Тест: " << name_test[i] << "\t Статус: " << status[i] << endl << endl;
		}
	}

	void SetPassed(int pos)
	{
		status[pos - 1] = "Сдан";
	}

	void SaveUserTestList()
	{
		string path = login_user + "-Test.txt";
		ofstream file(path);
		if (!file.is_open())
		{
			cout << "Error" << endl;
		}
		else
		{
			int i = 0;
			while (i < name_test.size())
			{
				file << category_test[i] << endl;
				file << name_test[i] << endl;
				file << status[i] << endl;
				i++;
			}
		}
		file.close();
	}

	string GetStatus(int pos)
	{
		return status[pos - 1];
	}
};
