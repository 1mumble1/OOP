#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : public ISolidShape
{
public:
	static const std::string NAME;

	CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
		:ISolidShape(outlineColor, fillColor)
		,m_leftTop(leftTop)
		,m_width(width)
		,m_height(height)
	{
		if (width <= 0 || height <= 0)
		{
			throw std::invalid_argument("Invalid sizes: width and height must be positive");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;

	CPoint GetRightBottom() const;

	double GetWidth() const;

	double GetHeight() const;

	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_leftTop;
	double m_width, m_height;
};