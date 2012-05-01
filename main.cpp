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

void read_dic(){
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

class Theory{
	string from, to;
public:
	Theory(){}
	Theory(const Theory& t): from(t.from), to(t.to){}
	Theory(const string& f, const string& t):from(f), to(t){}

	bool compatible(const Theory& b){
		assert(from.size() == to.size());
		size_t n = from.size();
		for(size_t i = 0; i < n; ++i)
			for(size_t j = 0; j < i; ++j)
				if((from[i] == from[j]) ^ (to[j] == to[i]))
					return false;
		return true;
	}

	Theory join(const Theory& b){
		return Theory(from + b.from, to + b.to);		
	}

	string apply(const vector<string>& vs){
		string ans;
		for(size_t i = 0; i < vs.size(); ++i){
			for(size_t j = 0; j < vs[i].size(); ++j){
				char dans = '?';			
				for(size_t k = 0; k < from.size(); ++k)
					if(from[k] == vs[i][j]){
						dans = to[k];
						break;
					}
				ans += dans;
			}
			ans += ' ';
		}
		return ans;
	}
};

bool cmp(const vector<Theory> & a, const vector<Theory> & b){
	return a.size() > b.size();
}

void compactify(vector<vector<Theory> > & vvt){
	sort(vvt.begin(), vvt.end(), cmp);
	vector<Theory> one = vvt.back();
	vvt.pop_back();
	vector<Theory> another = vvt.back();
	vvt.pop_back();
	cout << one.size() << "\t" << another.size() << endl;
	
	vector<Theory> joint;
	for(size_t i = 0; i < one.size(); ++i)
		for(size_t j = 0; j < another.size(); ++j)
			if(one[i].compatible(another[j])){
				Theory tmp(one[i]);
				joint.push_back(tmp.join(another[j]));
			}
	vvt.push_back(joint);
}

set<Theory> olw(vector<string> vs){
	set<Theory> ans;
	for(size_t i = 0; i < vs.size(); ++i)
		if(vs[i].size() == 1){
			ans.insert(Theory(vs[i], "i"));
			ans.insert(Theory(vs[i], "a"));
		}
	return ans;
}

int main(){
	read_dic();
	ifstream fin("tests.txt");
	while (fin.good()) {
		string riddle;
		getline(fin, riddle);
		vector<string> vs = split(riddle);
		set<Theory> one_letter = olw(vs);
		
		cout << "one_letter.size() == " << one_letter.size() << endl;		
	}
}
