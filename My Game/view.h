#pragma once
//#include <SFML/Graphics.hpp>

using namespace sf;

//sf::View view;//�������� sfml ������ "���", ������� � �������� �������

void setPlayerCoordinateForView(float x, float y, View & view) {
	float tempX = x; float tempY = y;
	if (x < 320) tempX = 320;//������� �� ���� ����� �������
	if (y < 240) tempY = 240;//������� �������
	if (x > 1280) tempX = 1280;//������ �������	
	if (y > 2960) tempY = 2960;
	view.setCenter(tempX, tempY);
}