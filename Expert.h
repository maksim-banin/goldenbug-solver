#include <vector>
#include "Theory.h"
using std::vector;

#ifndef EXPERT_H_
#define EXPERT_H_

class Expert {
public:
	virtual vector<Theory> derive(const Theory&, const string&) = 0;
};

#endif /* EXPERT_H_ */
