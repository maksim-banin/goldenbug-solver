#include <fstream>
#include "HipsterExpert.h"

HipsterExpert::HipsterExpert() {
	ifstream fin("forbidden.txt");
	while (fin.good()) {
		string tmp;
		getline(fin, tmp);
		forb.insert(tmp);
	}
}

vector<Theory> HipsterExpert::derive(const Theory&t, const string& riddle) {
	for (size_t i = 0; i < riddle.size() - 1; ++i)
		if (t.used_from.count(riddle[i]) && t.used_from.count(riddle[i + 1]) && forb.count(riddle.substr(i, 2)))
			return vector<Theory> ();
	return vector<Theory> (1, t);
}
