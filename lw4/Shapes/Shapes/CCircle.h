#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
	static const std::string NAME;

	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
		:ISolidShape(outlineColor, fillColor)
		, m_center(center)
		, m_radius(radius)
	{
		if (radius <= 0)
		{
			throw std::invalid_argument("Invalid radius: it must be positive");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetCenter() const;

	double GetRadius() const;

	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_center;
	double m_radius;
};