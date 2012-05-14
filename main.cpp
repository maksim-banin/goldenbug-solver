#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <set>
using namespace std;

map<string, vector<string> > dic;
string normalize(const string& s) {
	string ans(s);
	for (size_t i = 0; i < s.size(); ++i)
		ans[i] = 'a' + (find(s.begin(), s.end(), ans[i]) - s.begin());
	return ans;
}

void read_dic() {
	ifstream fin("dict.txt");
	while (fin.good()) {
		string tmp;
		fin >> tmp;
		dic[normalize(tmp)].push_back(tmp);
	}
}

vector<string> split(const string& s) {
	istringstream iss(s);
	istream_iterator<string> beg(iss);
	return vector<string> (beg, istream_iterator<string> ());
}

class Theory {
	string from, to;
public:
	Theory() {
	}
	Theory(const Theory& t) :
		from(t.from), to(t.to) {
	}
	Theory(const string& f, const string& t) :
		from(f), to(t) {
	}

	bool compatible(const Theory& b) const {
		assert(from.size() == to.size());
		size_t n = from.size();
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < i; ++j)
				if ((from[i] == b.from[j]) ^ (to[j] == b.to[i]))
					return false;
		return true;
	}

	Theory join(const Theory& b) const {
		return Theory(from + b.from, to + b.to);
	}

	string apply(const vector<string>& vs) const {
		string ans;
		for (size_t i = 0; i < vs.size(); ++i) {
			for (size_t j = 0; j < vs[i].size(); ++j) {
				char dans = '?';
				for (size_t k = 0; k < from.size(); ++k)
					if (from[k] == vs[i][j]) {
						dans = to[k];
						break;
					}
				ans += dans;
			}
			ans += ' ';
		}
		return ans;
	}
	bool operator<(const Theory& other) const {
		if (from.length() != other.from.length())
			return from.length() < other.from.length();
		if (from != other.from)
			return from < other.from;
		return to < other.to;
	}
	string str() const {
		return "'" + from + "' -> '" + to + "'";
	}
};

int main() {
	read_dic();
	ifstream fin("tests.txt");
	while (fin.good()) {
		string riddle;
		getline(fin, riddle);
		vector<string> words = split(riddle);
		vector<vector< Theory> > vvt(words.size());
		for(size_t i = 0; i < words.size(); ++i){
			vector<string> decod = dic[normalize(words[i])];
			for(size_t j = 0; j < decod.size(); ++j)
				vvt[i].push_back(Theory(words[i], decod[j]));
		}
		for(size_t i = 0; i < words.size(); ++i){
			// Look at the smallest set, take such item from it that smallest remaining is biggest			
			cout << words[i] << '\t' << vvt[i].size() << '\t' << vvt[i][0].str() << '\n';
		}
		cout << '\n';
	}
}
