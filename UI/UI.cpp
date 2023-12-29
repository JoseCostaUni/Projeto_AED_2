#include <thread>
#include <chrono>
#include "UI.h"

UI::UI() {}

void UI::loading_stuff(UI &ui) {
    LoadingFunctions::LoadFlights(g);
    this->logic = Logic(g);
    ui.load_sets();
    for(auto airline : LoadingFunctions::getArlines()){
        airlines.insert(airline.getCallSign());
    }
    diameter = g.calculateDiameter();
}

void UI::load_sets(){
    for(auto airport: g.getVertexSet()){
        this->cities.insert(airport->getInfo().getCity());
        this->airport_codes.insert(airport->getInfo().getCode());
        this->countries.insert(airport->getInfo().getCountry());
    }
}

void UI::clear_screen() {
    int i = 0;
    while(i != 100) {
        cout << endl;
        i++;
    }
}

bool UI::validate_input(char &op, const char lower_bound, const char upper_bound) {
    std::string tempValue;
    while(true){
        std::cin >> tempValue;
        std::cout << "\n";
        op = tempValue[0];
        op = std::toupper(op);
        if (std::cin.fail() || tempValue.length() != 1) {
            std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        }else{
            break;
        }
    }
    while (op < lower_bound || op > upper_bound) {
        std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        std::cin.clear();
        std::cin >> op;
    }
    return true;
}

void UI::menu_start() {
    char op;
    cout << "#################################################" << endl
         << "@@@@@  @@@@@  @@@@   @@@@@   @@@   @@@@   @@@@@  " << endl
         << "@   @    @    @@ @@  @@ @@  @   @  @@ @@    @    " << endl
         << "@@@@@    @    @@@@   @@@@@  @   @  @@@@     @    " << endl
         << "@   @    @    @@ @@  @@     @   @  @@ @@    @    " << endl
         << "@   @  @@@@@  @@ @@  @@      @@@   @@ @@    @    " << endl
         << "#################################################" << endl << '\n'
         << "Welcome to the Air Travel Flight Management System, what would you like to do?" << endl
         << "A. Proceed to the application" << endl
         << "B. Close the application" << endl
         << "Insert the letter: " ;
    validate_input(op,'A','B');
    switch(op){
        case 'A':
            main_menu();
            break;
        case 'B':
            cout << "Thanks for using our management system app!" << endl << "\n"
                 << "Made by: " << endl
                 << "Ângelo Oliveira || 202207798" << endl
                 << "José Costa      || 202207871" << endl
                 << "Bernardo Sousa  || 202206009" << endl;
            this_thread::sleep_for(chrono::seconds(2)); // Espera 2 segundos antes de fechar o terminal
            exit(0);

    }
}

void UI::main_menu(){
    char op;
    cout << "What would you like to know?" << endl;
    cout << "A. Consult Flights" << endl
         << "B. Consult Flight Statistics" << endl
         << "C. Plan a Trip" << endl
         << "D. Exit the Application" << endl
         << "Insert your choice:";

    validate_input(op, 'A', 'D');
    switch(op){
        case 'A':
            flight_consultation();
        case 'B':
            statistics_menu();
            break;
        case 'C':
            trip_planner();
            break;
        case 'D':
            //exit_menu()
            break;
        default:
            std::cerr << "Error";
    }
}

void UI::trip_planner(){
    char op;
    cout << "How would you like to chose your starting point?" << endl
         << "A. Origin Airport (You may use the name or the code of the airport)" << endl
         << "B: Origin City (We'll pick all airports in the city)" << endl
         << "C. Origin Country (We'll pick all airports in the country)" << endl
         << "D. Origin Coordinates (We'll pick the closest airport/s to the given coordinates)" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    string initial_Airport;
    string destination;
    unordered_set<string> filters;
    int choice = 0;
    bool Avoid_Or_Only ;
    bool Yes_or_No;

    std::string city;
    std::string country;

    auto commaPos = country.begin();
    switch ((op)) {
        case 'A':
            cout << "Insert the code of the airport where you would like to go from:" << endl;
            cin >> initial_Airport;
            get_destination(destination , choice , filters);
            switch (choice) {
                case 1:
                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);
                    if(Yes_or_No)
                    {
                        if(Avoid_Or_Only)
                        {
                            printList(logic.AirportToAirportAirlineOnlyFilters(Airport(initial_Airport) , Airport(destination) , filters));
                        }else
                        {
                            printList(logic.AirportToAirportAirlineAvoidFilters(Airport(initial_Airport) , Airport(destination) , filters));
                        }
                    }
                    else
                    {
                        printList(logic.AirportToAirport(Airport(initial_Airport) , Airport(destination)));
                    }
                    main_menu();
                    break;
                case 2:
                    //list<vector<Airport>> AirportToCountry(const Airport& initialAirport, const std::string& country);
                    //list<vector<Airport>> AirportToCountryAirlineAvoidFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);
                    //list<vector<Airport>> AirportToCountryAirlineOnlyFilter(Airport initialAirport , std::string country,unordered_set<std::string> airlines);

                    filters = get_Filters(Avoid_Or_Only , Yes_or_No);

                    commaPos = std::find(destination.begin(), destination.end(), ',');
                    if (commaPos != destination.end()) {
                        // Extract the first part (before the comma) and remove spaces
                        city = std::string(destination.begin(), commaPos);

                        // Extract the second part (after the comma) and remove spaces
                        country = std::string(std::find_if_not(commaPos + 1, destination.end(), ::isspace), destination.end());
                    } else {
                        std::cout << "Input not valid";
                        main_menu();
                    }

                    if(Yes_or_No)
                    {
                        list<vector<Airport>> CityToAirport(const Airport& destAirport , const std::string& city, const std::string& country , int choice , unordered_set<std::string> airlines);
                        list<vector<Airport>> CityToCity(const std::string& InitialCity, const std::string& InitialCountry,const std::string& FinalCity, const std::string& FinalCountry, int choice , const unordered_set<std::string>& airlines);
                        list<vector<Airport>> CityToCountry(const std::string& Initialcity, const std::string& InitialCountry, const std::string& country , int choice , const unordered_set<std::string>& airlines);

                        if(Avoid_Or_Only)
                        {
                            printList(logic.AirportToCityAirlineOnlyFilter(Airport(initial_Airport) , city , country , filters));
                        }else
                        {
                            printList(logic.AirportToCityAirlineAvoidFilter(Airport(initial_Airport) , city , country , filters));
                        }
                    }
                    else
                    {
                        printList(logic.AirportToCity(Airport(initial_Airport) , city , country));
                    }
                    main_menu();
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
            break;
        case 'B':

            break;
    }
}

void UI::get_destination(std::string& input , int& choice , unordered_set<std::string>& filters)
{
    char op;
    cout << "Which of these would you like to choose for destination point?" << endl
         << "A. Destination Airport (You may use the name or the code of the airport)" << endl
         << "B: Destination City (We'll pick all airports in the city)" << endl
         << "C. Destination Country (We'll pick all airports in the country)" << endl
         << "D. Destination Coordinates (We'll pick the closest airport/s to the given coordinates)" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    switch ((op)) {
        case 'A':
            cout << "Insert the code of the airport where you would like to go to:" << endl;
            cin >> input;
            choice = 1;
            break;
        case 'B':
            std::cin.ignore(); // Clear the input stream
            cout << "Insert the city where you would like to go to(Introduce it in the format [City,Country] :" << endl;
            std::getline(std::cin, input);
            choice = 2;
            break;
        case 'C':
            cout << "Insert the country of the airport where you would like to go to:" << endl;
            cin >> input;
            choice = 3;
            break;
        case 'D':
            cout << "Insert the coordinates of the closest airport where you would like to go to:" << endl;
            cin >> input;
            choice = 4;
            break;
    }
}

unordered_set<string> UI::get_Filters(bool& Avoid_Or_Only , bool& Yes_or_No)
{
    unordered_set<std::string> filters;
    string input;
    char op;
    cout << "Do you want to use airline filters?"<< endl;
    cout << "A - Yes" << endl
         << "B - No" << endl;
    validate_input(op , 'A' , 'B');

    Yes_or_No = op == 'A';
    string airline;
    if(Yes_or_No)
    {
        cout << "Introduce all airlines codes that you wish to include. Press 'd' when you're done" << endl;
        while (airline[0] != 'd')
        {
            std::cin >> airline;
            if(valid_airline(airline))
            {
                filters.insert(airline);
            }else
            {
                cout << "Please introduce a proper airline code" << endl;
            }
        }

        cout << "Do you wish to travel ONLY by these Airlines or to AVOID them?" << endl;
        cout << "A - ONLY" << endl
             << "B - AVOID" << endl;
        validate_input(op , 'A' , 'B');

        if(op == 'A'){
            Avoid_Or_Only = true;
        }else
        {
            Avoid_Or_Only = false;
        }
    }

    return filters;
}

bool UI::valid_airline(std::string& airline)
{
    if(airline[0] == 'd' && airline.size() == 1)
        return true;

    if (airline.length() != 3) {
        return false;
    }

    return std::all_of(airline.begin(), airline.end(), [](char c) {
        return std::isupper(c);
    });
}

void UI::printList(list<vector<Airport>> a)
{
    if(a.empty())
    {
        std::cout << "No trip available" << endl;
    }
    for(auto v : a){
        for(int i = 0 ; i < v.size()-1 ; i++){
            cout << v[i].getCode() << "->";
        }
        cout << v[v.size()-1].getCode() << endl;
    }
}

void UI::flight_consultation() {
    char op;
    cout << "How would you like to search for your flight? " << endl
         << "A. Consult number of flights out of an airport and from how many different airlines;" << endl
         << "B.Consult number of flights per city/airline " << endl
         << "Insert your choice: ";

    validate_input(op, 'A', 'B');
    switch(op){
        case 'A':
            number_out();
            break;
        case 'B':
            number_flights();
            break;

    }
}

void UI::statistics_menu(){
    char op;
    cout << "What statistics would you like to see?" << endl
         << "A. Global Statistics" << endl
         << "B. Airport Statistics" << endl
         << "C. Airline/City Statistics" << endl
         << "D. Country Statistics" << endl
         << "Insert your choice:";

    validate_input(op, 'A', 'E');
    switch(op){
        case 'A':
            global_numbers();
            break;
        case 'B':
            airport_statistics();
            break;
        case 'C':
            number_flights();
            break;
        case 'D':
            number_countries();
            break;
    }
}


void UI::airport_statistics(){
    char op;
    cout << "Which statistics would you like to know?" << endl
         <<"A. Consult number of destinations (airports, cities or countries) available for a given airport;" << endl
         <<"B. Consult number of reachable destinations from a given airport in a maximum of X lay-overs" << endl
         <<"C. Consult top-k airport with the greatest air traffic capacity, " << endl
         <<"D. Consult essential airports to the network's circulation capability" << endl
         << "Insert your option:";
    validate_input(op, 'A', 'D');
    switch (op){
        case 'A':
            number_reachable_destinations();
        case 'B':
            number_reachable_destinations_k();
        case 'C':
            greatest_traffic();
        case 'D':
            essential_airports();
    }

}


void UI::menu_options() {
    char op;
    clear_screen();
    cout << "What option would you like to choose?" << endl << '\n'
         << "A. Consult global number of airports and number of available flights" << endl //Global statistics
         << "B. Consult number of flights out of an airport and from how many different airlines;" << endl //flight consultation
         << "C. Consult number of flights per city/airline" << endl //flight consultation
         << "D. Consult number of different countries that a given airport/city flies to" << endl //Country statistics
         << "E. Consult number of destinations (airports, cities or countries) available for a given airport;" << endl // airport statistics
         << "F. Consult number of reachable destinations from a given airport in a maximum of X lay-overs" << endl // airport statistics
         << "G. Consult trip(s) with the greatest number of stops in between them" << endl
         << "H. Consult top-k airport with the greatest air traffic capacity, " << endl //airport statistics
         << "I. Consult essential airports to the network's circulation capability" << endl //airport statistics
         << "J. Consult best flight option(s) for a given source and destination locations" << endl //trip planner (ToDo)
         << "Insert the letter: ";
    validate_input(op,'A','J');
    switch(op){
        case 'A':
            global_numbers();
            break;
        case 'B':
            number_out();
            break;
        case 'C':
            number_flights();
            break;
        case 'D':
            number_countries();
            break;
        case 'E':
            number_reachable_destinations();
            break;
        case 'F':
            number_reachable_destinations_k();
            break;
        case 'G':
            longest_trip();
            break;
        case 'H':
            greatest_traffic();
            break;
        case 'I':
            essential_airports();
            break;
        case 'J':
            break;
    }
}

void UI::back_menu(){
    char op;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    menu_options();
}

void UI::global_numbers() {
    char op;
    cout << "Number of Airports: " << logic.GlobalNumberOfAirports() << endl;
    cout << "Number of Flights: " << logic.GlobalNumberOfFlights() << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    main_menu();
}

void UI::number_out() {
    char op;
    bool validate = false;
    std::pair<int, int> z;
    string airport_code;
    while(!validate){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        Airport airport = Airport(airport_code);
        if(g.findVertex(airport)){
            break;
        }else{
            cout << "Please insert a valid airport code" << endl;
        }
    }

    cout << endl;
    z = logic.FlightsOutOfAirportAndDifferentAirlines(airport_code);
    std::cout << "Number of flights: " << z.first << endl << "Number of different airlines: " << z.second << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    main_menu();
}

void UI::number_flights() {
    char op;
    cout << "Would you like to consult the flights per: " << endl;
    cout << "A. City" << endl;
    cout << "B. Airlines" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':{
            string city_name;
            while(true){
                city_name = "";
                cout << "What's the name of the city you would like to know the information?: ";
                cin >> city_name;
                if(this->cities.find(city_name) != this->cities.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << city_name << " : " <<logic.NumberOfFlightsPerCity(city_name) << endl;
            back_menu();
        }
        case 'B':{
            string airline_name;
            while(true){
                airline_name = "";
                cout << "What's the callsign of the airline you would like to know the information?: ";
                cin >> airline_name;
                if(this->airlines.find(airline_name) != this->airlines.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << airline_name << " airline : " << logic.NumberOfFlightsPerAirline(airline_name) << endl;
            back_menu();
        }
    }
    main_menu();
}

void UI::number_countries() {
    char op;
    cout << "Would you like to consult the number of different countries reachable from: " << endl;
    cout << "A. City" << endl;
    cout << "B. Airport" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    std::cout << "Insert the letter: ";
    validate_input(op,'A','B');
    switch(op){
        case 'A':{
            string city_name;
            while(true){
                city_name = "";
                cout << "What's the name of the city you would like to know the information?: ";
                cin >> city_name;
                if(this->cities.find(city_name) != this->cities.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << city_name << " : " <<logic.NumberOfCountriesThatCityFliesTo(city_name) << endl;
            back_menu();
        }
        case 'B':{
            string airport_code;
            while(true){
                airport_code = "";
                cout << "What's the code of the airport you would like to know the information?: ";
                cin >> airport_code;
                if(this->airport_codes.find(airport_code) != this->airlines.end()){
                    break;
                }
            }
            std::cout << "Number of flights of " << airport_code << " airport : " << logic.NumberOfCountries(airport_code) << endl;
            back_menu();
        }
    }
}

void UI::number_reachable_destinations() {
    string airport_code;
    while(true){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        if(this->airport_codes.find(airport_code) != this->airlines.end()){
            break;
        }
    }
    vector<Airport> tempVector = logic.nodesAtDistanceBFS(airport_code, diameter);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
    back_menu();

}

void UI::number_reachable_destinations_k() {
    string airport_code;
    int k;
    while(true){
        airport_code = "";
        cout << "What's the code of the airport you would like to know the information?: ";
        cin >> airport_code;
        if(this->airport_codes.find(airport_code) != this->airlines.end()){
            break;
        }
    }
    while(true){
        k = INT_MIN;
        cout << "What's the max number of lay-overs?: ";
        cin >> k;
        if(k >= 0 && k <= diameter){
            break;
        }
    }
    vector<Airport> tempVector = logic.nodesAtDistanceBFS(airport_code, k);

    vector<int> tempValues = logic.analyzeReachableAirports(tempVector);

    cout << "The " << airport_code << " airport within " << k << " lay-over(s) can reach:" << endl;
    cout << "Number of distinct airports: " << tempValues[0] << endl;
    cout << "Number of distinct countries: " << tempValues[1] << endl;
    cout << "Number of distinct cities: " << tempValues[2] << endl;
    back_menu();
}

void UI::longest_trip(){
    cout << "The longest distance is: " << diameter << endl << "Here are the longest flights:" << endl;
    for(auto v : g.getVertexSet())
    {
        vector<vector<Airport>> a = logic.FindMaxTripBfs(v->getInfo() , diameter);
        if(!a.empty()) {
            for (auto v: a) {
                vector<Airport> d = v;
                Airport z = d[0];
                Airport p = d[d.size() -1];
                cout << z.getCode() << " to " << p.getCode();
                cout << endl;
            }
        }
    }
    back_menu();
}

void UI::greatest_traffic(){
    int k;
    while(true){
        k = INT_MIN;
        cout << "What's the number of top airports you want to get information about?: ";
        cin >> k;
        if(k >= 0 && k <= airport_codes.size()){
            break;
        }
    }
    logic.GreatestKIndeegrees(k);
    back_menu();
}

void UI::essential_airports() {
    unordered_set<Airport> result = logic.findArticulationPoints();
    cout << "There are a total of " << result.size() << " essential airports" << endl;
    back_menu();
}
