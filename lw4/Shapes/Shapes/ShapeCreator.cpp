#include "ShapeCreator.h"
#include <sstream>
#include <iostream>

std::shared_ptr<IShape> ShapeCreator::CreateShape(const std::string& line)
{
    std::istringstream iss(line);
    std::string nameOfShape;
    iss >> nameOfShape;

    if (nameOfShape == CLineSegment::NAME)
    {
        return ShapeCreator::CreateLineSegment(iss);
    }
    else if (nameOfShape == CCircle::NAME)
    {
        return ShapeCreator::CreateCircle(iss);
    }
    else if (nameOfShape == CTriangle::NAME)
    {
        return ShapeCreator::CreateTriangle(iss);
    }
    else if (nameOfShape == CRectangle::NAME)
    {
        return ShapeCreator::CreateRectangle(iss);
    }

    return nullptr;
}


std::shared_ptr<CLineSegment> ShapeCreator::CreateLineSegment(std::istringstream& iss)
{
    double startX, startY, endX, endY;
    if (!(iss >> startX >> endX >> startY >> endY))
    {
        std::cout << "Invalid line segment coordinates" << std::endl;
        return nullptr;
    }

    CPoint startPoint = { startX, endX };
    CPoint endPoint = { startY, endY };

    uint32_t outlineColor;
    if (!(iss >> std::hex >> outlineColor))
    {
        std::cout << "Invalid color value" << std::endl;
        return nullptr;
    }

    return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<CCircle> ShapeCreator::CreateCircle(std::istringstream& iss)
{
    double centerX, centerY, radius;
    if (!(iss >> centerX >> centerY >> radius))
    {
        std::cout << "Invalid circle coordinates or sizes" << std::endl;
        return nullptr;
    }

    CPoint center = { centerX, centerY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

std::shared_ptr<CRectangle> ShapeCreator::CreateRectangle(std::istringstream& iss)
{
    double leftTopX, leftTopY, width, height;
    if (!(iss >> leftTopX >> leftTopY >> width >> height))
    {
        std::cout << "Invalid rectangle coordinates or sizes" << std::endl;
        return nullptr;
    }

    CPoint leftTop = { leftTopX, leftTopY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> ShapeCreator::CreateTriangle(std::istringstream& iss)
{
    double vertex1X, vertex1Y;
    double vertex2X, vertex2Y;
    double vertex3X, vertex3Y;
    if (!(iss >> vertex1X >> vertex1Y >>
        vertex2X >> vertex2Y >>
        vertex3X >> vertex3Y))
    {
        std::cout << "Invalid triangle coordinates" << std::endl;
        return nullptr;
    }

    CPoint vertex1 = { vertex1X, vertex1Y };
    CPoint vertex2 = { vertex2X, vertex2Y };
    CPoint vertex3 = { vertex3X, vertex3Y };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        std::cout << "Invalid color values" << std::endl;
        return nullptr;
    }

    return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}