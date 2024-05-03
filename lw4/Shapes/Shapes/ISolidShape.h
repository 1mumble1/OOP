#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape(uint32_t outlineColor, uint32_t fillColor)
		:IShape(outlineColor)
		, m_fillColor(fillColor)
	{}

	virtual uint32_t GetFillColor() const = 0;

	virtual std::string ToString() const
	{
		std::stringstream ss;
		ss << IShape::ToString();
		ss << "FillColor: " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl;
		return ss.str();
	};

protected:
	uint32_t m_fillColor = 0;
};