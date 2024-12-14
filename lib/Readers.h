#ifndef ReadersH
#define ReadersH

#include <string>

using namespace std;

class eReader {		// Читатели
private:
	__int64 nbil;	// Номер билета
	string rName;	// Имя
	string rSurn;	// Фамилия
	string rMidl;	// Отчество
	string phone; // Телефон

public:
	eReader() { nbil = -1; rSurn = ""; rName = ""; rMidl = ""; phone = ""; }	// Пустой конструктор
	eReader(__int64 _nbil, string _rSurn, string _rName, string _rMidl, string _phone);

	operator __int64() { return nbil; }	// Перегрузка преобразования типа
	operator string() { return rSurn+" "+rName; }	// Перегрузка преобразования типа

	__int64 getBil() { return nbil; }	// Геттеры
	string getName() { return rName; }
	string getSurn() { return rSurn; }
	string getMidl() { return rMidl;  }
	string getPhone() { return phone; }
};
#endif
