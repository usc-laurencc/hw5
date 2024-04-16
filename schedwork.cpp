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
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t d, const size_t m, DailySchedule& sched, size_t currN, size_t currD, size_t prevK, std::map<Worker_T, size_t> shiftCt);

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
    // initializing default sched (a bunch of zeroes)
    for (size_t i = 0; i < avail.size(); i++) {
      std::vector<Worker_T> temp(dailyNeed, 0);
      sched.push_back(temp);
    }

    // initializing initial shift counts for each worker
    const size_t numWorkers = avail[0].size();
    std::map<Worker_T, size_t> shiftCt;
    for (size_t i = 0; i < numWorkers; i++) {
      shiftCt[i] = 0;
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, -1, shiftCt);
}

bool scheduleHelper(const AvailabilityMatrix& avail, const size_t d, const size_t m, DailySchedule& sched, size_t currN, size_t currD, size_t prevK, std::map<Worker_T, size_t> shiftCt)
{
  // if all days have been filled out
  if (currN == avail.size())
    return true;
  // if number of workers has been met
  else if (currD == d) 
    return scheduleHelper(avail, d, m, sched, currN+1, 0, -1, shiftCt);

  else {
    // iterating through workers
    for (size_t i = 0; i < avail[0].size(); i++) {
      // if worker is available on this day
      if (avail[currN][i] && shiftCt[i] < m && i != prevK) {
        sched[currN][currD] = i;
        shiftCt[i] += 1;
        
        // if program does not backtrack
        if (scheduleHelper(avail, d, m, sched, currN, currD+1, i, shiftCt))
          return true;
        // else, revert shift count
        shiftCt[i] -= 1;
      }
    }
  }
  return false;
}

