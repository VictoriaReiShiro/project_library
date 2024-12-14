#ifndef BooksH
#define BooksH

#include <string>
#include <vector>

using namespace std;

class eBook {
private:
	__int64 nbook;	// Инвентарный номер
	string capt;	// Наименование
	vector <__int64> authors;	// Авторы
public:
	// Конструкторы
	eBook() { nbook = -1; capt = ""; authors.clear(); }	// Пустой конструктор
	eBook(__int64 _nbook, string _capt);
	eBook(__int64 _nbook, string _capt, int _author);
	eBook(__int64 _nbook, string _capt, vector<__int64> _authors);
	// Добавить автора
	void addAuthor(__int64 _author) { authors.push_back(_author); }

	operator __int64() { return nbook; }	// Перегрузка преобразования типа
	operator string() { return capt; }
	__int64 operator[](size_t n) { return getAuthor(n); }	// Оператор индексирования

	__int64 getN() { return nbook; }	// Геттеры
	string getCapt() { return capt; }
	__int64 getAuthor(size_t n) { return (n<authors.size())?authors[n]:-1; }
	size_t getCount() { return authors.size(); }	// Количество авторов
	
};
#endif
