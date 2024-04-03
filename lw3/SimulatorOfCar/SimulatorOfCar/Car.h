#pragma once
#include <stdint.h>;

using namespace std;

enum class Direction
{
	FORWARD,
	BACKWARD,
	STANDING_STILL
};

class Car
{
public:
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int8_t GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn = false;
	int8_t m_gear = 0;
	int m_speed = 0;
};