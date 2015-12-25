#pragma once

//#include <SFML/Graphics.hpp>
//#include "view.h"


///////////////////////////////////НОМЕР МИССИИ//////////////////////////////////

int getCurrentMission(int a)//ф-ция номера миссия, которая меняет номер миссии, в зависимости от координаты игрока Х (сюда будем передавать эту координату)
{
	int mission = 0;
	if ((a>0) && (a<10)) { mission = 0; } //знакомим игрока с игрой
	if (a>20) { mission = 1; } //игрок на первой миссии
	if (a>700) { mission = 2; }//2ой
	if (a>2200) { mission = 3; }//и тд

	return mission;//ф-ция возвращает номер миссии
}



/////////////////////////////////////ТЕКСТ МИССИИ/////////////////////////////////
std::string getTextMission(int currentMission) {

	std::string missionText = "";//текст миссии и его инициализация

	switch (currentMission)//принимается номер миссии и в зависимости от него переменной missionText присваивается различный текст
	{
	case 0: missionText = "\nУровень 1 \nСобери 50 звездочек"; break;
	case 1: missionText = "\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасаться\n ... бла-бла-бла ..."; break;
	case 2: missionText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше "; break;
	case 3: missionText = "\nИ так далее \nи тому подобное....."; break;
	}

	return missionText;//ф-ция возвращает текст
};

