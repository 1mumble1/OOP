#pragma once
#include <map>

enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL
};

struct SpeedLimits
{
	int lowerBound;
	int upperBound;
};

class Car
{
public:
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
	Direction m_direction = Direction::STANDING_STILL;

	const std::map<int, SpeedLimits> GEARS_AND_SPEEDS = {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}}};
};