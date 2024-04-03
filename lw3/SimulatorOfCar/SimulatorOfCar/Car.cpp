#include "Car.h"
#include <cmath>
#include <map>

const int GEAR_R = -1;
const int GEAR_N = 0;
const int MIN_SPEED = 0;
const int MAX_SPEED = 150;
const int MAX_R_SPEED = 20;

struct SpeedLimits
{
	int lowerBound;
	int upperBound;
};

const map<int8_t, SpeedLimits> GEARS_AND_SPEEDS = {
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}
};

bool Car::IsTurnedOn() const
{
	return m_isEngineOn;
}

Direction Car::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::STANDING_STILL;
	}

	if (m_speed < 0)
	{
		return Direction::BACKWARD;
	}

	return Direction::FORWARD;
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int8_t Car::GetGear() const
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

	if ((gear == GEAR_R && m_speed != MIN_SPEED) ||
		(gear == GEAR_N && m_speed < MIN_SPEED && m_speed > MAX_SPEED))
	{
		return false;
	}

	auto it = GEARS_AND_SPEEDS.find(gear);
	if (it == GEARS_AND_SPEEDS.end())
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

	if (m_gear == GEAR_R && speed < MIN_SPEED && speed > MAX_R_SPEED)
	{
		return false;
	}

	if (m_gear == GEAR_N && m_speed < speed)
	{
		return false;
	}

	auto it = GEARS_AND_SPEEDS.find(m_gear);
	if (speed < it->second.lowerBound && speed > it->second.upperBound)
	{
		return false;
	}

	if (m_gear == GEAR_R)
	{
		m_speed = -speed;
	}
	else
	{
		m_speed = speed;
	}

	return true;
}