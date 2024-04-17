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
int wordleHelper(std::string word, const std::string& in,
                 const std::string& floating, const std::set<std::string>& dict,
                 std::set<std::string>& answers, size_t unknownLettersCtr,
                 size_t index);
                 
// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating,
                             const std::set<std::string>& dict) {
  // Add your code here
  std::set<std::string> answers;
  int unknownLettersCtr = 0;
  for (size_t i = 0; i < in.size(); i++) {
    if (in[i] == '-') unknownLettersCtr++;
  }
  wordleHelper("", in, floating, dict, answers, 5, 0);
  return answers;
}

// Define any helper functions here

int wordleHelper(std::string word, const std::string& in,
                 const std::string& floating, const std::set<std::string>& dict,
                 std::set<std::string>& answers, size_t unknownLettersCtr,
                 size_t index) {
  std::string currFloating = floating;
  std::string currentWord = word;

  if (index == in.length()) {
    std::set<std::string>::iterator it = dict.find(word);
    if (it == dict.end()) return 0;
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
      if (unknownLettersCtr > currFloating.length()) {
        for (size_t i = 0; i < 26; i++) {
          char c = i + 97;
          currFloating = floating;
          size_t isFloating = currFloating.find(c);
          if (currFloating.find(c) != std::string::npos) {
            currFloating.erase(currFloating.begin() + isFloating);
          }
          wordleHelper(word + c, in, currFloating, dict, answers,
                       unknownLettersCtr - 1, index + 1);
        }
      } else {
        for (unsigned int i = 0; i < currFloating.length(); i++) {
          currFloating = currFloating;

          char a = currFloating[i];
          currFloating.erase(currFloating.begin() + i);

          wordleHelper(word + a, in, currFloating, dict, answers,
                       unknownLettersCtr - 1, index + 1);
        }
      }
    } else {
      wordleHelper(word + in[index], in, currFloating, dict, answers,
                   unknownLettersCtr, index + 1);
    }
  }
  return 0;
}
