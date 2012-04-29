#include <map>
#include <set>
#include <string>
using namespace std;
#ifndef THEORY_H_
#define THEORY_H_

struct Theory {
	map<char, char> rules;
	set<char> used_from, used_to;

	Theory();
	Theory(const Theory& t);
	Theory(const map<char, char> & R, const set<char>& UF, const set<char>& UT);
	Theory addRule(char from, char to) const;
	string apply(const string& str);
	bool isFinished(const string& str);
	bool operator<(const Theory& other) const;
};

#endif /* THEORY_H_ */
