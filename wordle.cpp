#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void getWords(std::set<std::string>& words, std::string in, std::string floating, int len);
int numHyphens(const std::string& in);
std::set<std::string> validWords(std::set<std::string>& words, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> words;
    getWords(words, in, floating, 0);
    return validWords(words, dict);
}

// Define any helper functions here
void getWords(std::set<std::string>& words, std::string in, std::string floating, int len) 
{
    // if the word is finished
    if (len == in.size() && floating == "")
        words.insert(in);
    // if all letters have been filled but floating requirement has not been met
    else if (len == in.size())
      return;
    // if letter is fixed
    else if (in[len] != '-')
        getWords(words, in, floating, len+1);
    
    else {
      // if there is only room left for the floating letters, search floating letters only
        std::string alphabet;
        if (numHyphens(in) == floating.size()) 
          alphabet = floating;
        else
          alphabet = "abcdefghijklmnopqrstuvwxyz";

        for (int i = 0; i < alphabet.size(); i++) {
            in[len] = alphabet[i];
            int floatIdx = floating.find(alphabet[i]);

            // checking off floating letters
            if (floatIdx != -1) {
                std::string newFloating(floating);
                newFloating.erase(newFloating.begin() + floatIdx);
                getWords(words, in, newFloating, len+1);
            }
            else 
                getWords(words, in, floating, len+1);
        }
    }
}

int numHyphens(const std::string& in)
{
  int num = 0;
  for (int i = 0; i < in.size(); i++) {
    if (in[i] == '-')
      num++;
  }
  return num;
}

std::set<std::string> validWords(std::set<std::string>& words, const std::set<std::string>& dict)
{
    std::set<std::string> validWords;
    for (std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
        if (dict.find(*it) != dict.end())
            validWords.insert(*it);
    }
    return validWords;
}