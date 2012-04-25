#include <vector>
#include <string>
#include <set>
#include "Expert.h"
using std::set;
using std::vector;
using std::string;

#ifndef DICTEXPERT_H_
#define DICTEXPERT_H_
class DictExpert: public Expert {
	map<string, set<string> > dic;

	string normalize(const string&);
	std::vector<std::string> split(const std::string& s);
public:
	DictExpert();
	vector<Theory> derive(const Theory&, const string&);
};

#endif /* DICTEXPERT_H_ */
