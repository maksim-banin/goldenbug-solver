#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>

#include "Theory.h"
#include "FreqExpert.h"
#include "HipsterExpert.h"
#include "DictExpert.h"
using namespace std;

vector<Theory> solve(const string & riddle) {
	const size_t MAX_INVOCATIONS = 10;

	vector<Expert*> exps;
	exps.push_back(new FreqExpert());
	exps.push_back(new HipsterExpert());
	exps.push_back(new DictExpert());

	queue<Theory> q;
	vector<Theory> ans;
	q.push(Theory());
	for (size_t i = 0; i < MAX_INVOCATIONS && !q.empty(); ++i) {
		if (q.front()[riddle]) {
			cout << q.front()(riddle) << endl;
			ans.push_back(q.front());
		}

		for (vector<Expert*>::iterator it = exps.begin(); it != exps.end(); ++it) {
			vector<Theory> vt = (*it)->derive(q.front(), riddle);
			q.pop();
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

/*

*/
int main() {
	ifstream fin("input.txt");
	string riddle;
	getline(fin, riddle);

	vector <Theory> theories = solve(riddle);
	
    string ans;
	for(size_t i = 0; i < theories.size(); ++i)
		if (similarity(riddle, theories[i](riddle)) >= similarity(riddle, ans))
		    ans = theories[i](riddle);

	cout << "Best guess was: " << ans << endl;
}
