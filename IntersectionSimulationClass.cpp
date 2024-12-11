#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"
#include "constants.h"


void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname)
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() || randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() || timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

// Insert Arrival Event into EventList
void IntersectionSimulationClass::scheduleArrival(const string &travelDir)
{
  int eventTypeId;
  int eventTimeOccur;
  cout << "Time: " << currentTime << " Scheduled ";
  
  if(travelDir == NORTH_DIRECTION)
  {
    eventTypeId = EVENT_ARRIVE_NORTH;
    eventTimeOccur = currentTime + getPositiveNormal(northArrivalMean,
                                                     northArrivalStdDev);
  }
  else if(travelDir == EAST_DIRECTION)
  {
    eventTypeId = EVENT_ARRIVE_EAST;
    eventTimeOccur = currentTime + getPositiveNormal(eastArrivalMean,
                                                     eastArrivalStdDev);
  }
  else if(travelDir == WEST_DIRECTION)
  {
    eventTypeId = EVENT_ARRIVE_WEST;
    eventTimeOccur = currentTime + getPositiveNormal(westArrivalMean,
                                                     westArrivalStdDev);
  }
  else if(travelDir == SOUTH_DIRECTION)
  {
    eventTypeId = EVENT_ARRIVE_SOUTH;
    eventTimeOccur = currentTime + getPositiveNormal(southArrivalMean,
                                                     southArrivalStdDev);
  }

  EventClass insertedEvent(eventTimeOccur, eventTypeId);
  eventList.insertValue(insertedEvent);
  cout << insertedEvent << endl;
}

// Insert Light Changing Event
void IntersectionSimulationClass::scheduleLightChange()
{
  int eventTypeId;
  int eventTimeOccur;
  cout << "Time: " << currentTime << " Scheduled ";

  if(currentLight == LIGHT_GREEN_EW)
  {
    eventTypeId = EVENT_CHANGE_YELLOW_EW;
    eventTimeOccur = currentTime + eastWestGreenTime;
  }
  else if(currentLight == LIGHT_GREEN_NS)
  {
    eventTypeId = EVENT_CHANGE_YELLOW_NS;
    eventTimeOccur = currentTime + northSouthGreenTime;
  }
  else if(currentLight == LIGHT_YELLOW_EW)
  {
    eventTypeId = EVENT_CHANGE_GREEN_NS;
    eventTimeOccur = currentTime + eastWestYellowTime;
  }
  else if(currentLight == LIGHT_YELLOW_NS)
  {
    eventTypeId = EVENT_CHANGE_GREEN_EW;
    eventTimeOccur = currentTime + northSouthYellowTime;
  }

  EventClass insertedEvent(eventTimeOccur, eventTypeId);
  eventList.insertValue(insertedEvent);
  cout << insertedEvent << endl;
}

bool IntersectionSimulationClass::handleNextEvent()
{
  EventClass curEvent;
  if(!eventList.removeFront(curEvent))
  {
    return false;
  }

  currentTime = curEvent.getTimeOccurs();
  // If currentTime larger than declared stopTime, return false 
  if(currentTime > timeToStopSim)
  {
    cout << endl;
    cout << "Next event occurs AFTER the simulation end time (" << curEvent;
    cout << ")!" << endl;
    return false;
  }
  else
  {
    cout << endl;
    cout << "Handling " << curEvent << endl;
    
    // ARRIVING EVENT
    // Handling EastCar Arriving Event
    if(curEvent.getType() == EVENT_ARRIVE_EAST)
    {
      CarClass car(EAST_DIRECTION, currentTime);
      eastQueue.enqueue(car);
      cout << car << " arrives east-bound - queue length: " 
           << eastQueue.getNumElems() << endl;
      
      // Update maxQueueLength
      if(eastQueue.getNumElems() > maxEastQueueLength)
      {
        maxEastQueueLength = eastQueue.getNumElems();
      }
      // Insert next East-direction arrival event
      scheduleArrival(EAST_DIRECTION);
    }

    // Handling NorthCar Arriving Event
    else if(curEvent.getType() == EVENT_ARRIVE_NORTH)
    {
      CarClass car(NORTH_DIRECTION, currentTime);
      northQueue.enqueue(car);
      cout << car << " arrives north-bound - queue length: " 
           << northQueue.getNumElems() << endl;

      // Update maxQueueLength
      if(northQueue.getNumElems() > maxNorthQueueLength)
      {
        maxNorthQueueLength = northQueue.getNumElems();
      }
      // Insert next North-direction arrival event
      scheduleArrival(NORTH_DIRECTION);
    }

    // Handling SouthCar Arriving Event
    else if(curEvent.getType() == EVENT_ARRIVE_SOUTH)
    {
      CarClass car(SOUTH_DIRECTION, currentTime);
      southQueue.enqueue(car);
      cout << car << " arrives south-bound - queue length: " 
           << southQueue.getNumElems() << endl;

      // Update maxQueueLength
      if(southQueue.getNumElems() > maxSouthQueueLength)
      {
        maxSouthQueueLength = southQueue.getNumElems();
      }
      // Insert next South-direction arrival event
      scheduleArrival(SOUTH_DIRECTION);
    }

    // Handling WestCar Arriving Event
    else if(curEvent.getType() == EVENT_ARRIVE_WEST)
    {
      CarClass car(WEST_DIRECTION, currentTime);
      westQueue.enqueue(car);
      cout << car << " arrives west-bound - queue length: "
           << westQueue.getNumElems() << endl;
      
      // Update maxQueueLength
      if(westQueue.getNumElems() > maxWestQueueLength)
      {
        maxWestQueueLength = westQueue.getNumElems();
      }
      // Insert next West-direction arrival event
      scheduleArrival(WEST_DIRECTION);
    }
    
    // LIGHT_CHANGING EVENT

    // Handling EW_Green event (Process North-South Yellow event)
    else if(curEvent.getType() == EVENT_CHANGE_GREEN_EW)
    {
      int numCarNorth = MINIMUN_NUMBER_CAR, numCarSouth = MINIMUN_NUMBER_CAR;
      bool isAdvanceNorth = true, isAdvanceSouth = true;
      cout << "Advancing cars on north-south yellow" << endl;
      
      while(isAdvanceNorth)
      {
        // If there's no more car in queue, stop iterating
        if(northQueue.getNumElems() == MINIMUN_NUMBER_CAR)
        {
          cout << "  No north-bound cars waiting to advance on yellow" << endl;
          isAdvanceNorth = false;
        }
        else
        {
          if(numCarNorth < northSouthYellowTime)
          {
            // Decide whether the car should pass during yellow light
            if(getUniform(UNIFORM_MIN, UNIFORM_MAX)
               <= percentCarsAdvanceOnYellow)
            {
              CarClass northPassingCar;
              northQueue.dequeue(northPassingCar);
              cout << "  Next north-bound car will advance on yellow" << endl;
              cout << "  Car #" << northPassingCar.getId();
              cout << " advances north-bound" << endl;

              numCarNorth++;
              numTotalAdvancedNorth++;
            }
            else
            {
              cout << "  Next north-bound car will NOT advance"
                   << " on yellow" << endl;
              isAdvanceNorth = false; 
            }
          }
          else
          {
            isAdvanceNorth = false;
          }
        }
      }

      while(isAdvanceSouth)
      {
        // If there's no more car in queue, stop iterating
        if(southQueue.getNumElems() == MINIMUN_NUMBER_CAR)
        {
          cout << "  No south-bound cars waiting to advance on yellow" << endl;
          isAdvanceSouth = false;
        }
        else
        {
          if(numCarSouth < northSouthYellowTime)
          {
            // Decide whether the car should pass during yellow light
            if(getUniform(UNIFORM_MIN, UNIFORM_MAX) 
               <= percentCarsAdvanceOnYellow)
            {
              CarClass southPassingCar;
              southQueue.dequeue(southPassingCar);
              cout << "  Next south-bound car will advance on yellow" << endl;
              cout << "  Car #" << southPassingCar.getId();
              cout << " advances south-bound" << endl;

              numCarSouth++;
              numTotalAdvancedSouth++;
            }
            else
            {
              cout << "  Next south-bound car will NOT advance"
                   << " on yellow" << endl;
              isAdvanceSouth = false; 
            }
          }
          else
          {
            isAdvanceSouth = false;
          }
        }
      }

      cout << "North-bound cars advanced on yellow: " << numCarNorth
           << " Remaining queue: " << northQueue.getNumElems() << endl;
      cout << "South-bound cars advanced on yellow: " << numCarSouth
           << " Remaining queue: " << southQueue.getNumElems() << endl;

      currentLight = LIGHT_GREEN_EW;
      scheduleLightChange();
    }

    // Handling NS_Green event (Process East-West Yellow event)
    else if(curEvent.getType() == EVENT_CHANGE_GREEN_NS)
    {
      int numCarEast = MINIMUN_NUMBER_CAR, numCarWest = MINIMUN_NUMBER_CAR;
      bool isAdvanceEast = true, isAdvanceWest = true;
      cout << "Advancing cars on east-west yellow" << endl;

      while(isAdvanceEast)
      {
        // If there's no more car in queue, stop iterating
        if(eastQueue.getNumElems() == MINIMUN_NUMBER_CAR)
        {
          cout << "  No east-bound cars waiting to advance on yellow" << endl;
          isAdvanceEast = false;
        }
        else
        {
          if(numCarEast < eastWestYellowTime)
          {
            // Decide whether the car should pass during yellow light
            if(getUniform(UNIFORM_MIN, UNIFORM_MAX)
               <= percentCarsAdvanceOnYellow)
            {
              CarClass eastPassingCar;
              eastQueue.dequeue(eastPassingCar);
              cout << "  Next east-bound car will advance on yellow" << endl;
              cout << "  Car #" << eastPassingCar.getId();
              cout << " advances east-bound" << endl;

              numCarEast++;
              numTotalAdvancedEast++;
            }
            else
            {
              cout << "  Next east-bound car will NOT advance"
                   << " on yellow" << endl;
              isAdvanceEast = false;  
            }
          }
          else
          {
            isAdvanceEast = false;
          }
        }
      }

      while(isAdvanceWest)
      {
        // If there's no more car in queue, stop iterating
        if(westQueue.getNumElems() == MINIMUN_NUMBER_CAR)
        {
          cout << "  No west-bound cars waiting to advance on yellow" << endl;
          isAdvanceWest = false;
        }
        else
        {
          if(numCarWest < eastWestYellowTime)
          {
            // Decide whether the car should pass during yellow light
            if(getUniform(UNIFORM_MIN, UNIFORM_MAX)
               <= percentCarsAdvanceOnYellow)
            {
              CarClass westPassingCar;
              westQueue.dequeue(westPassingCar);
              cout << "  Next west-bound car will advance on yellow" << endl;
              cout << "  Car #" << westPassingCar.getId();
              cout << " advances west-bound" << endl;

              numCarWest++;
              numTotalAdvancedWest++;
            }
            else
            {
              cout << "  Next west-bound car will NOT advance"
                   << " on yellow" << endl;
              isAdvanceWest = false;  
            }
          }
          else
          {
            isAdvanceWest = false;
          }
        }
      }

      cout << "East-bound cars advanced on yellow: " << numCarEast
           << " Remaining queue: " << eastQueue.getNumElems() << endl;
      cout << "West-bound cars advanced on yellow: " << numCarWest
           << " Remaining queue: " << westQueue.getNumElems() << endl;

      currentLight = LIGHT_GREEN_NS;
      scheduleLightChange();
    }

    // Handling NS_Yellow event (Process North-South Green event)
    else if(curEvent.getType() == EVENT_CHANGE_YELLOW_NS)
    {
      int numCarNorth = MINIMUN_NUMBER_CAR, numCarSouth = MINIMUN_NUMBER_CAR;
      // Decalre the maximum number of car which can pass
      int maxCarToNorth = min(northQueue.getNumElems(), northSouthGreenTime);
      int maxCarToSouth = min(southQueue.getNumElems(), northSouthGreenTime);
      cout << "Advancing cars on north-south green" << endl;
      
      for(int i = 0; i < maxCarToNorth; i++)
      {
        CarClass northPassingCar;
        northQueue.dequeue(northPassingCar);
        numCarNorth += 1;
        cout << "  Car #" << northPassingCar.getId();
        cout << " advances north-bound" << endl;
      }

      for(int i = 0; i < maxCarToSouth; i++)
      {
        CarClass southPassingCar;
        southQueue.dequeue(southPassingCar);
        numCarSouth += 1;
        cout << "  Car #" << southPassingCar.getId();
        cout << " advances south-bound" << endl;
      }

      numTotalAdvancedNorth += numCarNorth;
      numTotalAdvancedSouth += numCarSouth;
      
      cout << "North-bound cars advanced on green: " << numCarNorth
           << " Remaining queue: " << northQueue.getNumElems() << endl;
      cout << "South-bound cars advanced on green: " << numCarSouth
           << " Remaining queue: " << southQueue.getNumElems() << endl;

      currentLight = LIGHT_YELLOW_NS;
      scheduleLightChange();
    }

    // Handling EW_Yellow event (Process East-West Green event)
    else if(curEvent.getType() == EVENT_CHANGE_YELLOW_EW)
    {
      int numCarEast = MINIMUN_NUMBER_CAR, numCarWest = MINIMUN_NUMBER_CAR;
      // Decalre the maximum number of car which can pass
      int maxCarToEast = min(eastQueue.getNumElems(), eastWestGreenTime);
      int maxCarToWest = min(westQueue.getNumElems(), eastWestGreenTime);
      cout << "Advancing cars on east-west green" << endl;
      
      for(int i = 0; i < maxCarToEast; i++)
      {
        CarClass eastPassingCar;
        eastQueue.dequeue(eastPassingCar);
        numCarEast += 1;
        cout << "  Car #" << eastPassingCar.getId();
        cout << " advances east-bound" << endl;
      }

      for(int i = 0; i < maxCarToWest; i++)
      {
        CarClass westPassingCar;
        westQueue.dequeue(westPassingCar);
        numCarWest += 1;
        cout << "  Car #" << westPassingCar.getId();
        cout << " advances west-bound" << endl;
      }

      numTotalAdvancedEast += numCarEast;
      numTotalAdvancedWest += numCarWest;
      
      cout << "East-bound cars advanced on green: " << numCarEast
           << " Remaining queue: " << eastQueue.getNumElems() << endl;
      cout << "West-bound cars advanced on green: " << numCarWest
           << " Remaining queue: " << westQueue.getNumElems() << endl;

      currentLight = LIGHT_YELLOW_EW;
      scheduleLightChange();
    }
    
    return true;
  }
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
