#include <iostream>
#include <string>
#include <sstream>
#include "CRemoteControl.h"
#include "CCar.h"

const std::string EXIT = "...";

void RemoteControl::ExecuteCommand() const
{
	std::string command;
	m_output << "Info. ������� ��������� ��������� ����������, ����������� ��������, �������� � ��������" << std::endl;
	m_output << "EngineOn. �������� ���������" << std::endl;
	m_output << "EngineOff. ��������� ���������" << std::endl;
	m_output << "SetGear ��������. �������� �������� ��������, �������� ������ �� - 1 �� 5" << std::endl;
	m_output << "SetSpeed ��������. ������������� ��������� �������� ��������, �������� ��������������� ������" << std::endl;
	m_output << "... - ��� ������" << std::endl;

	while (std::getline(m_input, command))
	{
		if (command.empty())
		{
			continue;
		}

		if (command == EXIT)
		{
			break;
		}

		std::istringstream iss(command);
		std::string operation;
		int number;
		iss >> operation >> number;

		if (operation == "Info")
		{
			m_output << "��������� ���������: " << (m_car.IsTurnedOn() ? "���" : "����") << std::endl;
			m_output << "����������� ��������: ";
			switch (m_car.GetDirection())
			{
			case Direction::FORWARD:
				m_output << "forward" << std::endl;
				break;
			case Direction::BACKWARD:
				m_output << "backward" << std::endl;
				break;
			case Direction::STANDING_STILL:
				m_output << "standing still" << std::endl;
				break;
			}

			m_output << "��������: " << m_car.GetSpeed() << std::endl;
			m_output << "��������: " << m_car.GetGear() << std::endl;
			continue;
		}

		if (operation == "EngineOn")
		{
			if (m_car.TurnOnEngine())
			{
				m_output << "��������� �������" << std::endl;
			}
			else
			{
				m_output << "��������� �� �������" << std::endl;
			}
			continue;
		}

		if (operation == "EngineOff")
		{
			if (m_car.TurnOffEngine())
			{
				m_output << "��������� ��������" << std::endl;
			}
			else
			{
				m_output << "��������� �� ��������" << std::endl;
			}
			continue;
		}

		if (operation == "SetGear")
		{
			if (m_car.SetGear(number))
			{
				m_output << "�������� ��������" << std::endl;
			}
			else
			{
				m_output << "�������� �� ��������" << std::endl;
			}
			continue;
		}

		if (operation == "SetSpeed")
		{
			if (m_car.SetSpeed(number))
			{
				m_output << "�������� �����������" << std::endl;
			}
			else
			{
				m_output << "�������� �� �����������" << std::endl;
			}
			continue;
		}

		m_output << "����������� �������!" << std::endl;
	}
}