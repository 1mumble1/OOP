#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../SimulatorOfCar/Car.h"

SCENARIO("If create a car, it will be with turned off engine and speed = 0 and gear = 0 and direction is standing")
{
	Car car;
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("If create a car and turn on engine, try to turn it on again will be ok")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.IsTurnedOn());
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.IsTurnedOn());
}

SCENARIO("If create a car and turn on engine, you can turn it off again and again")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsTurnedOn());
}

SCENARIO("If create a car and turn on engine and try set any speed, it will be failed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(!car.SetSpeed(10));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("If create a car and turn on engine, you can set gear R or 1st without setting speed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.GetGear() == -1);
}

SCENARIO("If create a car and turn on engine and set gear R, you can set speed and get it with direction")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
}

SCENARIO("If create a car and turn on engine and set gear 1st, you can set speed and get it with direction")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
}

SCENARIO("If create a car and turn on engine and try set any gear except 1st and R, it will be failed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(!car.SetGear(2));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("If create a car and turn on engine and set gear R with non-null speed, you can't set 1st gear")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.GetGear() == -1);
}