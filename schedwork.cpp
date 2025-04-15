#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool fillScheduleBacktrack(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftsPerWorker, size_t day, size_t slot);
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
        
    size_t n = avail.size();    //number of days
    size_t k = avail[0].size(); //number of workers 

    sched.resize(n);
    sched = DailySchedule(n,std::vector<Worker_T>());
    std::vector<size_t> shiftsPerWorker(k,0);

    return fillScheduleBacktrack(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, 0, 0);

}

bool fillScheduleBacktrack(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<size_t>& shiftsPerWorker, size_t day, size_t slot)
{
    size_t n = avail.size();    //number of days
    size_t k = avail[0].size(); //number of workers 

    if(day == n) return true; //Base Case: all days scheduled

    if(slot==dailyNeed) //Case 1: all slots are filled for given day --> move to next day 
    {
        return fillScheduleBacktrack(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, day + 1, 0);
    }
    //test every possible worker to see if they can work the given slot on the given day 
    for(size_t i=0; i<k; i++)
    {
        //check if worker is available 
        //& worker not scheduled for this day 
        //& worker doesn't have maxShifts
        std::vector<Worker_T>::iterator it = std::find(sched[day].begin(), sched[day].end(),i);
        if(avail[day][i] && shiftsPerWorker[i]<maxShifts && it == sched[day].end() ){
            sched[day].push_back(i); // add the worker to that day
            shiftsPerWorker[i]++; //add 1 shift to given workers number of shifts
            //recurse to fill the next slot 
            if(fillScheduleBacktrack(avail, dailyNeed, maxShifts, sched, shiftsPerWorker, day, slot+1))
            {
                return true; //If it works, continue to the next slot
            }
            //Backtrack if it doesnt work - undo 
            sched[day].pop_back();
            shiftsPerWorker[i]--;
        
        }

    }

    return false;
}
