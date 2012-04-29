#include <algorithm>
#include <fstream>
#include <iostream>
#include "Theory.h"
#include "FreqExpert.h"
using namespace std;

FreqExpert::FreqExpert() {
	ifstream fin("freq.txt");
	vector<pair<double, char> > vpdc;
	for (char c = 'a'; c <= 'z'; ++c) {
		double tmp;
		fin >> tmp;
		vpdc.push_back(make_pair(tmp, c));
	}

	sort(vpdc.begin(), vpdc.end());
	reverse(vpdc.begin(), vpdc.end());

	for (size_t i = 0; i < vpdc.size(); ++i)
		perfect_order.push_back(vpdc[i].second);
}

vector<Theory> FreqExpert::derive(const Theory& t, const string& riddle) {
	map<char, int> mci;
	for (size_t i = 0; i < riddle.size(); ++i)
		if (riddle[i] != ' ')
			++mci[riddle[i]];

	vector<pair<int, char> > vpic;
	for (map<char, int>::iterator it = mci.begin(); it != mci.end(); ++it)
		vpic.push_back(make_pair(it->second, it->first));

	sort(vpic.begin(), vpic.end());
	reverse(vpic.begin(), vpic.end());

	vector<char> real_order;
	for (size_t i = 0; i < vpic.size(); ++i)
		real_order.push_back(vpic[i].second);

	size_t fi = 0, ti = 0;
	for (; fi < real_order.size(); ++fi)
		if (!t.hasFrom(real_order[fi]))
			break;

	for (; ti < perfect_order.size(); ++ti)
		if (!t.hasTo(perfect_order[ti]))
			break;

	if (fi >= real_order.size() || ti >= perfect_order.size())
		return vector<Theory> ();

	return vector<Theory> (1, t.addRule(real_order[fi], perfect_order[ti]));
}
