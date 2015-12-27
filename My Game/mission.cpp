#include "stdafx.h"
#include "mission.h"

int getCurrentMission(int a)
{
	int mission = 0;
	if ((a>0) && (a<10)) { mission = 0; } 
	if (a>20) { mission = 1; } 
	if (a>700) { mission = 2; }
	if (a>2200) { mission = 3; }

	return mission;
}


std::string getTextMission(int currentMission) {

	std::string missionText = "";

	switch (currentMission)
	{
	case 0: missionText = "\nУровень 1 \nСобери 50 звездочек"; break;
	case 1: missionText = "\nMission 1\n\nВот твоя первая\n миссия, на\n этом уровне \nтебе стоит опасаться\n ... бла-бла-бла ..."; break;
	case 2: missionText = "\nMission 2\n Необходимо решить\n логическую задачку,\n чтобы пройти дальше "; break;
	case 3: missionText = "\nИ так далее \nи тому подобное....."; break;
	}

	return missionText;
};
