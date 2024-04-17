#include "CCar.h"

const int GEAR_R = -1;
const int GEAR_N = 0;
const int MIN_SPEED = 0;
const int MAX_SPEED = 150;
const int MAX_R_SPEED = 20;

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_isEngineOn = true;
	return m_isEngineOn;
}

bool Car::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool Car::SetGear(int gear)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	auto it = GEARS_AND_SPEEDS.find(gear);
	if (it == GEARS_AND_SPEEDS.end())
	{
		return false;
	}

	if (it->first == GEAR_R && m_speed != 0)
	{
		return false;
	}

	if ((m_direction == Direction::BACKWARD && gear > 0) ||
		(m_direction == Direction::FORWARD && gear < 0))
	{
		return false;
	}

	if (m_speed < it->second.lowerBound || m_speed > it->second.upperBound)
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		return false;
	}

	if (!m_isEngineOn)
	{
		return false;
	}

	auto it = GEARS_AND_SPEEDS.find(m_gear);
	if (it == GEARS_AND_SPEEDS.end())
	{
		return false;
	}

	if (it->first == GEAR_N && m_speed < speed)
	{
		return false;
	}

	if (speed < it->second.lowerBound || speed > it->second.upperBound)
	{
		return false;
	}

	m_speed = speed;
	if (speed == 0)
	{
		m_direction = Direction::STANDING_STILL;
	}
	else if (m_gear == GEAR_R)
	{
		m_direction = Direction::BACKWARD;
	}
	else
	{
		m_direction = Direction::FORWARD;
	}
	return true;
}