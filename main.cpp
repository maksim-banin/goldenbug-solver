#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>

#include "Theory.h"
#include "FreqExpert.h"
#include "DictExpert.h"
using namespace std;

/*
 * Perform breath-first search
 */
vector<Theory> solve(const string & riddle) {
	const size_t MAX_INVOCATIONS = 50;

	vector<Expert*> exps;
	exps.push_back(new FreqExpert());
	exps.push_back(new DictExpert());

	set<Theory> q, was;
	vector<Theory> ans;
	q.insert(Theory());
	for (size_t i = 0; i < MAX_INVOCATIONS && !q.empty(); ++i) {
		Theory curr = *(q.begin());
		was.insert(curr);
		q.erase(curr);

		if (curr.isFinished(riddle)) {
			cout << curr.apply(riddle) << endl;
			ans.push_back(curr);
		}

		cout << i << "(" << q.size() << ")\t " << curr.apply(riddle) << endl;

		for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it) {
			vector<Theory> vt = (*it)->derive(curr, riddle);

			for (size_t i = 0; i < vt.size(); ++i)
				if (was.find(vt[i]) == was.end())
					q.insert(vt[i]);
		}
	}

	for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it)
		delete *it;

	return ans;
}

/*
 * Counts amount of same letters on the same positions in both strings
 */
int similarity(const string& riddle, const string& guess) {
	int ans = 0;
	for (size_t i = 0; i < min(riddle.size(), guess.size()); ++i)
		if (riddle[i] == tolower(guess[i]))
			++ans;
	return ans;
}

/*
 * Amongst all the theories, report one with best guess rate
 */
void evaluate(vector<Theory> & theories, string & riddle) {
	string ans;
	for (size_t i = 0; i < theories.size(); ++i)
		if (similarity(riddle, theories[i].apply(riddle)) >= similarity(riddle, ans))
			ans = theories[i].apply(riddle);

	cout << "Best guess was: '" << ans << "'" << endl;
}

/*
 * Open tests file and run all tests
 */
int main() {
	ifstream fin("tests.txt");
	while (fin.good()) {
		string riddle;
		getline(fin, riddle);

		vector<Theory> theories = solve(riddle);
		evaluate(theories, riddle);
	}
}
