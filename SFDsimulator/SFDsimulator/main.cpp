#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include "Fluide.h"
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)));



using namespace std;

int N = 512;
Fluide fluide(0.1f, 0.0f, 0.00000000000000001f);

void draw() {
	int cx = int(0.5*N / 8);
	int cy = int(0.5*N / 8);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			fluide.addDensity(cx + i, cy + j, rand() % (150 - 50 + 1) + 50);
			
		}
	}
	//i отвечает за скорость!
	for (int i = 0; i < 4; i++) {
		float t = 0.0f;
		float angle =  t*6.2831855f *2;
		float a = angle * (180 / 3.14);
		float x = sin(a);
		float y = cos(a);
		sf::Vector2f v(x, y);
		v.x = v.x*0.2;
		v.y = v.y*0.2;
		t += 0.01;
		fluide.addVelocity(cx, cy, v.x, v.y);
	}
}


int IX(int x, int y) {
	x = constrain(x, 0, N - 1);
	y = constrain(y, 0, N - 1);
	return x + (y * N);
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(N, N), "Fluide" , sf::Style::Default, settings);
	//фпс счетчик
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	//конец фпс 
	

	while (window.isOpen()) {
		//fps
		end = std::chrono::system_clock::now();
		std::chrono::duration<float> diff = end - start;
		window.setTitle("Fluid simulator " + std::to_string(int(1.0f / diff.count())) + " fps");
		start = end;
		
		//endfps
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		draw();
		std::vector<sf::RectangleShape> rt = fluide.renderD();
		for (auto && r : rt) window.draw(r);
		fluide.step();
		//window.draw(fluide.renderD());
		
		
		
		/*sf::VertexArray pointr(sf::Points, 230400);
		float w = 0;
		float h = 0;
		for (int i = 0; i < 230400; i++) {
			pointr[i].color = sf::Color(117, 193, 255);
			pointr[i].position = sf::Vector2f(w, h);
			if (w < 640) {
				w++;
			}
			else {
				w = 0;
				h++;
			}
		}*/
		
	
		//window.draw(pointr);
		window.display();
		
	}


	return 0;
}



