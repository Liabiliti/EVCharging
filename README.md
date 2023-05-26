# EVCharging
Description
First and foremost, this is a graph problem that revolves around EV charging stations. The graph is a map of the greater Sydney area and certain cities are displayed on the map. Those that are red have a charging and station and those that are black do not. The assignment is to provide a solution to some relevant problems associated with EV charging.

The end solution was able to solve the below problems:

  - List all the locations with charging stations in ascending order.
  - Take an input of a location and output the list of adjacent locations with charging stations.
  - Take an input of the current location and find the adjacent location with the lowest charging cost.
  - Take an input of the current location and output the nearest location with a charging station (excluding the current charging station). 
  - Find another location with the lowest total cost of traveling and charging (also excluding the current charging station). 
  - Find a path with the minimal charging cost and travel cost.
  - Find a path which allows the car to charge multiple times at different stations.

This project could be improved by using a more efficient algorithm for the cheapest path.

To run the file you can use a chosen IDE and compile via the IDE, additionally if the computer has a c++ compiler installed, then running these commands in the correct directory:

1. [compiler] EVChargingApp.cpp - o EVChargingApp
2. ./EVChargingApp
Will compile and run the program.
