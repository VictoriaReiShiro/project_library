#ifndef mdbH
#define mdbH

#include <map>
#include <vector>
#include <string>

#include "Books.h"
#include "Readers.h"
#include "Rental.h"

using namespace std;

const string BLANKS = " \n\r\t\f\v";
static string ltrim(const std::string &s)
{
		size_t start = s.find_first_not_of(BLANKS);
		return (start == string::npos) ? "" : s.substr(start);
}

class mdb {	// ����� ���� ������
private:
	map<__int64, string> Authors;	// ������
	vector<eBook> Books;			// �����
	vector<eReader> Readers;	// ��������
	vector<eRental> Rentals;	// ������ ����

	string dbName;				// ��� ��
public:
	mdb(string _dbName) { Authors.clear(); Books.clear(); Readers.clear();  dbName = _dbName; }

	void Load();	// ��������
	void Save();	// ����������

	// ���������� ������
	void addAuthor(__int64 _id, string _aName) { Authors[_id] = _aName; }
	void addAuthor(string _aName);

	map<__int64, string> getAuthors() { return Authors; }

	// ���������� �����
	void addBook(eBook _book) { Books.push_back(_book);  }
	// ���������� ��������
	void addReader(eReader _reader) { Readers.push_back(_reader); }
	// ���������� ������
	void addRental(eRental _rental) { Rentals.push_back(_rental); }

	size_t getNBooks() { return Books.size(); }	// ����������
	size_t getNReaders() { return Readers.size(); }
	size_t getNAuthors() { return Authors.size(); }
	size_t getNRentals() { return Rentals.size(); }

	string getAuthor(__int64 _id);		// ��������� ������
	__int64 getAuthId(string _name);

	eBook getBook(__int64 _id);				// �����
	eBook getBook(string _capt);
	eBook getBookI(size_t n) { return (n<Books.size())?Books[n]:eBook(); }
		
	eReader getReader(__int64 _nbil);	// ��������
	eReader getReader(string _surn);
	eReader getReaderI(size_t n) { return (n<Readers.size())?Readers[n]:eReader(); }
																			// ������
	eRental& getRental(__int64 _nbil, __int64 _book);
	eRental& getRental(size_t n);

	void remReader(__int64 _id);		// ��������
	void remBook(__int64 _id);
	void remRental(size_t n);
};

#endif