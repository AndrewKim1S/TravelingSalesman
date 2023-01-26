#include "City.h"


City::City() {}

City::City(int posX, int posY) {
		this->posX = posX - radius;
		this->posY = posY - radius;
		shape.setRadius(radius);
		shape.setFillColor(sf::Color(128, 128, 128));
		shape.setOutlineThickness(radius/3);
		shape.setOutlineColor(sf::Color(255, 255, 255));
		shape.setPosition(posX - radius, posY - radius);
}

City::~City() {
		// delete shape;
}

void City::render(sf::RenderWindow& window) {
		window.draw(shape);
}

int City::getX() {
		return this->posX;
}

int City::getY() {
		return this->posY; 
}

float distance(City& c1, City& c2) {
		return sqrt(pow(c1.getX() - c2.getX(), 2) + 
				pow(c1.getY() - c2.getY(), 2));
}
