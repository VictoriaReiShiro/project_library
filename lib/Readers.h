#ifndef ReadersH
#define ReadersH

#include <string>

using namespace std;

class eReader {		// ��������
private:
	__int64 nbil;	// ����� ������
	string rName;	// ���
	string rSurn;	// �������
	string rMidl;	// ��������
	string phone; // �������

public:
	eReader() { nbil = -1; rSurn = ""; rName = ""; rMidl = ""; phone = ""; }	// ������ �����������
	eReader(__int64 _nbil, string _rSurn, string _rName, string _rMidl, string _phone);

	operator __int64() { return nbil; }	// ���������� �������������� ����
	operator string() { return rSurn+" "+rName; }	// ���������� �������������� ����

	__int64 getBil() { return nbil; }	// �������
	string getName() { return rName; }
	string getSurn() { return rSurn; }
	string getMidl() { return rMidl;  }
	string getPhone() { return phone; }
};
#endif
