#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <io.h>
#include <stdio.h>
using namespace std;

struct Stud
{
	char fama[50];
	char group[10];
	int mat, phis, infa;
	double sr_ball;
};

void Create(FILE* file);
void ViewStud(FILE* file);
void Redact(FILE* file);
void Delete(FILE* file);
void Sort(FILE* file);
bool SravnenieBukv(char one[], char two[]);
void InfaStudentov(Stud* s);

void Menu()
{
	FILE* file = fopen("students.txt", "wb");
	fclose(file);
	bool menu = 1;
	while (menu == 1) 
	{
		cout << "1. Добавить студента в файл" << endl;
		cout << "2. Просмотреть всех студентов" << endl;
		cout << "3. Изменить информацию о студенте" << endl;
		cout << "4. Удалить студента" << endl;
		cout << "5. Сортировка" << endl;
		cout << "6. Индивидуальное задание" << endl;
		cout << "7. Выйти из программы" << endl;
		int n;
		cin >> n;
		switch (n) 
		{
		case 1: Create(file); break;
		case 2: ViewStud(file); break;
		case 3: Redact(file); break;
		case 4: Delete(file); break;
		case 5: Sort(file); break;
		case 6: menu = 0; break;
		default: cout << "Неверный ввод";
		}
	}
}

int main()
{
	Menu();
}

void Create(FILE* file) 
{
	file = fopen("students.txt", "ab");
	cout << "Введите фамилию, номер группы, оценки за математику, физику и информатику\n";
	Stud s;
	cin >> s.fama >> s.group >> s.mat >> s.phis >> s.infa;
	s.sr_ball = (s.mat + s.phis + s.infa) / 3;
	fwrite(&s, sizeof(Stud), 1, file);
	fclose(file);
}


void ViewStud(FILE* file) 
{
	file = fopen("students.txt", "rb");
	Stud s;
	int kolvo = _filelength(_fileno(file)) / sizeof(Stud);
	for (int i = 0; i < kolvo; i++) 
	{
		fread(&s, sizeof(Stud), 1, file);
		InfaStudentov(&s);
	}

	fclose(file);
}
void InfaStudentov(Stud* s)
{
	cout << " ФИО: " << s->fama << " Группа: " << s->group << " ОЦЕНКИ: Математика: " << s->mat << " Физика: " << s->phis << " Инфа: " << s->infa << " Ср. балл: " << s->sr_ball << endl << endl;
	
}


void Redact(FILE* file) 
{
	file = fopen("students.txt", "r+b");
	cout << "Введите номер студента\n";
	int n;
	cin >> n;
	cout << "Выберите то, что хотите изменить \n1) ФИО \n2) Группу \n3) Оценки\n";
	int choose;
	cin >> choose;
	Stud s;
	fseek(file, (int)(sizeof(Stud)) * (n - 1), 0);
	fread(&s, sizeof(Stud), 1, file);
	InfaStudentov(&s);
	switch (choose)
	{
	case 1: cin >> s.fama; break;
	case 2: cin >> s.group; break;
	case 3: cin >> s.mat >> s.phis >> s.infa; s.sr_ball = (s.infa + s.mat + s.phis) / 3;
	}
	fseek(file, (int)(sizeof(Stud)) * (n - 1), 0);
	fwrite(&s, sizeof(Stud), 1, file);
	fclose(file);
}

void Delete(FILE* file) 
{
	file = fopen("students.txt", "r+b");
	int kolvo = _filelength(_fileno(file)) / sizeof(Stud);
	int n;
	cout << "Введите номер студента: ";
	cin >> n;
	cout << "Вы уверены, что хотите удалить студента?\n 1.Да\n 2.Нет\n";
	int choose;
	cin >> choose;
	if (choose == 1)
	{
		Stud s;
		fseek(file, (n - 1) * sizeof(Stud), 0);
		fread(&s, sizeof(Stud), 1, file);

		for (int i = n; i < kolvo; i++) 
		{
			Stud s2;
			fread(&s2, sizeof(Stud), 1, file);
			fseek(file, (i - 1) * sizeof(Stud), 0);
			fwrite(&s2, sizeof(Stud), 1, file);
		}

		kolvo--;

		_chsize(_fileno(file), kolvo * sizeof(Stud));
	}
	fclose(file);
}

void Sort(FILE* file)
{
	file = fopen("students.txt", "r+b");
	int kolvo = _filelength(_fileno(file)) / sizeof(Stud);
	for (int i = kolvo - 1; i > 0; i--)
		for (int j = 0; j < i; j++) 
		{
			Stud s1, s2;
			fseek(file, (int)(sizeof(Stud)) * j, 0);
			fread(&s1, sizeof(Stud), 1, file);
			fread(&s2, sizeof(Stud), 1, file);
			if (SravnenieBukv(s1.fama, s2.fama)) 
			{
				fseek(file, (int)(sizeof(Stud)) * j, 0);
				fwrite(&s2, sizeof(Stud), 1, file);
				fwrite(&s1, sizeof(Stud), 1, file);

			}
		}

	fclose(file);
}
bool SravnenieBukv(char one[], char two[])
{
	for (int i = 0; i < 50; i++)
		if (one[i] > two[i])
			return true;
	return false;
}
void Sort_Sr_ball_Vbivanie(FILE* file) 
{
	file = fopen("students.txt", "r+b");
	int kolvo = _filelength(_fileno(file)) / sizeof(Stud);
	for (int i = kolvo - 1; i > 0; i--)
		for (int j = 0; j < i; j++) 
		{
			Stud s1, s2;
			fseek(file, (int)(sizeof(Stud)) * j, 0);
			fread(&s1, sizeof(Stud), 1, file);
			fread(&s2, sizeof(Stud), 1, file);
			if (s1.sr_ball < s2.sr_ball) 
			{
				fseek(file, (int)(sizeof(Stud)) * j, 0);
				fwrite(&s2, sizeof(Stud), 1, file);
				fwrite(&s1, sizeof(Stud), 1, file);

			}
		}
	fclose(file);
}
void Sort_Sr_ball_Vozrastanie(FILE* file) 
{
	file = fopen("students.txt", "r+b");
	int kolvo = _filelength(_fileno(file)) / sizeof(Stud);
	for (int i = kolvo - 1; i > 0; i--)
		for (int j = 0; j < i; j++) 
		{
			Stud s1, s2;

			fseek(file, (int)(sizeof(Stud)) * j, 0);
			fread(&s1, sizeof(Stud), 1, file);
			fread(&s2, sizeof(Stud), 1, file);
			if (s1.sr_ball > s2.sr_ball) 
			{
				fseek(file, (int)(sizeof(Stud)) * j, 0);
				fwrite(&s2, sizeof(Stud), 1, file);
				fwrite(&s1, sizeof(Stud), 1, file);

			}
		}
	fclose(file);
}
