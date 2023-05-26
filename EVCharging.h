/*
 * EVCharging.h
 *
 *  Created on: 29 Apr 2023
 *      Author: 2002345
 */

#ifndef EVCHARGING_H_
#define EVCHARGING_H_

class EVCharging
{ // you may also declare this class as an extension of WeightedGraph
private:
	map<int, Location> locations; /* The int represents what number the key for the location and
	is the number of the location in the list (Penrith = 0, St Marys = 1 etc.). The location object holds the name
	of the location, whether there is a charging station and the charging price*/
	int numberOfLocations;
	WeightedGraphType *graph;
	unordered_set<string> locationList;

public:
	EVCharging();
	~EVCharging();
	bool cityExists(string location);
	void inputLocations();
	void printLocations();
	void printAdjacencyMatrix();
	void leastExpensiveChargingStations();
	void adjacentLocations(string locationName);											// Task 3
	void cheapestAdjacentCity(string locationName);											// Task 4
	void closestCity(string locationName);													// Task 5
	void cheapestLocation(string locationName);												// Task 6
	double cheapestPath(string locationName, string destinationName);						// Task 7
	void cheapestPath(string locationName, string destintaionName, int chargingAmount);		// Task 8
	// Task 9
	void cheapestPathFree(string locationName, string destinationName, int chargingAmount); 
	vector<int> findAllPaths(int start, int end, int chargingAmount);
	list<int> getNeighbours(int vertex);
	bool exists(int vertex, vector<int> path);
	double costOfPath(vector<int> path, int chargingAmount, int flag);
};

bool EVCharging::cityExists(string location)
{
	return locationList.count(location) > 0;
}

EVCharging::EVCharging()
{
	inputLocations();
	graph = new WeightedGraphType(numberOfLocations);
}

EVCharging::~EVCharging()
{
	delete graph;
}
void EVCharging::inputLocations()
{
	ifstream infile;
	char fileName[50] = "Locations.txt";

	infile.open(fileName);

	if (!infile)
	{
		cout << "Cannot open input file." << endl;
		return;
	}
	// Opens file
	int locationIndex = 0;

	while (!infile.eof())
	{
		Location s;
		string charger;
		string price;
		while (!infile.eof())
		{
			getline(infile, s.locationName, ',');
			getline(infile, charger, ',');
			getline(infile, price);
			s.chargerInstalled = (stoi(charger) == 1) ? true : false;
			s.chargingPrice = stod(price);
			s.index = locationIndex;
			locationList.insert(s.locationName);
			locations[locationIndex] = s;
			locationIndex++;
		}
	}

	numberOfLocations = locationIndex;
}

void EVCharging::printLocations()
{
	cout << "List of locations and charging information " << endl;
	cout << setw(8) << "Index" << setw(20) << "Location name" << setw(20) << "Charging station" << setw(20) << "Charging price" << endl;

	map<int, Location>::iterator it = locations.begin();

	for (; it != locations.end(); it++)
	{
		it->second.printLocation();
	}

	cout << endl;
}

void EVCharging::printAdjacencyMatrix()
{
	cout << "Adjacency matrix (0 means no direct connection, non-zero value represents the distance of adjacent locations)\n"
		 << endl;
	cout << setw(13) << " ";
	for (int i = 0; i < numberOfLocations; i++)
	{
		cout << setw(13) << locations[i].locationName;
	}
	cout << endl;
	for (int i = 0; i < numberOfLocations; i++)
	{
		cout << setw(13) << locations[i].locationName;
		for (int j = 0; j < numberOfLocations; j++)
		{
			cout << setw(13) << (graph->getWeight(i, j) == DBL_MAX ? 0.0 : graph->getWeight(i, j));
		}
		cout << endl;
	}
}

void EVCharging::adjacentLocations(string location)
{
	int adjCityCharging = 0;
	int index;
	for (int i = 0; i < numberOfLocations; i++)
		if (locations[i].locationName == location)
		{
			index = i;
			break;
		}

	if (index == numberOfLocations)
	{
		cout << "Not available on the map";
		return;
	}
	cout << "Adjacent cities to " << location << " with charging stations: " << endl;
	for (int j = 0; j < numberOfLocations; j++)
	{
		if ((graph->getWeight(index, j) != DBL_MAX) && (locations[j].chargerInstalled != 0))
		{
			cout << locations[j].locationName << endl;
			adjCityCharging++;
		}
	}

	if (adjCityCharging == 0)
	{
		cout << "None. There were no adjacent cities with charging stations!";
	}
	return;
}

void EVCharging::leastExpensiveChargingStations()
{
	priority_queue<Location> chargers;
	for (int i = 0; i < locations.size(); i++)
	{
		if (locations[i].chargerInstalled != 0)
			chargers.push(locations[i]);
	}
	cout << endl;
	while (!chargers.empty())
	{
		if (chargers.top().locationName.length() < 8)
			cout << chargers.top().index << "\t" << chargers.top().locationName << "\t\tYes";
		else
			cout << chargers.top().index << "\t" << chargers.top().locationName << "\tYes";
		if (chargers.top().chargingPrice == 0)
			cout << "\tfree of charge" << endl;
		else
			cout << "\t$" << chargers.top().chargingPrice << "/kWh" << endl;
		chargers.pop();
	}
	return;
}

void EVCharging::cheapestAdjacentCity(string location)
{
	Location cheapestCity;
	double cheapest = 100;
	srand(time(NULL));
	double chargingAmount = rand() % 40 + 10;
	int adjCityCharging = 0, index;
	for (int i = 0; i < numberOfLocations; i++)
		if (locations[i].locationName == location)
		{
			index = i;
			break;
		}
	if (index == numberOfLocations)
	{
		cout << "Not available on the map";
		return;
	}
	cout << "Charging amount: " << chargingAmount << "kWh";
	for (int j = 0; j < numberOfLocations; j++)
		if ((graph->getWeight(index, j) != DBL_MAX) && (locations[j].chargerInstalled != 0))
		{
			double cost = ((graph->getWeight(index, j) * 2) * 0.10) + (chargingAmount * locations[j].chargingPrice);
			if (cost < cheapest)
			{
				cheapestCity = locations[j];
				cheapest = cost;
			}
			adjCityCharging++;
		}
	cout << endl
		 << "The cheapest next charging station is " << cheapestCity.locationName << ". Charging cost = $" << cheapest;
	if (adjCityCharging == 0)
		cout << "There were no adjacent cities with charging stations!";
	return;
}

void EVCharging::closestCity(string locationName) // Create shortest path (figure out how to do this)
{
	vector<vector<double> > placeholder;
	double shortest = DBL_MAX;
	int adjCityCharging = 0, index, shortestIndex;
	for (int i = 0; i < numberOfLocations; i++) // Finds locaiton input
		if (locations[i].locationName == locationName)
		{
			index = i;
			break;
		}
	placeholder = graph->shortestPath(index);
	for (int j = 0; j < numberOfLocations; j++)
	{
		if (j == index)
		{
			continue;
		}
		else if ((shortest > placeholder[0][j]) && (locations[j].chargerInstalled != 0))
		{
			shortest = placeholder[0][j];
			shortestIndex = j;
		}
	}
	cout << locations[shortestIndex].locationName << " is the closest city with a distance of " << shortest;
}

void EVCharging::cheapestLocation(string locationName)
{
	vector<vector<double> > placeholder;
	srand(time(NULL));
	int index = 0, cheapestCity = 0, chargingAmount = rand() % 40 + 11;
	double cheapest = 1000, cost = 0;
	for (int i = 0; i < numberOfLocations; i++) // Finds locaiton input
		if (locations[i].locationName == locationName)
		{
			index = i;
			break;
		}
	placeholder = graph->shortestPath(index);
	cout << "Charging amount: " << chargingAmount << "kWh" << endl;
	for (int j = 0; j < numberOfLocations; j++)
	{
		cost = (((placeholder[0][j] * 2) * 0.10) + (locations[j].chargingPrice * chargingAmount));
		if (j == index)
		{
			continue;
		}
		if (locations[j].chargerInstalled == 0)
		{
			continue;
		}
		if (chargingAmount < 25)
		{
			if (cheapest > cost)
			{
				cheapest = cost;
				cheapestCity = j;
			}
		}
		else if (chargingAmount > 25 && locations[j].chargingPrice > 0)
		{
			if (cheapest > cost)
			{
				cheapest = cost;
				cheapestCity = j;
			}
		}
	}
	cout << "The cheapest other charging station is " << locations[cheapestCity].locationName << endl
		 << "Distance = " << placeholder[0][cheapestCity] << "km" << endl
		 << "Charging Cost = $" << locations[cheapestCity].chargingPrice * chargingAmount << endl;
	cout << "Travel Cost = $" << (placeholder[0][cheapestCity] * 2) * 0.10 << endl
		 << "Total Cost = $" << cheapest;
	return;
}

void EVCharging::cheapestPath(string locationName, string destinationName, int chargingAmount)
{
	vector<vector<double> > placeholder;
	stack<int> stops;
	srand(time(NULL));
	int sourceIndex = 0, destinationIndex = 0, vertex = 0, cheapestStop = 0, stopNumber = 1;
	double cost = 0, cheapest = 1000;
	for (int i = 0; i < numberOfLocations; i++) // Finds locaiton input
		if (locations[i].locationName == locationName)
		{
			sourceIndex = i;
			break;
		}
	placeholder = graph->shortestPath(sourceIndex);
	for (int i = 0; i < numberOfLocations; i++) 
		if (locations[i].locationName == destinationName)
		{
			destinationIndex = i;
			break;
		}
	vertex = destinationIndex;
	while (vertex != sourceIndex)
	{
		stops.push(vertex);
		cost = ((placeholder[0][destinationIndex]) * 0.10) + (chargingAmount * locations[vertex].chargingPrice);
		if (chargingAmount <= 25)
		{
			if (cheapest > cost)
				cheapestStop = vertex;
		}
		else if (chargingAmount > 25 && locations[vertex].chargingPrice > 0)
		{
			if (cheapest > cost)
				cheapestStop = vertex;
		}
		vertex = placeholder[1][vertex] - 1;
	}
	cout << "The charging amount " << chargingAmount << endl
		 << "The cheapest other charging station is " << locations[cheapestStop].locationName << endl
		 << "Charging cost = $" << (chargingAmount * locations[cheapestStop].chargingPrice) << endl
		 << "Travel cost = $" << ((placeholder[0][destinationIndex]) * 0.10) << endl
		 << "Total cost = $" << ((placeholder[0][destinationIndex]) * 0.10) + (chargingAmount * locations[cheapestStop].chargingPrice) << endl
		 << "Travel path: " << locations[sourceIndex].locationName;

	while (!stops.empty())
	{
		cout << ", " << locations[stops.top()].locationName;
		stops.pop();
	}
}

void EVCharging::cheapestPathFree(string locationName, string destinationName, int chargingAmount)
{
	int sourceIndex, destinationIndex;
	vector<int> bestPath;
	for (int i = 0; i < numberOfLocations; i++) // Finds locaiton input
		if (locations[i].locationName == locationName)
		{
			sourceIndex = i;
			break;
		}
	for (int i = 0; i < numberOfLocations; i++) 
		if (locations[i].locationName == destinationName)
		{
			destinationIndex = i;
			break;
		}
	bestPath = findAllPaths(sourceIndex, destinationIndex, chargingAmount);
	double totalCost = costOfPath(bestPath, chargingAmount, 1);
}

vector<int> EVCharging::findAllPaths(int start, int end, int chargingAmount)
{
	vector<int> cheapestPath;
	double cheapestCost = 10000;
	vector<int> initialPath;
	stack<pair<int, vector<int> > > pathStack;
	initialPath.push_back(start);
	pathStack.push(make_pair(start, initialPath));

	while (!pathStack.empty())
	{
		auto current = pathStack.top();
		pathStack.pop();
		int currentVertex = current.first;
		vector<int> currentPath = current.second;
		if (currentVertex == end && !currentPath.empty())
		{
			if (currentPath[currentPath.size() - 1] == end && currentPath[0] == start)
				if (costOfPath(currentPath, chargingAmount, 0) < cheapestCost)
				{
					cheapestCost = costOfPath(currentPath, chargingAmount, 0);
					cheapestPath = currentPath;
				}
		}
		else
		{
			for (int i : getNeighbours(currentVertex))
			{
				if (!exists(i, currentPath))
				{
					vector<int> newPath = currentPath;
					newPath.push_back(i);
					pathStack.push(make_pair(i, newPath));
				}
			}
		}
	}
	return cheapestPath;
}
double EVCharging::costOfPath(vector<int> path, int chargingAmount, int flag)
{
	double distance = 0, cheapest = 100000;
	int chargingLeft = chargingAmount;
	for (int j = 0; j < path.size() - 1; j++)
	{
		if (locations[path[j]].chargerInstalled != 0)
		{
			if (locations[path[j]].chargingPrice == 0)
			{
				if (flag == 1)
				{
					cout << locations[path[j]].locationName << endl;
				}
				chargingLeft -= 25;
			}
			else if (locations[path[j]].chargingPrice < cheapest)
			{
				cheapest = locations[path[j]].chargingPrice;
			}
		}

		distance += graph->getWeight(path[j], path[j+1]);
	}
	if(chargingLeft < 0)
			chargingLeft = 0;
	if (flag == 1)
	{
		cout << "Travel cost = " << (distance * 0.10) << endl
			 << "Charging cost = " << (chargingLeft * cheapest) << endl
			 << "Total cost = " << (distance * 0.10) + (chargingLeft * cheapest) << endl
			 << "Path: " << locations[path[0]].locationName;
		for(int i = 1; i < path.size(); i++)
		{
			cout << ", " << locations[path[i]].locationName;
		}
	}
	return (distance * 0.10) + (chargingLeft * cheapest);
}

bool EVCharging::exists(int vertex, vector<int> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == vertex)
		{
			return true;
		}
	}
	return false;
}
list<int> EVCharging::getNeighbours(int vertex)
{
	list<int> neighbours;
	for (int j = 0; j < numberOfLocations; j++) 
	{
		if (graph->getWeight(vertex, j) != DBL_MAX)
			neighbours.push_back(j);
	}
	return neighbours;
}

#endif /* EVCHARGING_H_ */
