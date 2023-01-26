#include <iostream>
#include "TravelingSalesman.h"


int main() {
		srand(static_cast<unsigned>(time(0)));		
		TravelingSalesman t = TravelingSalesman();

		while(t.isOpen()) {
				t.run();
		}

		return 0;
}
