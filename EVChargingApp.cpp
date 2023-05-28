#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <iomanip>
#include <unordered_set>
#include <limits>
#include <unistd.h>

using namespace std;

#include "Location.h"
#include "WeightedGraph.h"
#include "EVCharging.h"

int main()
{
	EVCharging charging;
	string city, destinationCity;
	int task, chargingAmount;
	double weight, chargingCost;
	while(1)
	{
		cout << "\nChoose a task to run:\n"
			<< "1. Print location information\n"
			<< "2. Print adjacency matrix\n"
			<< "3. Task 3 - List all charging stations in ascending order\n"
			<< "4. Task 4 - List adjacent charging stations\n"
			<< "5. Task 5 - Find the adjacent charging stations\n"
			<< "6. Task 6 - Find the nearest charging station\n"
			<< "7. Task 7 - Find the cheapest charging station other than the current location\n"
			<< "8. Task 8 - Find the cheapest charging station between origin and destination (single charging)\n"
			<< "9. Task 9 - Find the best way of charging (multiple charging)\n"
			<< "10. Task 10 - Add vertex\n"
			<< "11. Task 11 - Delete vertex\n"
			<< "0. Quit\n";
		cin >> task;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (task)
		{
			case 1:
				charging.printLocations();
				break;
			case 2:
				charging.printAdjacencyMatrix();
				break;
			case 3:
				charging.leastExpensiveChargingStations();
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 11:
				cout << "Input a location:\n";
				getline(cin, city);
				if (charging.cityExists(city))
				{
					if(task == 4)
						charging.adjacentLocations(city);
					if(task == 5)
						charging.cheapestAdjacentCity(city);
					if(task == 6)
						charging.closestCity(city);
					if(task == 7)
						charging.cheapestLocation(city); 
					if(task == 11)
						charging.deleteLocation(city);

				}
				else
				{
					cout << "Not a city!\n";
				}
				break;
			case 8:
			case 9:
				cout << "Input starting location:\n";
				getline(cin, city);
				cout << "Input destination location:\n";
				getline(cin, destinationCity);
				if (charging.cityExists(city) && charging.cityExists(destinationCity))
				{
					cout << "Input kWh to be charged:\n";
					cin >> chargingAmount;
					if((chargingAmount > 0) && (chargingAmount <= 50))
					{
						if(task == 8)
						{
							charging.cheapestPath(city, destinationCity, chargingAmount);
						}
						if(task == 9)
						{
							charging.cheapestPathFree(city, destinationCity, chargingAmount);
						}
					}
					else
					{
						cout << "Charging amount entered was not in the range of (0 - 50)";
					}
				}
				else
				{
					cout << "One of the inputs was not a city!\n";
				}
				break;
			case 10:
				cout << "New location:\n";
				getline(cin, city);
				cout << "Existing neighbour location to new location:\n";
				getline(cin, destinationCity);
				if (!charging.cityExists(city) && charging.cityExists(destinationCity))
				{
					cout << "Distance between locations:\n";
					cin >> weight;
					cout << "Charging price of station (if station cannot charge, input -1):\n";
					cin >> chargingCost;
					if((chargingCost >= -1) && (chargingCost < 1))
						charging.addLocation(city, destinationCity, weight, chargingCost);
					else
						cout << "Charging cost entered was not in the range of (-1 - 1)";
				}
				else
				{
					cout << "New city already exists or neighbour was not an existing city!\n";
				}
				break;
			case 0:
				exit(0);
				break;
			default:
				cout << "Not an option";
		}
	}


	return 0;
}
