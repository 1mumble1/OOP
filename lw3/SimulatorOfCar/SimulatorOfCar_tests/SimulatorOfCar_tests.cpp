#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../SimulatorOfCar/CCar.h"

SCENARIO("If create a car, it will be with turned off engine and speed = 0 and gear = 0 and direction is standing")
{
	Car car;
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("If create a car, you can't set gear and speed")
{
	Car car;
	REQUIRE(!car.IsTurnedOn());
	REQUIRE(!car.SetGear(1));
	REQUIRE(!car.SetSpeed(10));
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

SCENARIO("If create a car and turn on engine and set gear non-N or speed non-null, you can't turn it off")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.IsTurnedOn());
	car.SetSpeed(10);
	car.SetGear(0);
	REQUIRE(!car.TurnOffEngine());
	REQUIRE(car.IsTurnedOn());
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

SCENARIO("If turn on engine, you can set gear R or 1st without setting speed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.GetGear() == -1);
}

SCENARIO("If set gear R, you can set speed and get it with direction")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
}

SCENARIO("If set gear 1st, you can set speed and get it with direction")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
}

SCENARIO("If try set any gear except 1st and R, it will be failed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(!car.SetGear(2));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	REQUIRE(car.GetDirection() == Direction::STANDING_STILL);
}

SCENARIO("If set gear R with non-null speed, you can't set 1st gear")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(!car.SetGear(1));
	REQUIRE(car.GetGear() == -1);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
}

SCENARIO("If set some speed and set N gear, you can only decrease speed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(0));
	REQUIRE(!car.SetSpeed(30));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.GetSpeed() == 10);
}

SCENARIO("If set 1st gear, you can only set speed in range of 1st gear")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(!car.SetSpeed(40));
	REQUIRE(car.GetSpeed() == 20);
}

SCENARIO("If set any gear, you can only set non-negative speed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(!car.SetSpeed(-20));
	REQUIRE(car.GetSpeed() == 0);
}

SCENARIO("If set R gear and non-null speed, the direction is backward")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
}

SCENARIO("If try to set non-valid gear, it will be failed")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(!car.SetGear(-2));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(!car.SetGear(6));
	REQUIRE(car.GetGear() == 0);
}

SCENARIO("If set any speed, you can set gear if that speed in range of gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	REQUIRE(!car.SetGear(3));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(!car.SetGear(-1));
	REQUIRE(car.GetGear() == 1);
}

SCENARIO("If set R gear and any speed and set N gear, the direction is backward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(20);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
	car.SetGear(0);
	REQUIRE(car.GetDirection() == Direction::BACKWARD);
}

SCENARIO("If set 1st gear, you can set speed in its range")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(!car.SetSpeed(40));
	REQUIRE(car.SetSpeed(10));
}

SCENARIO("If set R gear, you can set speed in its range")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(!car.SetSpeed(40));
	REQUIRE(car.SetSpeed(10));
}

SCENARIO("If set 2nd gear, you can set speed in its range")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	REQUIRE(car.SetGear(2));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(!car.SetSpeed(0));
	REQUIRE(!car.SetSpeed(-1));
	REQUIRE(!car.SetSpeed(60));
	REQUIRE(car.SetSpeed(30));
}

SCENARIO("If set 5th gear, you can set speed = 150 and that is max")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetGear(2));
	REQUIRE(car.SetSpeed(50));
	REQUIRE(car.SetGear(3));
	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.SetGear(4));
	REQUIRE(car.SetSpeed(90));
	REQUIRE(car.SetGear(5));
	REQUIRE(car.SetSpeed(150));
	REQUIRE(!car.SetSpeed(160));
}