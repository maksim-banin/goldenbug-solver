#include <map>
#include <set>
#include <string>
using namespace std;
#ifndef THEORY_H_
#define THEORY_H_

class Theory {
	map<char, char> rules;
	set<char> used_from, used_to;

public:
	Theory();
	Theory(const Theory& t);
	Theory(const map<char, char> & R, const set<char>& UF, const set<char>& UT);
	Theory addRule(char from, char to) const;
	string apply(const string& str) const;
	bool tryDerive(const string& p_from, const string& p_to, Theory & curr) const;
	bool hasFrom(char c) const;
	bool hasTo(char c) const;
	bool isFinished(const string& str) const;
	bool operator<(const Theory& other) const;
};

#endif /* THEORY_H_ */
