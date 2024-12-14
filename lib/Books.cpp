#include "pch.h"		// Äëÿ visual studio 2017

#include "Books.h"

eBook::eBook(__int64 _nbook, string _capt) {
	nbook = _nbook; capt = _capt; authors.clear(); 
}

eBook::eBook(__int64 _nbook, string _capt, int _author) {
	nbook = _nbook; capt = _capt; 
	authors.clear(); authors.push_back(_author);
}


eBook::eBook(__int64 _nbook, string _capt, vector<__int64> _authors) {
	nbook = _nbook; capt = _capt; authors.clear(); 
	authors.assign(_authors.begin(), _authors.end());
}