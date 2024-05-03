#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : public ISolidShape
{
public:
	static const std::string NAME;

	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
		:ISolidShape(outlineColor, fillColor)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
		double side12 = GetSide(vertex1, vertex2);
		double side23 = GetSide(vertex2, vertex3);
		double side31 = GetSide(vertex3, vertex1);

		if (side12 + side23 <= side31 ||
			side12 + side31 <= side23 ||
			side23 + side31 <= side12)
		{
			throw std::invalid_argument("Invalid arguments: in triangle every side must be bigger than summary of other two sides");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string ToString() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;

	CPoint GetVertex2() const;

	CPoint GetVertex3() const;

	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;

	double GetSide(const CPoint& vertex1, const CPoint& vertex2) const;
};