// Shapes_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../Shapes/CPoint.h"
#include "../Shapes/IShape.h"
#include "../Shapes/ISolidShape.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CCircle.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/ShapeCreator.h"
#include "../Shapes/ShapeService.h"

#define _USE_MATH_DEFINES
#include <math.h>

const uint32_t OUTLINE_COLOR = 0x012345;
const uint32_t FILL_COLOR = 0xABCDEF;
//TODO	create shapes (invalid and valid), check ToString(), parse lines to create shapes, get max area and min perimeter

SCENARIO("If create line segment with points (0;0) and (0;1), we get area = 0, perimeter = 1")
{
	CPoint start = { 0, 0 };
	CPoint end = { 0, 1 };
	CLineSegment line = { start, end, OUTLINE_COLOR };
	REQUIRE(line.GetArea() == 0);
	REQUIRE(line.GetPerimeter() == 1);
}

SCENARIO("If create line segment with points (0;0) and (0;0), we get area = 0, perimeter = 0")
{
	CLineSegment line = { {0, 0}, {0, 0}, OUTLINE_COLOR };
	REQUIRE(line.GetArea() == 0);
	REQUIRE(line.GetPerimeter() == 0);
}

SCENARIO("If create circle with radius = 5, we get area = 0, perimeter = 0")
{
	CCircle circle = { {0, 0}, 5, OUTLINE_COLOR, FILL_COLOR };
	REQUIRE(circle.GetArea() == M_PI * 5 * 5);
	REQUIRE(circle.GetPerimeter() == 2 * M_PI * 5);
}