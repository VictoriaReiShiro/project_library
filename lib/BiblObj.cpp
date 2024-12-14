#include "pch.h"		// ��� visual studio 2017

#define _CRT_SECURE_NO_WARNINGS		// ��� ������������� ������ � ����� � VS 2017

#include <windows.h>	// ��� �������� ������

#include <ctime>
#include <iostream>

#include "mdb.h"
#include "Books.h"
#include "Readers.h"

using namespace std;

mdb db("librum.db");		// ���� ������

void addBook() {
		__int64 id; char str[100]; string book,st; vector<__int64> auth;
		cout << "������� �������� �����: "; cin.getline(str, 100); cin.getline(str, 100); 
		book = ltrim(str); 
		for(;;) {
				for (auto p : db.getAuthors())		// ������ �������
						cout << p.first << " " << p.second << endl;
			cout << endl;
			cout << "���� �� ��� ������ ������������ � ������, ������� ��� ������: ";
			cin.getline(str, 100); st = ltrim(str); 
			if (st == "") break; 
			db.addAuthor(st);
		}
		for (;;) {
				cout << "������ ������ ������ ��� 0: "; cin >> id;
				if (id == 0) break;
				auth.push_back(id);
		}
		cout << "������� ��� �����: "; cin >> id;
		db.addBook(eBook(id,book,auth));
}

void showMenu()
{ 
	__int64 id, nbil;
	char str[100]; string st[4];
	eReader reader; eBook book;
	for (int ch;;) {
		cout << "1. ������ ����" << endl;
		cout << "2. ������ ���������" << endl;
		cout << "3. ������ �������� ����" << endl;
		cout << "4. ������ �����" << endl;
		cout << "5. �������� ������� �����" << endl;
		cout << "6. ����� ��������" << endl;
		cout << "7. ����� �����" << endl;
		cout << "8. �������� ��������" << endl;
		cout << "9. �������� �����" << endl;
		cout << "0. �����" << endl;
		cout << ">>>"; cin >> ch;
		switch (ch)
		{
		case 0:
				return;
		case 1:					// ������ ����
				for (size_t i = 0; i < db.getNBooks(); i++) {
						cout << db.getBookI(i) << ". " << string(db.getBookI(i)) << " | ������: ";
						for (size_t j = 0; j < db.getBookI(i).getCount(); j++)
								cout << db.getAuthor(db.getBookI(i)[j]) << ((j!=db.getBookI(i).getCount()-1)?", ":"");
						cout << endl;
				}
				cout << "����� " << db.getNBooks() << " ����" << endl;
				break;
		case 2:					// ������ ���������
				for (size_t i = 0; i < db.getNReaders(); i++)
					cout << db.getReaderI(i) << " " << (string)db.getReaderI(i) << " ���. " <<
								db.getReaderI(i).getPhone() << endl;
				cout << "-----------" << endl;
				break;
		case 3:					// ������ �������� ����
				for (size_t i = 0; i < db.getNRentals(); i++) 
						cout << (i+1) << ". " << string(db.getReader(db.getRental(i).getReader())) << " " <<
								string(db.getBook(db.getRental(i).getBook())) << " " <<
								string(db.getRental(i)) << " ������� " <<
								db.getRental(i).getReturn() << endl;
				cout << "�� ����� " << db.getNRentals() << " ����" << endl;
				break;
		case 4:					// ������ �����
				cout << "����� �����: "; cin >> id;
				if (db.getBook(id) != id) { cout << "����� �� �������" << endl; break; }
				cout << "����� ������������� ������: "; cin >> nbil;
				if (db.getReader(nbil) != nbil) { cout << "�������� �� ������" << endl; break; }
				cout << "������ " << string(db.getBook(id)) << " " << string(db.getReader(nbil)) << endl;
				cout << "���������� ����: "; cin >> ch;
				db.addRental(eRental(nbil, id, time(0), ch));
				break;
		case 5:					// �������� �������
				cout << "������� ����� ������: "; cin >> ch;
				db.remRental(ch-1);
				break;
		case 6:					// ����� ��������
				cout << "������� ������� ��������: "; cin.getline(str, 100); cin.getline(str, 100);
				reader = db.getReader(str);
				if (reader == -1) cout << "�������� " << str << "�� ������" << endl; else
 					cout << reader << " " << " ���. " << (string)reader << reader.getPhone() <<endl;
				break;
		case 7:					// ����� �����
				cout << "������� ������������: "; cin.getline(str, 100); cin.getline(str, 100);
				book = db.getBook(str);
				if (book == -1) { cout << "����� " << str << "�� �������" << endl; break; }
				cout << book << " "  << (string)book << endl;
				for (size_t j = 0; j < book.getCount(); j++)
						cout << db.getAuthor(book[j]) << ((j != book.getCount() - 1) ? ", " : "");
				cout << endl;
				break;
		case 8:					// ���������� ��������
				cout << "������� �������: "; cin.getline(str, 100); cin.getline(str, 100); st[0] = ltrim(str);
				cout << "������� ���: "; cin.getline(str, 100); st[1] = ltrim(str);
				cout << "������� ��������: "; cin.getline(str, 100); st[2] = ltrim(str);
				cout << "�������: "; cin.getline(str, 100); st[3] = ltrim(str);
				cout << "����� ������: "; cin >> nbil;
				db.addReader(eReader(nbil, st[0], st[1], st[2], st[3]));
				break;
		case 9:					// ���������� �����
				addBook();
				break;
		}
	}
}

int main()
{
	SetConsoleCP(811);			// ��� �������� ������ ��� 1251
	SetConsoleOutputCP(811);
	setlocale(LC_ALL, "rus");
	//system("chcp 1251");

	db.Load();
	showMenu();
	db.Save();


/* Sample:	
  db.addAuthor(1,"������� �.�.");
	db.addAuthor(4,"���� �.");
	db.addAuthor(5,"������ E.");

	db.addReader(eReader(1, "������", "����", "��������", "+7(945)223-12-71"));
	
	db.addBook(eBook(1,"����� � ���",1));
	db.addBook(eBook(2, "12 �������", { 4,5 }));

	db.addRental(eRental(1, 2, time(0), 10));
	db.addRental(eRental(3, 3, time(0), 10));
	db.getRental(3, 3).extendTo(10); /**/
}
