#include "pch.h"		// Для visual studio 2017

#include <map>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

#include "mdb.h"

void mdb::Load() {
	char str[100]; __int64 id;
	string st[4];
	ifstream ifs(dbName);
	size_t npos; 
	ifs >> npos;	// Список авторов
	for (size_t i = 0; i < npos; i++) {
			ifs >> id; ifs.getline(str, 100); st[0] = ltrim(str);
			addAuthor(id, st[0]);
	}

	ifs >> npos;	// Список читателей
	for (size_t i = 0; i < npos; i++) {
			ifs >> id; 
			ifs.getline(str, 100); st[0] = ltrim(str);
			ifs.getline(str, 100); st[1] = ltrim(str);
			ifs.getline(str, 100); st[2] = ltrim(str);
			ifs.getline(str, 100); st[3] = ltrim(str);
			addReader(eReader(id, st[0], st[1], st[2], st[3]));
	}

	ifs >> npos;	// Список книг
	size_t nauth; 
	vector<__int64> authids; __int64 aid;
	for (size_t i = 0; i < npos; i++) {
			ifs >> id;
			ifs.getline(str, 100); st[0] = ltrim(str);
			ifs >> nauth; authids.clear();
			for (size_t j = 0; j < nauth; j++) {
					ifs >> aid;
					authids.push_back(aid);	}
			addBook(eBook(id, st[0], authids));
	}

	ifs >> npos;	// Список выдач
	time_t issue; int days;
	for (size_t i = 0; i < npos; i++) {
			ifs >> id >> aid >> issue >> days;
			addRental(eRental(id, aid, issue, days));
	}
}

void mdb::Save() {
	ofstream fos(dbName);
	fos << Authors.size() << endl;
	for (auto p : Authors)		// Сохранить авторов
			fos << p.first << " " << p.second << endl;

	fos << Readers.size() << endl;
	for (size_t i = 0; i < Readers.size(); i++) {	// Сохранить читателей
		fos << Readers[i] << " " <<
		    Readers[i].getSurn() << endl <<
				Readers[i].getName() << endl <<
				Readers[i].getMidl() << endl <<
				Readers[i].getPhone() << endl;
	}

	fos << Books.size() << endl;
	for (size_t i = 0; i < Books.size(); i++) {		// Сохранить читателей
		fos << Books[i].getN() << " " << Books[i].getCapt() << endl << Books[i].getCount() << " ";
			for (size_t j = 0; j < Books[i].getCount(); j++)
					fos << Books[i][j] << " "; 
			fos << endl;
	}

	fos << Rentals.size() << endl;
	for (size_t i = 0; i < Rentals.size(); i++) {		// Сохранить выдачи
			fos << Rentals[i].getReader() << " " << Rentals[i].getBook() << " " <<
					Rentals[i].getIssue() << " " << Rentals[i].getDays() << " " << endl;
	}
}
void mdb::addAuthor(string _aName)	// Автоматически генерировать код автора
{
  for(__int64 i=1;i<0x7FFFFFFFFFFFFFFF;i++)
	  if (Authors.find(i)==Authors.end()) {
		  addAuthor(i, _aName); break;
	  }
}

string mdb::getAuthor(__int64 _id) {	// Автор по коду
  if (Authors.find(_id) == Authors.end()) return "";
  return Authors[_id];
}

__int64 mdb::getAuthId(string _name) {	// Код по имени книги
	for (auto p : Authors)
		if (p.second == _name) return p.first;
	return -1;
}

eBook mdb::getBook(__int64 _id) {		// Книга по коду
	for (size_t i = 0; i < Books.size(); i++)
		if (Books[i].getN() == _id) return Books[i];
	return eBook();
}

eBook mdb::getBook(string _capt) {		// Книга по имени
	for (size_t i = 0; i < Books.size(); i++)
		if (Books[i].getCapt() == _capt) return Books[i];
	return eBook();
}

eReader mdb::getReader(__int64 _nbil) {	// Читатель по коду
	for (size_t i = 0; i < Readers.size(); i++)
		if (Readers[i].getBil() == _nbil) return Readers[i];
	return eReader();
}

eReader mdb::getReader(string _surn) {	// Читатель по фамилии
	for (size_t i = 0; i < Readers.size(); i++)
		if (Readers[i].getSurn() == _surn) return Readers[i];
	return eReader();
}

eRental& mdb::getRental(size_t n) { 
	eRental dummy;
	return (n < Rentals.size()) ? Rentals[n] : dummy; 
}

eRental& mdb::getRental(__int64 _nbil, __int64 _id) {		// Выдача по номеру билета и книге
		for (size_t i = 0; i < Rentals.size(); i++)
			if (Rentals[i].getReader() == _nbil && Rentals[i].getBook() == _id) return Rentals[i];
  eRental dummy;
	return dummy;
}

void mdb::remReader(__int64 _nbil) {			// Удаление читателя
	size_t n = -1;
	for (size_t i = 0; i < Readers.size(); i++)
			if (Readers[i].getBil() == _nbil) { n = i; break;	}
	if (n == -1) return;
	Readers.erase(Readers.begin() + n);
}

void mdb::remBook(__int64 _id) {				// Удаление книги
		size_t n = -1;
		for (size_t i = 0; i < Books.size(); i++)
		if (Books[i].getN() == _id) { n = i; break; }
		if (n == -1) return;
		Books.erase(Books.begin() + n);
}

void mdb::remRental(size_t n)	{					// Удаление выдачи
		if (n<Rentals.size()) Rentals.erase(Rentals.begin() + n);
}