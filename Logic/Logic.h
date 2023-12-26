//
// Created by jose-costa on 12/23/23.
//

#ifndef PROJETO_2_LOGIC_H
#define PROJETO_2_LOGIC_H

#include <unordered_map>
#include <memory>
#include "Graph.h"
#include "Airport.h"


class Logic {
private:
    Graph<Airport> graph;
    //maps Airport names to codes
    unordered_map<std::string , std::string> NamesToCodes;
public:
    Logic();
    Logic(Graph<Airport>& g);

    double HaversineAlgorithm(double lat1, double lon1,double lat2, double lon2);
    void DijkstraAlgorithm();
    int GlobalNumbers();
    int GlobalNumberOfAirports();
    //todo perguntar ao prof se per city é para ou de ou ambos
    int NumberOfFlightsPerCity(std::string city);
    int NumberOfFlightsPerAirline(const std::string& airlineCode);
    int NumberOfCountries(std::string airportCode);
    int NumberOfCountriesThatCityFliesTo(std::string city);
    size_t GlobalNumberOfFlights();
    std::pair<int , int> FlightsOutOfAirportAndDifferentAirlines(const std::string& AirportCode);
    vector<string> TopTrafficAirports(int k);
};


#endif //PROJETO_2_LOGIC_H
