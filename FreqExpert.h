#include <vector>
#include <string>
#include "Theory.h"
#include "Expert.h"
using std::vector;
using std::string;

#ifndef FREQEXPERT_H_
#define FREQEXPERT_H_

class FreqExpert: public Expert {
	vector<char> perfect_order;
public:
	FreqExpert();
	vector<Theory> derive(const Theory&, const string&);
};
#endif /* FREQEXPERT_H_ */
