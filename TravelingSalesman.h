#include <iostream>
#include <vector>
#include <cassert>
#include "City.h"
#include "math.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define PI 3.1415

class TravelingSalesman {
		
		struct Road {
				City city1;
				City city2;
				sf::RectangleShape shape;
				sf::Color color;
				float angle;
				float roadLength;

				Road();
				Road(City& c1, City& c2, sf::Color c);
				void render(sf::RenderWindow& window);
				float getRoadLength();
		};

		struct Route {
				std::vector<Road> roads;
				std::vector<Road> shortestRoad;
				std::vector<City> cities;
				std::vector<City> shortestRoute;
				float distance;
				float shortestDistance;
				int numCities;

				Route();
				Route(std::vector<City> cities);
				void renderRoads(sf::RenderWindow& window);
				void createRoads();
				float calculateDistance();
				void setCity(std::vector<City> c);
				void renderShortest(sf::RenderWindow& window);
		};

		public:
				enum State {
						IDLE,
						BRUTEFORCE,
						GENETICALGORITHM,
						ANTCOLONYOPTOMIZATION
				};

				TravelingSalesman();
				~TravelingSalesman();

				void run();
				void pollEvents();
				void render();
				bool isOpen();
				void createCities(int numCities);
				void bruteForce(std::vector<City> c, int size);

		private:
				State state;
				Route route;
				int width;
				int length;
				std::vector<City> cities;
				std::vector<Road> roads;
				int numCities;

				int totalNumOfPermutations;
				int checkedPermutations;

				sf::RenderWindow* window;
				sf::Event event;
				sf::Clock clock;
				sf::Font* font;
				sf::Text* consoleInfo;
				sf::Text* percentCompletion;
};
