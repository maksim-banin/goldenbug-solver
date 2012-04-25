#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include "DictExpert.h"

DictExpert::DictExpert() {
	ifstream fin("dict.txt");
	while (fin.good()) {
		string tmp;
		fin >> tmp;
		dic[normalize(tmp)].insert(tmp);
	}
}

vector<string> DictExpert::split(const string& s) {
	using namespace std;
	istringstream iss(s);
	istream_iterator<string> beg(iss);
	return vector<string> (beg, istream_iterator<string> ());
}

string DictExpert::normalize(const string& s) {
	using namespace std;
	string ans(s);

	for (string::iterator it = ans.begin(); it != ans.end(); ++it)
		*it = (islower(*it) ? 'a' : 'A') + (find(s.begin(), s.end(), *it) - s.begin());
	return ans;
}

vector<Theory> DictExpert::derive(const Theory &t, const string& riddle) {
	istringstream iss(riddle);
	vector<string> vs;
	while (iss.good()) {
		string tmp;
		iss >> tmp;
		vs.push_back(tmp);
	}

	vector<Theory> ans;
	for (size_t i = 0; i < vs.size(); ++i)
		if (dic.find(normalize(vs[i])) != dic.end()) {
			set<string> temp = dic.find(normalize(vs[i]))->second;
			for (set<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
				Theory curr(t);
				bool good = true;
				for (size_t j = 0; j < it->size(); ++j) {
					char from = vs[i][j], to = (*it)[j];
					if (t.used_from.count(from) && t.rules.find(from)->second != to) {
						good = false;
						break;
					}
					if (t.used_to.count(to)) {
						good = false;
						break;
					}
					curr = curr.addRule(from, to);
				}
				if (good)
					ans.push_back(curr);
			}
		}
	return ans;
}
