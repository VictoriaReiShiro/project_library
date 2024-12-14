#ifndef rentalH
#define rentalH

#include <ctime>
#include <string>

using namespace std;

class eRental {	// Выдача книги
private:
		__int64 rId;		// Читатель
		__int64 bId;		// Книга
		time_t issue;		// Дата выдачи
		int days;				// Количество дней

public:
		eRental() { rId = -1; bId = -1; days = 0; }
		eRental(__int64 _rd, __int64 _bk, time_t _issue, int  _days);

		operator string();

		__int64 getReader() { return rId; }
		__int64 getBook() { return bId; }
		time_t getIssue() { return issue; }
		int getDays() { return days; }
		string getReturn();

		void extendTo(int _days) { days += _days; }			// Продление выдачи
};
#endif