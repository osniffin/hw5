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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& results, size_t idx);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // in - word pattern with fixed letters and blanks
    // floating - "yellow" letters that appear somewhere
    // dict - dict-eng.txt
    // things to keep track of: index, 
  std::set<std::string> results; 
  wordleHelper(in, floating, dict, results,0);
  return results;
}


// Define any helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& results, size_t idx)
{
  if(idx == in.size())
  {
    if(floating.empty() && dict.find(in)!= dict.end())
    {
      results.insert(in);
    }
    return;
  }
  if(in[idx]!= '-')
  {
    wordleHelper(in,floating, dict, results, idx+1);

  }else{ //index reached is - (blank)
    // use a floating letter
    // use any other letter a-z
    //keep track of floating letters: only used once
    //try a-z
    for(char i='a';i<='z';i++){
      std::string tempIn = in;
      std::string newFloating = floating;

      if(floating.find(i)!=std::string::npos){//Case 1: if 'i' is in floating letters
        tempIn[idx]=i; //add the floating letter into the blank spot
        newFloating.erase(floating.find(i),1); //erase the used floating value from the temp floating list
        wordleHelper(tempIn,newFloating, dict, results, idx+1); //recurse

      }else{// Case 2: if 'i' is NOT in floating
        //if there are more dashes left than floating letters
        //count blanks left 
        size_t blanksLeft =0;
        for (size_t j = 0; j < tempIn.size(); j++){
          if(in[j] == '-') blanksLeft++;
        }
        //compare blanks to the new floating 
        if(blanksLeft>newFloating.size()){ //if there are more blanks than floating letters remaining 
          tempIn[idx]=i; //add the letter into the blank spot
          wordleHelper(tempIn,newFloating, dict, results, idx+1); //recurse 
        }
      }
    }
  }
}

