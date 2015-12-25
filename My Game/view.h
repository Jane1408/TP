#pragma once
//#include <SFML/Graphics.hpp>

using namespace sf;

//sf::View view;//объ€вили sfml объект "вид", который и €вл€етс€ камерой

void setPlayerCoordinateForView(float x, float y, View & view) {
	float tempX = x; float tempY = y;
	if (x < 320) tempX = 320;//убираем из вида левую сторону
	if (y < 240) tempY = 240;//верхнюю сторону
	if (x > 1280) tempX = 1280;//нижнюю сторону	
	if (y > 2960) tempY = 2960;
	view.setCenter(tempX, tempY);
}