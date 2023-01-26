#include <iostream>
#include "math.h"
#include <SFML/Graphics.hpp>

#define radius 6

class City {

		public:
				City();
				City(int posX, int posY);
				~City();
				void render(sf::RenderWindow& window);
				int getX();
				int getY();
				inline int getRadius() { return radius; }

		private:
				int posX;
				int posY;

				sf::CircleShape shape;

};

float distance(City& c1, City& c2);
