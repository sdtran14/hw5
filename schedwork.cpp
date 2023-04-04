#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool bt(const AvailabilityMatrix& avail, DailySchedule& cSched, vector<size_t> cMaxes, int idx, const size_t dailyNeed);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		vector<size_t> maxes(avail[0].size(), maxShifts);
    return bt(avail, sched, maxes, 0, dailyNeed);
    



}

bool bt(const AvailabilityMatrix& avail, DailySchedule& cSched, vector<size_t> cMaxes, int idx, const size_t dailyNeed)
{
	/*
		if(idx > 0) 
		{
			for(int i = 0; i < (signed)cSched[0].size(); i++)
			{
				
				if(cMaxes[cSched[idx-1][i]]-- <= 0) {
					return false;
				}	
			}
		}
		*/
		/*
		cout<<"CMAXES:"<<endl;
				for(int p : cMaxes) cout<<p<<", ";
					cout<<endl;
		*/
		if(idx >= (signed)avail.size()) return true;
    vector<int> availIndexes;
    for(int i = 0; i<(signed)avail[0].size(); i++) 
    {
        if(avail[idx][i]) availIndexes.push_back(i);
    }
		/*
    cout<<"avail at idx:"<<idx<<endl;
					for(int p : availIndexes) cout<<p<<", ";
					cout<<endl;
		*/
    vector<int> s;
		vector<Worker_T> cur;
		s.push_back(-1);
		
		while(!s.empty()) 
		{
			int top = s.back();
			s.pop_back();
			if(top!=-1) 
			{
				cMaxes[availIndexes[top]]++;
				cur.pop_back();
			}
			for(Worker_T i = top+1; i<availIndexes.size(); i++) 
			{
				if(cMaxes[availIndexes[i]] > 0) 
				{
				cMaxes[availIndexes[i]]--;
				s.push_back(i);
				cur.push_back(availIndexes[i]);
				if(s.size() >= dailyNeed) 
				{
					
					
					cSched.push_back(cur);
					/*
					if(idx == 5 && s[0] == 2 && s[1] == 4 && s[2] == 6) 
					//&& cSched[5][0] == 2 //&& cSched[5][1] == 5 
					//&& cSched[5][2] == 6)
					{
						cout<<"CurrLayer:"<<idx<<endl;
					for(int p : s) cout<<p<<", ";
					cout<<endl;
					cout<<"i:"<<i<<"top, "<<top<<endl;
					}
					*/
					
          if(bt(avail, cSched, cMaxes, idx+1, dailyNeed)) return true;
				
					
					
          cSched.pop_back();
					s.pop_back();
					cur.pop_back();
					cMaxes[availIndexes[i]]++;
				}
				}
			}
			
		}
		return false;
}


