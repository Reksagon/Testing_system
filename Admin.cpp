#include "Admin.h"

string Admin::login_admin;
string Admin::password_admin;
int Category::Count;
string path_admin = "admin.txt";
int test_num = 1;
int p = 3;

int Admin:: Check(string lgn, string psswrd)
{

	while (p>0)
	{
		if (Admin::login_admin == lgn && Admin::password_admin == psswrd) { return 1; break; }
		else { system("cls"); p--; cout << "Неправильынй логин или пароль. Осталось попыток: " << p << endl; return 2;}
	}
	return 3;

}
void Admin::Load_Admin()
{
	ifstream file(path_admin);

	if (!file.is_open())
	{
		string lgn, psswrd;
		file.open(path_admin);
		cout << "Введите логин:" << endl;
		cin >> lgn;
		cout << "Введите пароль:" << endl;
		cin >> psswrd;

		ofstream fout(path_admin);

			fout << Shifr(lgn) << endl;
			fout << Shifr(psswrd) << endl;

		fout.close();
		Admin::login_admin = lgn;
		Admin::password_admin = psswrd;
		system("cls");
		cout << "Вы успешно зарегистрировались в системе!" << endl;

	}
	else
	{
		string lgn, psswrd;
	
		file >> lgn;
		file >> psswrd;
		
		Admin::login_admin = DeShifr(lgn);
		Admin::password_admin = DeShifr(psswrd);
		file.close();
	}
}
string Admin::Shifr(string str)
{
	string* str2 = new string;
	*str2 = " ";
	int a;
	for (int i = 0; i < str.length(); i++)
	{
		a = str[i];
		if (a == 32)
			*str2 += a;
		else
			*str2 += a + 3;
	}

	str = *str2;
	return str;
}
string Admin::DeShifr(string str)
{
	string* str3 = new string;
	int b;
	for (int i = 0; i < str.length(); i++)
	{
		b = str[i];

		if (b == 32)
			*str3 += b;
		else
			*str3 += b - 3;
	}

	str = *str3;
	return str;
}
string Admin::GetLogin()
{
	return login_admin;
}



//************************************************************************************************************************************************
//Category

void Category::Delete(int pos)
{
	if (pos < 1 || pos > Count)
	{
		cout << "Не правильная позиция!!!\n";
		return;
	}
	int i = 1;
	NameCategory* Deletee = hd;
	while (i < pos)
	{
		Deletee = Deletee->nxt;
		i++;
	}
	NameCategory* PrevDelete = Deletee->prv;
	NameCategory* AfterDelete = Deletee->nxt;
	if (PrevDelete != 0 && Count != 1)
		PrevDelete->nxt = AfterDelete;
	if (AfterDelete != 0 && Count != 1)
		AfterDelete->prv = PrevDelete;
	if (pos == 1)
		hd = AfterDelete;
	if (pos == Count)
		tl = PrevDelete;
	delete Deletee;
	Count--;
}
void Category::Add(string name)
{
	NameCategory* temp = new NameCategory();
	temp->prv = NULL;
	temp->Name = name;
	temp->nxt = hd;

	if (Count == NULL)
		hd = tl = temp;
	else
		hd = temp;
	Count++;
}
void Category::Print_Category()
{

	if (hd == NULL) return;
	else
	{
		NameCategory* tmp;

		tmp = hd;
		int i = 0;
		while (i < Count)
		{
			cout << i+1 << " - категория: " << tmp->Name << endl;
			tmp = tmp->nxt;
			i++;
		}
	}


}
string Category::GetName(int pos)
{
int i = 1;
NameCategory* Get = hd;
while (i < pos)
{
	Get = Get->nxt;
	i++;
}
return Get->Name;
}
void Category::Save()
{
	string path = "category.txt";
	ofstream fout(path);
	if (!fout.is_open())
	{
		cout << "Ошибка! Файлы не сохранены!" << endl;
	}
	else
	{
		NameCategory* temp = hd;

		while (temp != NULL)
		{
			fout << temp->Name << " ";
			temp = temp->nxt;
		}
		fout.close();
		cout << "Категории сохранены!" << endl;
	}
}
void Category::Load()
{
	string path = "category.txt";
	ifstream file(path);

	if (!file.is_open())
	{
		cout << "Can't open file " << path << endl << endl;
	}
	else
	{
		string s;
		while (file >> s)
		{

			NameCategory* temp = new NameCategory;
			temp->Name = s;
			Add(temp->Name);
		}
		file.close();

	}



}
//************************************************************************************************************************************************
//Test
string Transliterate(string& str1)
{
	for (int i = 0; i < str1.size(); i++)
	{
		switch (str1[i])
		{
		case 'а': str1[i] = 'a'; break;
		case 'б': str1[i] = 'b'; break;
		case 'в': str1[i] = 'v'; break;
		case 'г': str1[i] = 'g'; break;
		case 'д': str1[i] = 'd'; break;
		case 'е': str1[i] = 'e'; break;
		case 'ё': str1[i] = 'ye'; break;
		case 'ж': str1[i] = 'zh'; break;
		case 'з': str1[i] = 'z'; break;
		case 'и': str1[i] = 'i'; break;
		case 'й': str1[i] = 'y'; break;
		case 'к': str1[i] = 'k'; break;
		case 'л': str1[i] = 'l'; break;
		case 'м': str1[i] = 'm'; break;
		case 'н': str1[i] = 'n'; break;
		case 'о': str1[i] = 'o'; break;
		case 'п': str1[i] = 'p'; break;
		case 'р': str1[i] = 'r'; break;
		case 'с': str1[i] = 's'; break;
		case 'т': str1[i] = 't'; break;
		case 'у': str1[i] = 'u'; break;
		case 'ф': str1[i] = 'f'; break;
		case 'х': str1[i] = 'ch'; break;
		case 'ц': str1[i] = 'z'; break;
		case 'ч': str1[i] = 'ch'; break;
		case 'ш': str1[1] = 'sh'; break;
		case 'щ': str1[i] = 'ch'; break;
		case 'ъ': str1[i] = 'b'; break;
		case 'ы': str1[i] = 'y'; break;
		case 'ь': str1[i] = 'b'; break;
		case 'э': str1[i] = 'e'; break;
		case 'ю': str1[i] = 'yu'; break;
		case 'я': str1[i] = 'ya'; break;
		case 'А': str1[i] = 'A'; break;
		case 'Б': str1[i] = 'B'; break;
		case 'В': str1[i] = 'V'; break;
		case 'Г': str1[i] = 'G'; break;
		case 'Д': str1[i] = 'D'; break;
		case 'Е': str1[i] = 'E'; break;
		case 'Ё': str1[i] = 'Ye'; break;
		case 'Ж': str1[i] = 'Zh'; break;
		case 'З': str1[i] = 'Z'; break;
		case 'И': str1[i] = 'I'; break;
		case 'Й': str1[i] = 'Y'; break;
		case 'К': str1[i] = 'K'; break;
		case 'Л': str1[i] = 'L'; break;
		case 'М': str1[i] = 'M'; break;
		case 'Н': str1[i] = 'N'; break;
		case 'О': str1[i] = 'O'; break;
		case 'П': str1[i] = 'P'; break;
		case 'Р': str1[i] = 'R'; break;
		case 'С': str1[i] = 'S'; break;
		case 'Т': str1[i] = 'T'; break;
		case 'У': str1[i] = 'U'; break;
		case 'Ф': str1[i] = 'F'; break;
		case 'Х': str1[i] = 'Ch'; break;
		case 'Ц': str1[i] = 'Z'; break;
		case 'Ч': str1[i] = 'Ch'; break;
		case 'Ш': str1[i] = 'Sh'; break;
		case 'Щ': str1[i] = 'Ch'; break;
		case 'Ъ': str1[i] = 'b'; break;
		case 'Ы': str1[i] = 'Y'; break;
		case 'Ь': str1[i] = 'b'; break;
		case 'Э': str1[i] = 'E'; break;
		case 'Ю': str1[i] = 'Yu'; break;
		case 'Я': str1[i] = 'Ya'; break;

		}
	}
	return str1;
}
void Test::Delete(int pos)
{
	if (pos < 1 || pos > Count)
	{
		cout << "Не правильная позиция!!!\n";
		return;
	}
	int i = 1;
	Test_data* Deletee = hd;
	while (i < pos)
	{
		Deletee = Deletee->nxt;
		i++;
	}
	Test_data* PrevDelete = Deletee->prv;
	Test_data* AfterDelete = Deletee->nxt;
	if (PrevDelete != 0 && Count != 1)
		PrevDelete->nxt = AfterDelete;
	if (AfterDelete != 0 && Count != 1)
		AfterDelete->prv = PrevDelete;
	if (pos == 1)
		hd = AfterDelete;
	if (pos == Count)
		tl = PrevDelete;
	delete Deletee;
	Count--;
}
void Test::AddHead(string category, string name, string task, string a, string b, string c, string d, double bal, string answer)
{
	Test_data* temp = new Test_data();
	temp->prv = NULL;
	temp->category = category;
	temp->NameTest = name;
	temp->Task = task;
	temp->a = a;
	temp->b = b;
	temp->c = c;
	temp->d = d;
	temp->bal = bal;
	temp->answer = answer;
	temp->nxt = hd;

	if (Count == NULL)
		hd = tl = temp;
	else
		hd = temp;
	Count++;
}
void Test::Print_Test()
{
	if (hd == NULL) return;
	else
	{
		Test_data* tmp;

		tmp = hd;
		int i = 0;
		cout << "Категория: " << tmp->category << endl;
		cout << "Тест: " << tmp->NameTest << endl << endl;
		while (tmp!=NULL)
		{

			cout << i + 1 << ": " << tmp->Task << "(" << tmp->bal << " балла):" << endl;
			cout << "A." << tmp->a << endl;
			cout << "B." << tmp->b << endl;
			cout << "C." << tmp->c << endl;
			cout << "D." << tmp->d << endl;
			cout << "Правильный ответ: " << tmp->answer << endl << endl;
			tmp = tmp->nxt;
			i++;
		}
	}
}
double Test::GetBal() 
{
	int i = 0;
	double get = 0;
	Test_data* Get = hd;
	while (i < Count)
	{
		get += Get->bal;
		Get = Get->nxt;
		i++;
	}
	return (12 - get);
}
void Test::Save()
{
	
	TestList* tl = new TestList;
	Test_data* tmp = hd;
	string trans = tmp->category;
	string cat = tmp->category;
	string name = tmp->NameTest;
	string path = Transliterate(trans);
	string num = to_string(test_num);
	path += num + ".txt";
		ofstream fout;
		fout.open(path);
		if (!fout.is_open())
		{
			cout << "Ошибка! Файлы не сохранены!" << endl;
		}
		else
		{
			fout << tmp->category << endl;
			fout << tmp->NameTest << endl;
			while (tmp != NULL)
			{
				fout << tmp->Task << endl;
				fout << tmp->a << endl;
				fout << tmp->b << endl;
				fout << tmp->c << endl;
				fout << tmp->d << endl;
				fout << tmp->bal << endl;
				fout << tmp->answer << endl;
				tmp = tmp->nxt;
			}
			
			cout << "Тест сохранен!" << endl;
			tl->AddTest(cat, name, path);
			tl->Save();
			fout.close();
			++test_num;
		}

		ifstream file("user.txt");
		vector<string> log_u, pas_u;
		if (!file.is_open())
		{
			cout << "Не удалось открыть файл " << "user.txt" << endl;

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
				log_u.push_back(DeShifr(lgn));
				pas_u.push_back(DeShifr(psswrd));
				i++;
			}
			file.close();
		}
		tmp = hd;
		for (int i = 0; i < log_u.size(); i++)
		{
			string p = log_u[i] + "-Test.txt";
			ofstream oout;
			oout.open(p, ios::app);
			if (!oout.is_open())
			{
				cout << "Erroe" << endl;
			}
			else
			{
				oout << tmp->category << endl;
				oout << tmp->NameTest << endl;
				oout << "Не сдан" << endl;
				oout.close();
			}
		}
	}
bool Test::Load(int num)
{
	TestList* tl = new TestList;
	tl->Load();

	string path = tl->GetPath(num);

		ifstream file(path);

		if (!file.is_open())
		{
			cout << "Файл не открыт!" << endl;
		}
		else
		{
			Test_data* temp = new Test_data;
			string cat, name;
			getline(file, cat);
			getline(file, name);

			string task, a, b ,c ,d ,bal, answer;
			while (getline(file, task))
			{
				getline(file, a);
				getline(file, b);
				getline(file, c);
				getline(file, d);
				getline(file, bal);
				int bb = atoi(bal.c_str());
				getline(file, answer);
				AddHead(cat, name, task, a, b, c, d,bb ,answer);
			}
			file.close(); 

		}

	return false;
}
//void Test::AllTest()
//{
//	if (hd == NULL) return;
//	else
//	{
//		Test_data* tmp;
//
//		tmp = hd;
//		int i = 0;
//		string cat = tmp->category;
//		cout << "Категория: " << cat << endl;
//		while (i < Count)
//		{
//			if (cat != tmp->category) 
//			{
//				cat = tmp->category;
//				cout << "Категория: " << cat << endl;
//			}
//			cout << i+1 << ". Тест: " << tmp->NameTest << endl;
//			tmp = tmp->nxt;
//			i++;
//		}
//	}
//}
void Test::Print_Test(int pos)
{
	//if (pos < 1 || pos > Count)
	//{
	//	// Неверная позиция
	//	cout << "Неверная позиция !!!\n";
	//	return;
	//}
	Test_data* tmp = hd;



	int i = 0;
	while (i < pos)
	{
		tmp = tmp->nxt;
		i++;
	}
		
	cout << "Категория: " << tmp->category << endl;
	cout << "Тест: " << tmp->NameTest << endl << endl;
	
	cout << i + 1 << ": " << tmp->Task << "(" << tmp->bal << " балла):" << endl;
		cout << "A." << tmp->a << endl;
		cout << "B." << tmp->b << endl;
		cout << "C." << tmp->c << endl;
		cout << "D." << tmp->d << endl;
		//tmp = tmp->nxt;
		//i++;
	
	cout << endl;
}
//******************************************************************************************************************************
//*****************************************************************************************************************************
void TestList::Delete(int pos)
{
	if (pos < 1 || pos > Count)
	{
		cout << "Не правильная позиция!!!\n";
		return;
	}
	int i = 1;
	NameTests* Deletee = hd;
	while (i < pos)
	{
		Deletee = Deletee->nxt;
		i++;
	}
	NameTests* PrevDelete = Deletee->prv;
	NameTests* AfterDelete = Deletee->nxt;
	if (PrevDelete != 0 && Count != 1)
		PrevDelete->nxt = AfterDelete;
	if (AfterDelete != 0 && Count != 1)
		AfterDelete->prv = PrevDelete;
	if (pos == 1)
		hd = AfterDelete;
	if (pos == Count)
		tl = PrevDelete;
	delete Deletee;
	Count--;
}
void TestList::AddTest(string category, string name, string path)
{
	NameTests* temp = new NameTests();
	temp->prv = NULL;
	temp->category = category;
	temp->name = name;
	temp->path = path;
	temp->nxt = hd;

	if (Count == NULL)
		hd = tl = temp;
	else
		hd = temp;
	Count++;
}
void TestList::AddTestBack(string category, string name, string path)
{
	NameTests* temp = new NameTests();
	temp->nxt = NULL;
	temp->category = category;
	temp->name = name;
	temp->path = path;
	temp->prv = tl;
	if (tl != 0)
		tl->nxt = temp;
	if (Count == 0)
		hd = tl = temp;
	else
		tl = temp;
	Count++;
}
void TestList::Print_Tests()
{
	Category* cat = new Category;
	if (hd == NULL) return;
	else
	{
		NameTests* tmp;

		tmp = hd;
		int i = 0;
		while (i < Count)
		{	
			cout << " Категория: " << tmp->category << endl;
			cout << i + 1 << ". " << tmp->name << endl << endl;
			tmp = tmp->nxt;
			i++;
				
		}

	}


}
string TestList::GetPath(int pos)
{
	int i = 1;
	NameTests* Get = hd;
	while (i < pos)
	{
		Get = Get->nxt;
		i++;
	}
	return Get->path;
}
void TestList::Save()
{
	string path = "list_tests.txt";
	ofstream fout;
	fout.open(path, fstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка! Файлы не сохранены!" << endl;
	}
	else
	{
		NameTests* temp = hd;

		while (temp != NULL)
		{
			fout << temp->category << endl;
			fout << temp->name << endl;
			fout << temp->path << endl;
			temp = temp->nxt;
		}
		fout.close();
		//cout << "Категории сохранены!" << endl;
	}
}
void TestList::Save2()
{
	string path = "list_tests.txt";
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())
	{
		cout << "Ошибка! Файлы не сохранены!" << endl;
	}
	else
	{
		NameTests* temp = hd;

		while (temp != NULL)
		{
			fout << temp->category << endl;
			fout << temp->name << endl;
			fout << temp->path << endl;
			temp = temp->nxt;
		}
		fout.close();
		//cout << "Категории сохранены!" << endl;
	}
}
void TestList::Load()
{
	string path = "list_tests.txt";
	ifstream file(path);

	if (!file.is_open())
	{
		cout << "Ошибка! Файлы не открыты " << path << endl << endl;
	}
	else
	{
		string s;
		while (getline(file, s))
		{

			NameTests* temp = new NameTests;
			temp->category = s;
			getline(file,temp->name);
			getline(file,temp->path);
			AddTestBack(temp->category, temp->name, temp->path);
		}
		file.close();

	}

	test_num = Count+1;

}
void TestList::DeleteTest(int num)
{

	TestList* tl = new TestList;
	tl->Load();
	if (num > tl->Count) { cout << "Ошибка. Неправильный индекс теста! " << endl; return; }
	string path = tl->GetPath(num);
	
	tl->Delete(num);
	char removename[255];
	strcpy(removename, path.c_str());
	remove(removename);
	tl->Save2();
	cout << "Тест удален!" << endl;

}
