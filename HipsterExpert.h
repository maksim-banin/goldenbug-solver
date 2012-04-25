#include <map>
#include <vector>
#include <string>
#include "Theory.h"
#include "Expert.h"
using std::vector;
using std::string;
using std::map;

#ifndef HIPSTEREXPERT_H_
#define HIPSTEREXPERT_H_

/* HipsterExpert knows all rare letter combinations */
class HipsterExpert: public Expert {
	set<string> forb;
public:
	HipsterExpert();
	vector<Theory> derive(const Theory&, const string&);
};

#endif /* HIPSTEREXPERT_H_ */
