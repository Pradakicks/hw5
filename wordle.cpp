#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "dict-eng.h"
#include "wordle.h"
using namespace std;

// Add prototypes of helper functions here

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating,
                             const std::set<std::string>& dict) {
  // Add your code here
  std::set<std::string> answers;
  wordleHelper("", in, floating, dict, answers);
  return answers;
}

// Define any helper functions here

int wordleHelper(std::string word, const std::string& in,
                 const std::string& floating, const std::set<std::string>& dict,
                 std::set<std::string>& answers) {
  if (word.length() == in.length()) {
    // Check if word is valid then print
    std::set<std::string>::iterator it = dict.find(word);
    if (it == dict.end()) return 0;

    std::string currentWord = word;
    for (size_t i = 0; i < floating.length(); i++) {
      size_t pos = currentWord.find(floating[i]);
      if (pos == string::npos) {
        return 0;
      } else {
        currentWord[pos] = '-';
      }
    }
    answers.insert(word);

  } else {
    if (in[word.length()] == '-') {
      for (size_t i = 0; i < 26; i++) {
        std::string currentWord = word;
        currentWord.push_back(97 + i);
        wordleHelper(currentWord, in, floating, dict, answers);
      }
    } else {
      word.push_back(in[word.length()]);
      wordleHelper(word, in, floating, dict, answers);
    }
  }
  return 0;
}
