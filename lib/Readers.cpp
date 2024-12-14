#include "pch.h"		// Для visual studio 2017

#include <string>
#include "Readers.h"

using namespace std;
// Конструктор
eReader::eReader(__int64 _nbil, string _rSurn, string _rName, string _rMidl, string _phone) {
	nbil = _nbil;
	rName = _rName; rSurn = _rSurn; rMidl = _rMidl; ; phone = _phone;
}
