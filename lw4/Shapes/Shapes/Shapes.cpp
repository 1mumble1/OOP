// Shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ShapeService.h"

int main()
{
	ShapeService shapeService;
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			continue;
		}

		shapeService.ConstructShape(line);

	}

	if (shapeService.GetMaxAreaShape() == nullptr)
	{
		return 0;
	}

	std::cout << "Shape with max area:\n" << shapeService.GetMaxAreaShape()->ToString() << std::endl;
	std::cout << "Shape with min perimeter:\n" << shapeService.GetMinPerimeterShape()->ToString() << std::endl;

	shapeService.DrawShapes();

	return 0;
}
