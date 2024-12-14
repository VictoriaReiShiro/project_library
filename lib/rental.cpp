#include "pch.h"		// Для visual studio 2017

#define _CRT_SECURE_NO_WARNINGS		// Для работы с датой в VS 2017

#include <ctime>
#include <string>

#include "rental.h"

using namespace std;

eRental::eRental(__int64 _rd, __int64 _bk, time_t _issue, int _days)
{
		rId = _rd; bId = _bk; issue = _issue; days = _days;
}

eRental::operator string() {
	char s[40];
	tm *now = localtime(&issue);
	strftime(s, 40, "%d.%m.%Y (%a)", now);

	return s; 
}

string eRental::getReturn() {
		char s[40];
		time_t ret = issue;
		ret += days * 24 * 60 * 60;
		tm *now = localtime(&ret);
		strftime(s, 40, "%d.%m.%Y (%a)", now);
		return s;
}
