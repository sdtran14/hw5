#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"

using namespace std;


// Add prototypes of helper functions here
void wordleh(
		std::string in,
		std::string floating, 
		const std::set<std::string>& dict, 
		int idx, 
		std::set<std::string>& res
		,
		int numBlanks);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
		std::set<std::string> res;
		int numB = 0;
		for(int i = 0; i<(signed)in.size(); i++) 
		{
			if(in[i] == '-') numB++;
		}
		wordleh(in, floating, dict, 0, res, numB);
		return res;
} 
    // Add your code here
    

void wordleh(std::string in, std::string floating, const std::set<std::string>& dict, int idx, std::set<std::string>& res, int numBlanks)
{
	if(idx == (signed)in.size())
	{
		if(dict.find(in) != dict.end()) 
		{
			res.insert(in);
		}
	}
	else if(in[idx] != '-') wordleh(in, floating, dict, idx+1,res, numBlanks);
	else 
	{
		for(int i = 0; i< 26; i++) 
		{
			char c = 'a' + i;
			auto f = floating.find(c);
			if (f != string::npos) 
			{
				in[idx] = c;
				//cout<<c<<", "<<floating<<endl;
				floating.erase(f, 1);
				//cout<<floating<<endl;
				wordleh(in, floating, dict, idx+1,res, numBlanks-1);
				floating.push_back(c);

			} else if(floating.size() < (unsigned)numBlanks) 
			{
				in[idx] = c;
				wordleh(in, floating, dict, idx+1,res, numBlanks-1);
			}	
		}
	}
}
// Define any helper functions here
