#ifndef BooksH
#define BooksH

#include <string>
#include <vector>

using namespace std;

class eBook {
private:
	__int64 nbook;	// ����������� �����
	string capt;	// ������������
	vector <__int64> authors;	// ������
public:
	// ������������
	eBook() { nbook = -1; capt = ""; authors.clear(); }	// ������ �����������
	eBook(__int64 _nbook, string _capt);
	eBook(__int64 _nbook, string _capt, int _author);
	eBook(__int64 _nbook, string _capt, vector<__int64> _authors);
	// �������� ������
	void addAuthor(__int64 _author) { authors.push_back(_author); }

	operator __int64() { return nbook; }	// ���������� �������������� ����
	operator string() { return capt; }
	__int64 operator[](size_t n) { return getAuthor(n); }	// �������� ��������������

	__int64 getN() { return nbook; }	// �������
	string getCapt() { return capt; }
	__int64 getAuthor(size_t n) { return (n<authors.size())?authors[n]:-1; }
	size_t getCount() { return authors.size(); }	// ���������� �������
	
};
#endif
