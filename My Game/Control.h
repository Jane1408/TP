#pragma once
//#include "Classes.h"
//#include <SFML/Graphics.hpp>
//#include "view.h"
//#include "Struct.h"


using namespace sf;


void controlPlayer(Sprite & sprite, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down, int w, int h);

void AttackControlPlayer(Sprite & sprite, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down, int w, int h);

//void ControlNonPlayer(Sprite & sprite_non);