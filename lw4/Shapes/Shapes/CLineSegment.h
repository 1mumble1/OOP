#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CLineSegment : public IShape
{
public:
	static const std::string NAME;

	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
		:IShape(outlineColor)
		,m_startPoint(startPoint)
		,m_endPoint(endPoint)
	{}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	CPoint GetStartPoint() const;

	CPoint GetEndPoint() const;

	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_startPoint, m_endPoint;
};