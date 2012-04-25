#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>

#include "Theory.h"
#include "FreqExpert.h"
#include "DictExpert.h"
using namespace std;

vector<Theory> solve(const string & riddle) {
	const size_t MAX_INVOCATIONS = 50;

	vector<Expert*> exps;
	exps.push_back(new FreqExpert());
	exps.push_back(new DictExpert());

	queue<Theory> q;
	vector<Theory> ans;
	q.push(Theory());
	for (size_t i = 0; i < MAX_INVOCATIONS && !q.empty(); ++i) {
		Theory curr = q.front();
		q.pop();

		if (curr[riddle]) {
			cout << curr(riddle) << endl;
			ans.push_back(curr);
		}

		cout << i << "(" << q.size() << ")\t " << curr(riddle) << endl;

		for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it) {
			vector<Theory> vt = (*it)->derive(curr, riddle);
			//cerr << "vt.stize() == " << vt.size() << endl;
			for (size_t i = 0; i < vt.size(); ++i)
				q.push(vt[i]);
		}
	}

	for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it)
		delete *it;

	return ans;
}

int similarity(const string& riddle, const string& guess) {
	int ans = 0;
	for (size_t i = 0; i < min(riddle.size(), guess.size()); ++i)
		if (riddle[i] == tolower(guess[i]))
			++ans;
	return ans;
}

void evaluate(vector<Theory> & theories, string & riddle) {
	string ans;
	for (size_t i = 0; i < theories.size(); ++i)
		if (similarity(riddle, theories[i](riddle)) >= similarity(riddle, ans))
			ans = theories[i](riddle);

	cout << "Best guess was: '" << ans << "'" << endl;
}

/*

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
