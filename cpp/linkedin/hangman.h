#pragma once

#include "henry.h"
#include <random>

namespace _hangman {

// https://gist.github.com/saltavenger/3939185 single machine, single user
// version
vector<string> words = {"cat", "tree", "swing", "around", "scientist"};

string chooseWord() { return words[rand() % words.size()]; }

void play() {
  int count = 0;
  while (count < 5) {
  }
}

} // namespace _hangman
