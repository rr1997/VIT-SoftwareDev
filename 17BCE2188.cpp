#include<bits/stdc++.h>

using namespace std;

class Game {
public:
	// TWO PLAYERS ARE PLAYING THE GAME
	int n = 5;
	string board[5][5];
	unordered_map<string, pair<int, int>> remaning1;
	unordered_map<string, pair<int, int>> remaning2;


	// 1. PAWN    // LEFT // RIGHT // FORWARD // BACKWORD
	// IF ANOTHER PLAYER EXISTS THEY PLAYER CANNOT MOVE THERE

	// TAKE INPUT OF PLAYER 1



	void takeInput() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				board[i][j] = "-";
			}
		}
		// PLAYER 1 INPUT
		string moves;
		cin >> moves;

		stringstream ss(moves);
		int i = 0;
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			string toAdd = "A-";
			toAdd += substr;
			remaning1[substr] = make_pair(4, i);
			board[4][i++] = toAdd;
		}

		// PLAYER 2 INPUT
		cin >> moves;

		stringstream ss1(moves);
		i = 0;
		while (ss1.good()) {
			string substr;
			getline(ss1, substr, ',');
			string toAdd = "B-";
			toAdd += substr;
			remaning2[substr] = make_pair(0, i);
			board[0][i++] = toAdd;
		}

		// PRINT THE BOARD
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		return;
	}



	bool stringFormat(string s) {
		if (s.size() != 4) return false;
		if (s[0] != 'P') return false;
		if (s[s.size() - 2] != ':') return false;
		char direction = s[s.size() - 1];
		bool b = (direction == 'F' || direction == 'B' || direction == 'L' || direction == 'R');
		if (!b) return false;
		return true;
	}


	void GamePlay() {


		int c = 0;



		while (remaning1.size() != 1 || remaning2.size() != 1) {

			if (c == 0) {
				// PLAYER 1 CHANCE
				cout << "Player-1:";
				string s;
				cin >> s;

				// STRING IS VALID OR NOT

				bool b = stringFormat(s);
				if (b == false) {
					cout << "Invalid input format (Not in format of x:y" << endl;
					cout << "Choose Another Move" << endl;
					c = 0;
					continue;
				}


				string player = "";
				player += s[0];
				player += s[1];

				char move = s[s.size() - 1];

				// CHARACHTER DOEST EXIST
				if (remaning1.count(player) == 0) {
					cout << "Character doesn't exist, Invalid Move" << endl;
					cout << "Choose Another Move" << endl;
					c = 0;
					continue;
				}

				// OUT OF BOARD
				pair<int, int> idx = remaning1[player];
				int i = idx.first;
				int j = idx.second;
				//cout << player << " " << i << " " << j << endl;

				// CALCULATE THE NEW INDEX
				if (move == 'F') i--;
				else if (move == 'B') i++;
				else if (move == 'R') j++;
				else if (move == 'L') j--;

				if (i < 0 || j < 0 || i >= 5 || j >= 5) {
					cout << "Out Of Board" << endl;
					c = 0;
					continue;
				}


				// OWN CHARACHTER STANDING THERE
				if (board[i][j] != "-") {
					// SOMEONE IS THERE
					// SAME TEAM
					string temp = board[i][j];
					if (temp[0] == 'A') {
						cout << "Own character standing at the target position" << endl;
						c = 0;
						continue;
					}


					// OPPOSITE TEAM
					string t1 = "A-";
					t1 += player;
					board[i][j] = t1;
					board[idx.first][idx.second] = "-";
					string toKill = "";
					toKill += temp[2];
					toKill += temp[3];
					remaning2.erase(toKill);
					remaning1[player] = make_pair(i, j);
					string toAdd = "A-";
					toAdd += player;
					c = 1;
				}
				else {
					// NO ONE IS THERE SIMPLY MOVE
					remaning1[player] = make_pair(i, j);
					board[idx.first][idx.second] = '-';
					string toAdd = "A-";
					toAdd += player;
					board[i][j] = toAdd;
					c = 1;
				}
			}

			else {
				// PLAYER 2 CHANCE
				cout << "Player-2:";
				string s;
				cin >> s;

				// STRING IS VALID OR NOT

				bool b = stringFormat(s);
				if (b == false) {
					cout << "Invalid input format (Not in format of x:y" << endl;
					cout << "Choose Another Move" << endl;
					c = 1;
					continue;
				}


				string player = "";
				player += s[0];
				player += s[1];

				char move = s[s.size() - 1];

				// CHARACHTER DOEST EXIST
				if (remaning2.count(player) == 0) {
					cout << "Character doesn't exist, Invalid Move" << endl;
					cout << "Choose Another Move" << endl;
					c = 1;
					continue;
				}

				// OUT OF BOARD
				pair<int, int> idx = remaning2[player];
				int i = idx.first;
				int j = idx.second;


				// CALCULATE THE NEW INDEX
				if (move == 'F') i++;
				else if (move == 'B') i--;
				else if (move == 'R') j--;
				else if (move == 'L') j++;

				if (i < 0 || j < 0 || i >= 5 || j >= 5) {
					cout << "Out Of Board" << endl;
					c = 1;
					continue;
				}


				// OWN CHARACHTER STANDING THERE
				if (board[i][j] != "-") {
					// SOMEONE IS THERE
					// SAME TEAM
					string temp = board[i][j];
					if (temp[0] == 'B') {
						cout << "Own character standing at the target position" << endl;
						c = 1;
						continue;
					}


					// OPPOSITE TEAM
					string t1 = "B-";
					t1 += player;
					board[i][j] = t1;
					board[idx.first][idx.second] = "-";
					string toKill = "";
					toKill += temp[2];
					toKill += temp[3];
					remaning1.erase(toKill);
					remaning2[player] = make_pair(i, j);
					string toAdd = "B-";
					toAdd += player;
					c = 0;

				}
				else {
					// NO ONE IS THERE SIMPLY MOVE
					remaning2[player] = make_pair(i, j);
					board[idx.first][idx.second] = '-';
					string toAdd = "B-";
					toAdd += player;
					board[i][j] = toAdd;
					c = 0;

				}
			}

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					cout << board[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}



};


int main() {

	Game g;
	g.takeInput();
	g.GamePlay();

}