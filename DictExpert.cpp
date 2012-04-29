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
			vector<Theory> curr_ans;
			set<string> temp = dic.find(normalize(vs[i]))->second;
			for (set<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
				Theory curr(t);
				if (t.tryDerive(vs[i], *it, curr))
					curr_ans.push_back(curr);
			}
			if (ans.size() == 0 || (curr_ans.size() > 1 && ans.size() > curr_ans.size()))
				ans = curr_ans;
		}
	return ans;
}
