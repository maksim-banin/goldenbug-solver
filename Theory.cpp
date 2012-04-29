#include <map>
#include <set>
#include <string>

#include "Theory.h"
using namespace std;

Theory::Theory() :
	rules(), used_from(), used_to() {
}

Theory::Theory(const Theory& t) :
	rules(t.rules), used_from(t.used_from), used_to(t.used_to) {
}

Theory::Theory(const map<char, char> & R, const set<char>& UF, const set<char>& UT) :
	rules(R), used_from(UF), used_to(UT) {
}

Theory Theory::addRule(char from, char to) const {
	Theory ans(rules, used_from, used_to);
	ans.rules[from] = to;
	ans.used_from.insert(from);
	ans.used_to.insert(to);
	return ans;
}

string Theory::apply(const string& str) {
	string ans;
	for (size_t i = 0; i < str.size(); ++i)
		if (str[i] == ' ')
			ans += ' ';
		else if (rules.find(str[i]) != rules.end())
			ans += 'A' - 'a' + rules[str[i]];
		else
			ans += str[i];
	return ans;
}

bool Theory::isFinished(const string& str) const {
	for (size_t i = 0; i < str.size(); ++i)
		if (rules.find(str[i]) == rules.end())
			return false;
	return true;
}

bool Theory::operator<(const Theory& other) const {
	return rules < other.rules;
}

