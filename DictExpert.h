#include <vector>
#include <string>
#include <set>
#include "Expert.h"
using std::set;
using std::vector;
using std::string;

#ifndef DICTEXPERT_H_
#define DICTEXPERT_H_
/*
 * Derive new guesses based on dictionary
 */
class DictExpert: public Expert {
	map<string, set<string> > dic;

	string normalize(const string&);
	std::vector<std::string> split(const std::string& s);
    //bool whatever(set<string>::iterator it, vector<string> vs, size_t i, const Theory & t, Theory & curr);
public:
	DictExpert();
	vector<Theory> derive(const Theory&, const string&);
};

#endif /* DICTEXPERT_H_ */
