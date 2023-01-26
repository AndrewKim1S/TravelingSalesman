#include "TravelingSalesman.h"


// Road Class
TravelingSalesman::Road::Road() {}

TravelingSalesman::Road::Road(City& c1, City& c2, sf::Color c) {
		city1 = c1;
		city2 = c2;
		color = c;
		float angle = atan2((c1.getY() - c2.getY()), (c1.getX() - c2.getX())) * 180 / PI - 180;
		shape.setPosition(sf::Vector2f(c1.getX()+6, c1.getY()+6));
		roadLength = distance(c1, c2);
		shape.setSize(sf::Vector2f(roadLength, 3));
		shape.setFillColor(color);
		shape.setOrigin(0, 2);
		shape.setRotation(angle);
}

void TravelingSalesman::Road::render(sf::RenderWindow& window) {
		window.draw(shape);
}

float TravelingSalesman::Road::getRoadLength() {
		return roadLength;
}


// Route Class
TravelingSalesman::Route::Route() {}

TravelingSalesman::Route::Route(std::vector<City> cities) {
		this->cities = cities;
		this->shortestRoute = cities;
		distance = calculateDistance();
		shortestDistance = 99999;
		numCities = cities.size();
}

void TravelingSalesman::Route::renderRoads(sf::RenderWindow& window) {
		for(Road r : roads) {
				r.render(window);
		}
}

void TravelingSalesman::Route::createRoads() {
		roads.clear();
		for(int i = 0; i < numCities - 1; i++) {
				roads.push_back(Road(cities[i], cities[i+1], sf::Color::White));
		}
		roads.push_back(Road(cities[numCities-1], cities[0], sf::Color::White));
}

float TravelingSalesman::Route::calculateDistance() {
		float totalDistance = 0;
		for(Road r : roads) {
				totalDistance += r.getRoadLength();
		}
		if(totalDistance < shortestDistance) {
				shortestDistance = totalDistance;
				shortestRoute = cities;
		}
		return totalDistance;
}

void TravelingSalesman::Route::setCity(std::vector<City> c) {
		this->cities = c;
}

void TravelingSalesman::Route::renderShortest(sf::RenderWindow& window) {
		setCity(shortestRoute);
		createRoads();
}


// TravelingSalesman Class
TravelingSalesman::TravelingSalesman() {
		window = new sf::RenderWindow(sf::VideoMode(1500, 900), "Traveling Salesman");
		width = 1500;
		length = 900;
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(false);
		window->setPosition(sf::Vector2i(200, 75));

		state = State::IDLE;
		numCities = 5;
		createCities(numCities);
		
		font = new sf::Font();
		assert(font->loadFromFile("util/PlatNomor-eZ2dm.otf"));
		consoleInfo = new sf::Text();
		consoleInfo->setFont(*font);
		consoleInfo->setFillColor(sf::Color::White);
		consoleInfo->setCharacterSize(18);
		consoleInfo->setString("Traveling Salesman Simulation");
		consoleInfo->setPosition(sf::Vector2f(width/35, length/30));
		percentCompletion = new sf::Text();
		percentCompletion->setFont(*font);
		percentCompletion->setFillColor(sf::Color::White);
		percentCompletion->setCharacterSize(18);
		percentCompletion->setString("0 %");
		percentCompletion->setPosition(sf::Vector2f(width/35, length/30 + 30));
}

TravelingSalesman::~TravelingSalesman() {
		delete window;
}

void TravelingSalesman::run() {
		switch(state) {
				case IDLE:
						pollEvents();
						render();
						break;
				case BRUTEFORCE:
						clock.restart();
						consoleInfo->setString("Traveling Salesman - Brute Force Solution");
						totalNumOfPermutations = numCities;
						checkedPermutations = 0;
						for(int i = 1; i < numCities; i++) {
								totalNumOfPermutations *= numCities - i;
						}
						bruteForce(cities, numCities);
						route.renderShortest(*window);
						render();
						consoleInfo->setString("TravelingSalesman Simulation");
						state = State::IDLE;
						break;
				case GENETICALGORITHM: 
						break;
				case ANTCOLONYOPTOMIZATION:
						break;
				default:
						break;
		}
}

void TravelingSalesman::pollEvents() {
		while(window->pollEvent(event)) {
				switch(event.type) {
						case sf::Event::Closed:
								window->close();
								break;
						case sf::Event::KeyPressed:
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								} if(event.key.code == sf::Keyboard::B) {
										state = State::BRUTEFORCE;
								}
								break;
						default:
								break;
				}
		}
}

void TravelingSalesman::render() {
		window->clear(sf::Color(32, 32, 32));
		for(City c : cities) {
				c.render(*window);
		}
		route.renderRoads(*window);
		window->draw(*consoleInfo);
		window->draw(*percentCompletion);
		window->display();
}

bool TravelingSalesman::isOpen() {
		return window->isOpen();
}

void TravelingSalesman::createCities(int numCities) {
		for(int i = 0; i < numCities; i++) {
				bool CityCreated = false;
				while(!CityCreated) {
						bool validCity = true;
						City newCity = City(rand() % static_cast<int>(width*0.8) + width/10, 
								rand() % static_cast<int>(length*0.8) + length/10);
						for(City c : cities) {
								if(distance(c, newCity) < 25) {
										validCity = false;
								}
						}
						if(validCity) {
								cities.push_back(newCity);
								CityCreated = true;
						}
				}
		}
		route = Route(cities);
		route.createRoads();
}

void TravelingSalesman::bruteForce(std::vector<City> c, int size) {
		if(size == 1) {
				bool timeElapsed = false;
				while(!timeElapsed) {
						if(clock.getElapsedTime().asMilliseconds() > 400) {
								clock.restart();
								timeElapsed = true;
						}
				}
				checkedPermutations ++;
				std::string percent = std::to_string(static_cast<double>(checkedPermutations) / 
						static_cast<double>(totalNumOfPermutations) * 100);
				percentCompletion->setString(percent.substr(0,4) + 
						" %  ...  Shortest Distance: " + 
						std::to_string(route.shortestDistance).substr(0, 4));
				route.setCity(c);
				route.createRoads();
				route.calculateDistance();
				render();
				return;
		}
		pollEvents();
		for(int i = 0; i < size; i++) {
				bruteForce(c, size -1);
				if(size % 2 == 1) {
						std::swap(c[0], c[size - 1]);
				} else {
						std::swap(c[i], c[size - 1]);
				}
		}
}
