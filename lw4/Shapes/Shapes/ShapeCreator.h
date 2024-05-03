#pragma once

#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"

class ShapeCreator
{
public:
    static std::shared_ptr<IShape> CreateShape(const std::string& line);

private:
    static std::shared_ptr<CLineSegment> CreateLineSegment(std::istringstream& iss);

    static std::shared_ptr<CRectangle> CreateRectangle(std::istringstream& iss);

    static std::shared_ptr<CTriangle> CreateTriangle(std::istringstream& iss);

    static std::shared_ptr<CCircle> CreateCircle(std::istringstream& iss);
};