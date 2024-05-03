#pragma once
#include "CPoint.h"
#include <iomanip>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) = 0;

	virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) = 0;

	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;

	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};