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

	vector<vector<Theory> > currs;
	for (size_t i = 0; i < vs.size(); ++i)
		if (dic.find(normalize(vs[i])) != dic.end()) {
			vector<Theory> curr_ans;
			set<string> temp = dic.find(normalize(vs[i]))->second;
			for (set<string>::iterator it = temp.begin(); it != temp.end(); ++it) {
				Theory curr(t);
				if (t.tryDerive(vs[i], *it, curr))
					curr_ans.push_back(curr);
			}
			currs.push_back(curr_ans);
		}

	int fails_cnt = 0;
	for (size_t i = 0; i < currs.size(); ++i)
		for (size_t j = i + 1; j < currs.size(); ++j)
			if(currs[i].size() > currs[j].size())
				swap(currs[i], currs[j]);

	vector<Theory> ans;
	for (size_t i = 0; i < currs.size(); ++i)
		for(size_t j = 0; j < currs[i].size(); ++j)
			ans.push_back(currs[i][j]);

	return fails_cnt > 1 ? vector<Theory> () : ans;
}
