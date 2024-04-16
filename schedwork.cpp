#ifndef RECCHECK
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool scheduleHelper(size_t currDay, const AvailabilityMatrix& avail,
                    const size_t dailyNeed, const size_t maxShifts,
                    DailySchedule& sched,
                    map<Worker_T, size_t>& shifts);

bool testCurrentDay(size_t currDay, const AvailabilityMatrix& avail,
                 const size_t dailyNeed, const size_t maxShifts,
                 DailySchedule& sched, map<Worker_T, size_t>& shifts,
                 vector<Worker_T>& currentWorkers, size_t startID,
                 size_t workersAdded);
// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed,
              const size_t maxShifts, DailySchedule& sched) {
  if (avail.size() == 0U) {
    return false;
  }
  sched.clear();
  sched.resize(avail.size());

  map<Worker_T, size_t> shifts;

  for (size_t worker = 0; worker < avail[0].size(); ++worker) {
    shifts[worker] = 0;
  }

  return scheduleHelper(0, avail, dailyNeed, maxShifts, sched, shifts);

  // Add your code below
}

bool scheduleHelper(size_t currDay, const AvailabilityMatrix& avail,
                    const size_t dailyNeed, const size_t maxShifts,
                    DailySchedule& sched,
                    map<Worker_T, size_t>& shifts) {
  if (currDay ==
      avail.size()) {  // base case: all days have been successfully scheduled
    return true;
  }

  vector<Worker_T> currentWorkers;

  for (size_t worker = 0; worker < avail[currDay].size(); ++worker) {
    if (avail[currDay][worker]) {
      currentWorkers.push_back(worker);
    }
  }
  // try to find valid combo of workers for today
  return testCurrentDay(currDay, avail, dailyNeed, maxShifts, sched, shifts,
                     currentWorkers, 0, 0);
}

bool testCurrentDay(size_t currDay, const AvailabilityMatrix& avail,
                 const size_t dailyNeed, const size_t maxShifts,
                 DailySchedule& sched, map<Worker_T, size_t>& shifts,
                 vector<Worker_T>& currentWorkers, size_t startID,
                 size_t workersAdded) {
  if (workersAdded == dailyNeed) {  // base case: enough workers added for today
    return scheduleHelper(currDay + 1, avail, dailyNeed, maxShifts, sched,
                     shifts);
  }

  for (size_t i = startID; i < currentWorkers.size(); ++i) {
    Worker_T worker = currentWorkers[i];
    // add worker if available and still under max shifts
    if (avail[currDay][worker] && shifts[worker] < maxShifts) {
      sched[currDay].push_back(worker);
      shifts[worker]++;
      if (testCurrentDay(currDay, avail, dailyNeed, maxShifts, sched,
                      shifts, currentWorkers, i + 1,
                      workersAdded + 1)) {
        return true;
      }
      // backtrack
      shifts[worker]--;
      sched[currDay].pop_back();
    }
  }

  return false;  // no valid schedule found for this day
}