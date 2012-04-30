#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Theory.h"
#include "FreqExpert.h"
#include "DictExpert.h"
using namespace std;

/*
 * Perform depth-first
 */
const size_t MAX_INVOCATIONS = 128;
size_t invocations_counter = 0;

set<Theory> was;
vector<Expert*> exps;
vector<Theory> valids;

vector<Theory> dfs(const Theory & curr, const string& riddle) {
	++invocations_counter;
	if (invocations_counter > MAX_INVOCATIONS)
		return vector<Theory> ();

	vector<Theory> ans;
	was.insert(curr);

	if (curr.isFinished(riddle)) {
		valids.push_back(curr);
		//		cout <<  curr.apply(riddle) << endl;
	}
	cout << ".";

	for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it) {
		vector<Theory> vt = (*it)->derive(curr, riddle);

		for (size_t i = 0; i < vt.size(); ++i)
			if (was.find(vt[i]) == was.end()) {
				was.insert(vt[i]);
				dfs(vt[i], riddle);
			}
	}
	return ans;
}

vector<Theory> solve(const string & riddle) {
	vector<Theory> ans = dfs(Theory(), riddle);
	was.clear();
	invocations_counter = 0;
	return ans;
}

/*
 * Counts amount of same letters on the same positions in both strings
 */
int similarity(const string& riddle, const string& guess) {
	int ans = 0;
	//	cout << "Guess is: '"<< guess << "'\n";
	for (size_t i = 0; i < min(riddle.size(), guess.size()); ++i)
		if (riddle[i] == tolower(guess[i]))
			++ans;
	return ans;
}

/*
 * Amongst all the theories, report one with best guess rate
 */
double evaluate(vector<Theory> & theories, const string & riddle) {
	string ans;
	for (size_t i = 0; i < theories.size(); ++i)
		if (similarity(riddle, theories[i].apply(riddle)) >= similarity(riddle, ans))
			ans = theories[i].apply(riddle);

	cout << "Best guess was: '" << ans << "'" << endl;
	return (double) similarity(riddle, ans) / riddle.size();
}

/*
 * Open tests file and run all tests
 */
int main() {
	ifstream fin("tests.txt");
	exps.push_back(new DictExpert());
	exps.push_back(new FreqExpert());

	while (fin.good()) {
		string riddle;
		getline(fin, riddle);
		cout << "Cyphertext is: '" << riddle << "'\n";
		cout << "Solving";
		solve(riddle);
		cout << endl;
		cout << "Guess quality is: " << evaluate(valids, riddle) << "\n";
		valids.clear();
	}
}
