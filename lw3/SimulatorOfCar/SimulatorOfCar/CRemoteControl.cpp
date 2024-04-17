#include <iostream>
#include <string>
#include <sstream>
#include "CRemoteControl.h"
#include "CCar.h"

const std::string EXIT = "...";

void RemoteControl::ExecuteCommand() const
{
	std::string command;
	m_output << "Info. Выводит состояние двигателя автомобиля, направление движения, скорость и передачу" << std::endl;
	m_output << "EngineOn. Включает двигатель" << std::endl;
	m_output << "EngineOff. Выключает двигатель" << std::endl;
	m_output << "SetGear передача. Включает заданную передачу, заданную числом от - 1 до 5" << std::endl;
	m_output << "SetSpeed скорость. Устанавливает указанную скорость движения, заданную неотрицательным числом" << std::endl;
	m_output << "... - для выхода" << std::endl;

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
			m_output << "Состояние двигателя: " << (m_car.IsTurnedOn() ? "вкл" : "выкл") << std::endl;
			m_output << "Направление движения: ";
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

			m_output << "Скорость: " << m_car.GetSpeed() << std::endl;
			m_output << "Передача: " << m_car.GetGear() << std::endl;
			continue;
		}

		if (operation == "EngineOn")
		{
			if (m_car.TurnOnEngine())
			{
				m_output << "Двигатель включен" << std::endl;
			}
			else
			{
				m_output << "Двигатель не включен" << std::endl;
			}
			continue;
		}

		if (operation == "EngineOff")
		{
			if (m_car.TurnOffEngine())
			{
				m_output << "Двигатель выключен" << std::endl;
			}
			else
			{
				m_output << "Двигатель не выключен" << std::endl;
			}
			continue;
		}

		if (operation == "SetGear")
		{
			if (m_car.SetGear(number))
			{
				m_output << "Передача включена" << std::endl;
			}
			else
			{
				m_output << "Передача не включена" << std::endl;
			}
			continue;
		}

		if (operation == "SetSpeed")
		{
			if (m_car.SetSpeed(number))
			{
				m_output << "Скорость установлена" << std::endl;
			}
			else
			{
				m_output << "Скорость не установлена" << std::endl;
			}
			continue;
		}

		m_output << "Неизвестная команда!" << std::endl;
	}
}