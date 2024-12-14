#include "pch.h"		// Для visual studio 2017

#define _CRT_SECURE_NO_WARNINGS		// Для использования работы с датой в VS 2017

#include <windows.h>	// для Русского текста

#include <ctime>
#include <iostream>

#include "mdb.h"
#include "Books.h"
#include "Readers.h"

using namespace std;

mdb db("librum.db");		// База данных

void addBook() {
		__int64 id; char str[100]; string book,st; vector<__int64> auth;
		cout << "Введите название книги: "; cin.getline(str, 100); cin.getline(str, 100); 
		book = ltrim(str); 
		for(;;) {
				for (auto p : db.getAuthors())		// Список авторов
						cout << p.first << " " << p.second << endl;
			cout << endl;
			cout << "Если не все авторы присутствуют в списке, введите имя автора: ";
			cin.getline(str, 100); st = ltrim(str); 
			if (st == "") break; 
			db.addAuthor(st);
		}
		for (;;) {
				cout << "Ведите номера автора или 0: "; cin >> id;
				if (id == 0) break;
				auth.push_back(id);
		}
		cout << "Введите код книги: "; cin >> id;
		db.addBook(eBook(id,book,auth));
}

void showMenu()
{ 
	__int64 id, nbil;
	char str[100]; string st[4];
	eReader reader; eBook book;
	for (int ch;;) {
		cout << "1. Список книг" << endl;
		cout << "2. Список читателей" << endl;
		cout << "3. Список выданных книг" << endl;
		cout << "4. Выдать книгу" << endl;
		cout << "5. Отметить возврат книги" << endl;
		cout << "6. Поиск читателя" << endl;
		cout << "7. Поиск книги" << endl;
		cout << "8. Добавить читателя" << endl;
		cout << "9. Добавить книгу" << endl;
		cout << "0. Выход" << endl;
		cout << ">>>"; cin >> ch;
		switch (ch)
		{
		case 0:
				return;
		case 1:					// Список книг
				for (size_t i = 0; i < db.getNBooks(); i++) {
						cout << db.getBookI(i) << ". " << string(db.getBookI(i)) << " | авторы: ";
						for (size_t j = 0; j < db.getBookI(i).getCount(); j++)
								cout << db.getAuthor(db.getBookI(i)[j]) << ((j!=db.getBookI(i).getCount()-1)?", ":"");
						cout << endl;
				}
				cout << "Всего " << db.getNBooks() << " книг" << endl;
				break;
		case 2:					// Список читателей
				for (size_t i = 0; i < db.getNReaders(); i++)
					cout << db.getReaderI(i) << " " << (string)db.getReaderI(i) << " тел. " <<
								db.getReaderI(i).getPhone() << endl;
				cout << "-----------" << endl;
				break;
		case 3:					// Список выданных книг
				for (size_t i = 0; i < db.getNRentals(); i++) 
						cout << (i+1) << ". " << string(db.getReader(db.getRental(i).getReader())) << " " <<
								string(db.getBook(db.getRental(i).getBook())) << " " <<
								string(db.getRental(i)) << " вернуть " <<
								db.getRental(i).getReturn() << endl;
				cout << "На руках " << db.getNRentals() << " книг" << endl;
				break;
		case 4:					// Выдать книгу
				cout << "Номер книги: "; cin >> id;
				if (db.getBook(id) != id) { cout << "Книга не найдена" << endl; break; }
				cout << "Номер читательского билета: "; cin >> nbil;
				if (db.getReader(nbil) != nbil) { cout << "Читатель не найден" << endl; break; }
				cout << "Выдать " << string(db.getBook(id)) << " " << string(db.getReader(nbil)) << endl;
				cout << "Количество дней: "; cin >> ch;
				db.addRental(eRental(nbil, id, time(0), ch));
				break;
		case 5:					// Отметить возврат
				cout << "Введите номер выдачи: "; cin >> ch;
				db.remRental(ch-1);
				break;
		case 6:					// Поиск читателя
				cout << "Введити фамилию читателя: "; cin.getline(str, 100); cin.getline(str, 100);
				reader = db.getReader(str);
				if (reader == -1) cout << "Читатель " << str << "не найден" << endl; else
 					cout << reader << " " << " тел. " << (string)reader << reader.getPhone() <<endl;
				break;
		case 7:					// Поиск книги
				cout << "Введити наименование: "; cin.getline(str, 100); cin.getline(str, 100);
				book = db.getBook(str);
				if (book == -1) { cout << "Книга " << str << "не найдена" << endl; break; }
				cout << book << " "  << (string)book << endl;
				for (size_t j = 0; j < book.getCount(); j++)
						cout << db.getAuthor(book[j]) << ((j != book.getCount() - 1) ? ", " : "");
				cout << endl;
				break;
		case 8:					// Добавление читателя
				cout << "Введите фамилию: "; cin.getline(str, 100); cin.getline(str, 100); st[0] = ltrim(str);
				cout << "Введите имя: "; cin.getline(str, 100); st[1] = ltrim(str);
				cout << "Введите отчество: "; cin.getline(str, 100); st[2] = ltrim(str);
				cout << "Телефон: "; cin.getline(str, 100); st[3] = ltrim(str);
				cout << "Номер билета: "; cin >> nbil;
				db.addReader(eReader(nbil, st[0], st[1], st[2], st[3]));
				break;
		case 9:					// Добавление книги
				addBook();
				break;
		}
	}
}

int main()
{
	SetConsoleCP(811);			// для Русского текста или 1251
	SetConsoleOutputCP(811);
	setlocale(LC_ALL, "rus");
	//system("chcp 1251");

	db.Load();
	showMenu();
	db.Save();


/* Sample:	
  db.addAuthor(1,"Толстой Л.Н.");
	db.addAuthor(4,"Ильф И.");
	db.addAuthor(5,"Петров E.");

	db.addReader(eReader(1, "Петров", "Иван", "Петрович", "+7(945)223-12-71"));
	
	db.addBook(eBook(1,"Война и мир",1));
	db.addBook(eBook(2, "12 стульев", { 4,5 }));

	db.addRental(eRental(1, 2, time(0), 10));
	db.addRental(eRental(3, 3, time(0), 10));
	db.getRental(3, 3).extendTo(10); /**/
}
