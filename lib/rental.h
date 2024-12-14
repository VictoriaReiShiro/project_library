#ifndef rentalH
#define rentalH

#include <ctime>
#include <string>

using namespace std;

class eRental {	// ������ �����
private:
		__int64 rId;		// ��������
		__int64 bId;		// �����
		time_t issue;		// ���� ������
		int days;				// ���������� ����

public:
		eRental() { rId = -1; bId = -1; days = 0; }
		eRental(__int64 _rd, __int64 _bk, time_t _issue, int  _days);

		operator string();

		__int64 getReader() { return rId; }
		__int64 getBook() { return bId; }
		time_t getIssue() { return issue; }
		int getDays() { return days; }
		string getReturn();

		void extendTo(int _days) { days += _days; }			// ��������� ������
};
#endif