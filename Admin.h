#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <list>
#include <direct.h>
#include <conio.h>
#include <vector>

using namespace std;

class Admin
{
private:
	static string login_admin;
	static string password_admin;
	int Count_Admin = 0;
public:
	Admin() = default;
	void Load_Admin();
	int Check(string lgn, string psswrd);
	string Shifr(string str);
	string DeShifr(string str);
	string GetLogin();
	void LoadStat();
	void SetAdmin(string lgn, string psswrd)
	{
		Admin::login_admin = lgn;
		Admin::password_admin = psswrd;
	}
};

struct NameCategory
{
	string Name;
	NameCategory* nxt, *prv;
};
class Category
{
protected:
	NameCategory* hd, *tl;
	
public:
	static int Count;
	friend class Test;
	Category()
	{
		hd = tl = NULL;
		Count = 0;
	}
	void Delete(int pos);
	void Add(string name);
	void Print_Category();
	string GetName(int pos);
	void Save();
	void Load();
};
struct Test_data 
{
	string category;
	string NameTest;
	string Task;
	string a,b,c,d;
	double bal;
	string answer;
	Test_data* nxt, * prv;
};
class Test : public Admin
{
protected:
	Test_data* hd, * tl;
	
public:
	int Count;
	friend class Category;
	Test()
	{
		hd = tl = NULL;
		Count = 0;
	}
	~Test()
	{
		Clear();
	}
	void Clear()
	{
		while (Count != 0)
			Delete(1);
	}
	int Size()
	{
		return Count;
	}
	string Category()
	{
		Test_data* tmp = hd;
		return tmp->category;

	}
	string NameTest()
	{
		Test_data* tmp = hd;
		return tmp->NameTest;

	}
	char getAnswer(int x)
	{
		Test_data* tmp = hd;
		int i = 0;
		while (i < x)
		{
			tmp = tmp->nxt;
			i++;
		}
		string c = tmp->answer;
		char ret = c.c_str()[0];
		
		return ret;
	}
	double GetGetBall(int pos)
	{
		Test_data* tmp = hd;
		int x = 0;
		while (x < pos)
		{
			tmp = tmp->nxt;
			x++;
		}
		return tmp->bal;
	}
	void Delete(int pos);
	void AddHead(string category, string name, string taks, string a, string b, string c, string d, double bal, string answer);
	void Print_Test();
	bool Load(int num);
	void Save();
	double GetBal();
	void Print_Test(int pos);
	
	//void PrintList()
	//{
	//	for (auto i = test_list.cbegin(); i != test_list.cend(); ++i)
	//	{
	//		Print_Test();
	//	}
	//}
};

struct NameTests
{
	string category;
	string name;
	string path;

	NameTests* nxt, * prv;
};
class TestList
{
protected:
	NameTests* hd, * tl;
	
public:
	int Count;
	TestList()
	{
		hd = tl = NULL;
		Count = 0;
	}
	void Delete(int pos);
	void AddTest(string category, string name, string path);
	void Print_Tests();
	string GetPath(int pos);
	void Save();
	void Save2();
	void Load();
	void DeleteTest(int num);
	string GetCategory(int pos)
	{
		int i = 1;
		NameTests* Get = hd;
		while (i < pos)
		{
			Get = Get->nxt;
			i++;
		}
		return Get->category;
	}
	string GetName(int pos)
	{
		int i = 1;
		NameTests* Get = hd;
		while (i < pos)
		{
			Get = Get->nxt;
			i++;
		}
		return Get->name;
	}
	void AddTestBack(string category, string name, string path);
};
