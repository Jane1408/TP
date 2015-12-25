#pragma once

//#include <SFML/Graphics.hpp>
//#include "view.h"


///////////////////////////////////����� ������//////////////////////////////////

int getCurrentMission(int a)//�-��� ������ ������, ������� ������ ����� ������, � ����������� �� ���������� ������ � (���� ����� ���������� ��� ����������)
{
	int mission = 0;
	if ((a>0) && (a<10)) { mission = 0; } //�������� ������ � �����
	if (a>20) { mission = 1; } //����� �� ������ ������
	if (a>700) { mission = 2; }//2��
	if (a>2200) { mission = 3; }//� ��

	return mission;//�-��� ���������� ����� ������
}



/////////////////////////////////////����� ������/////////////////////////////////
std::string getTextMission(int currentMission) {

	std::string missionText = "";//����� ������ � ��� �������������

	switch (currentMission)//����������� ����� ������ � � ����������� �� ���� ���������� missionText ������������� ��������� �����
	{
	case 0: missionText = "\n������� 1 \n������ 50 ���������"; break;
	case 1: missionText = "\nMission 1\n\n��� ���� ������\n ������, ��\n ���� ������ \n���� ����� ���������\n ... ���-���-��� ..."; break;
	case 2: missionText = "\nMission 2\n ���������� ������\n ���������� �������,\n ����� ������ ������ "; break;
	case 3: missionText = "\n� ��� ����� \n� ���� ��������....."; break;
	}

	return missionText;//�-��� ���������� �����
};

