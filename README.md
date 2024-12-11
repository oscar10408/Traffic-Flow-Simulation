# Traffic Flow Simulation Project

## Overview
For this project, I will be provided with a significant amount of code to start with. This is very different from previous projects where I might be given only function prototypes, and I would essentially be starting from scratch. The provided classes and code will allow me to avoid spending too much time on high-level design, but I will need to spend some time understanding the provided code and how the code I will be adding will work with it.

In general, this project should be less time-consuming compared to a "start from scratch" project, and will allow me to focus on the simulation aspects instead of spending too much time on file reading, error checking, or determining which attributes my `EventClass` should have. Since the end of the semester is quickly approaching, this approach provides a good opportunity to gain experience with an event-driven simulation, as well as working with someone else’s code—just as would be the case in a team-based environment.

This project involves the implementation of an event-driven simulation of traffic flow through a 4-way intersection managed by a traffic light. The simulation will include cars arriving at the intersection from all four directions, and the traffic light changing state throughout the simulation. At the end of the simulation, I will output some minimal statistics about the traffic flow.


# Traffic Flow Simulation Project

## Detailed Description

### Phase 1: Templated Data Structures
In **Phase 1**, I will modify some of the data structures developed in Project 4 to be **templated**. This means that these data structures will be associated with a generic data type using C++ templates, allowing them to store a variety of data types instead of just integers. Specifically, the following classes must be updated:
- `SortedListClass`
- `FIFOQueueClass`

Note that there is no need to modify or include the `LIFOStackClass` in this project, so it will not be required to be templated or included in the submission.

The goal is to ensure that these templated data structure classes match the design, names, and functional interface as developed in Project 4. I will not add new member functions, introduce new member variables, or alter the number or meaning of function parameters. The primary difference between the Project 4 and Project 5 versions of these classes will be the introduction of templates to support different data types.

Phase 1 involves minimal new code development, primarily focusing on modifying the data structures to be templated and developing test cases to ensure the updated data structures work with various data types. Exhaustive testing will be performed in this phase to ensure that the modified data structures work as expected.

### Phase 2: Event-Driven Simulation
Once the templated data structures are implemented and tested, I will proceed to **Phase 2**, which involves developing an event-driven simulation of traffic flow through a 4-way intersection controlled by a functioning traffic light. 

The core components of the simulation are:
1. **Event Class**: This will define the events (such as cars arriving at the intersection and traffic light state changes) in the simulation.
2. **Event List**: The events will be stored in a `SortedListClass`, referred to as the "event list". This list will only contain events that are scheduled to occur in the future; events that have already been handled will not be stored.
   
The simulation will proceed by advancing through "time tics", which represent a generic unit of time. The definition of a "time tic" is unit-less, allowing for flexible scaling of the simulation. For example, a "time tic" could represent 1 second, 1 minute, or 1 millisecond, depending on the user’s preference.

#### Concept of Time Tics
A **time tic** represents a unit-less measure of time, making the simulation scaleable. When a simulation event occurs in "3 time tics", it means that the event happens after 3 advancements of time, but the exact unit of time (seconds, milliseconds, etc.) can vary depending on the user's settings.

### Simulation Parameters and Input File Format
The simulation will require 15 control parameters to function. These parameters will be read from a text file, whose name will be provided to the program via a command line argument. Below are the control parameters:

1. **Random Number Generator Seed**: A non-negative integer value to seed the random number generator for selecting a pseudo-random sequence in the simulation.
2. **Simulation End Time**: A positive integer indicating the time at which the simulation should end. Events occurring after this time will not be handled.
3. **East-West Green and Yellow Times**: Two positive integers indicating the duration of green and yellow lights for east-west traffic flow.
4. **North-South Green and Yellow Times**: Two positive integers indicating the duration of green and yellow lights for north-south traffic flow.
5. **Arrival Rate for East-Bound Cars**: Mean and standard deviation for the arrival rate of cars traveling east.
6. **Arrival Rate for West-Bound Cars**: Mean and standard deviation for the arrival rate of cars traveling west.
7. **Arrival Rate for North-Bound Cars**: Mean and standard deviation for the arrival rate of cars traveling north.
8. **Arrival Rate for South-Bound Cars**: Mean and standard deviation for the arrival rate of cars traveling south.
9. **Percentage of Drivers Advancing Through Yellow Light**: An integer between 0 and 100 indicating the percentage of drivers who will advance through a yellow light.

The input file format will be a simple ASCII text file where these 15 values are provided in a whitespace-delimited format. The parameters should be in the exact order listed above.

#### Example Input File
An example input file containing the 15 simulation control parameters might look like this:<br />
12345<br />
1000<br /> 
10 2<br /> 
17 3<br /> 
3 1.04<br /> 
15 2.7<br /> 
7.25 0<br /> 
12.5 3.3<br /> 
65<br />

