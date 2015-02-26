#include <iostream>
#include <fstream>
#include <string>

#include "GameState.h"

using namespace std;

const int amount = 10;

void updateScores() {
  string tempname = gameState.playerName;
  int tempscore = gameState.score;

  string filename;

  switch (gameState.gameMode) {
  case GAME_STANDARD:
    filename = "classic.txt";
    break;
  case GAME_SURVIVAL:
    filename = "survival.txt";
    break;
  case GAME_TITANIC:
    filename = "titanic.txt";
    break;
  }
  string line;

  string names[amount];
  int scores[amount];

  ifstream myfile(filename);

  if (myfile.is_open()) {
    int i = 0; // main loop counter
    int k = 0; // counter of names array
    int l = 0; // counter of scores
    while (getline(myfile, line)) {
      if (i % 2 == 0) {
        names[k] = line;
        k++;
      } else {
        scores[l] = stoi(line);
        l++;
      }

      i++;
    }
    myfile.close();
  } else { 
    cout << "Unable to open file" << endl;
  };

  int min = scores[0];
  string strmin = names[0];
  int arraypos = 0;
  for (int i = 1; i < amount; i++) {
    if (scores[i] < min) {
      min = scores[i];
      strmin = names[i];
      arraypos = i;
    }
  }

  if (min < tempscore) {
    scores[arraypos] = tempscore;
    names[arraypos] = tempname;
  }

  int a, b, temp;
  string btemp;
  for (a = 0; a < amount; a++) {
    for (b = 0; b < amount - 1 - a; b++) {
      if (scores[b] < scores[b + 1]) {
        temp = scores[b + 1];
        btemp = names[b + 1];

        scores[b + 1] = scores[b];
        names[b + 1] = names[b];

        scores[b] = temp;
        names[b] = btemp;
      }
    }
  }

  //re-write the files.

  ofstream newfile(filename);
  for (int i = 0; i < amount; i++) {
    newfile << names[i] << endl;
    newfile << scores[i] << endl;
  }
  myfile.close();
}
