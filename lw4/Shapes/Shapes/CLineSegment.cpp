#include "CLineSegment.h"
#include <cmath>

const std::string CLineSegment::NAME = "line_segment";

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return std::sqrt(std::pow(m_startPoint.m_x - m_endPoint.m_x, 2) + std::pow(m_startPoint.m_y - m_endPoint.m_y, 2));
}

std::string CLineSegment::ToString() const
{
    std::stringstream ss;
    ss << "Name: line segment" << std::endl;
    ss << IShape::ToString();
    ss << "Start Point: (" << m_startPoint.m_x << "; " << m_startPoint.m_y << ")" << std::endl;
    ss << "End Point: (" << m_endPoint.m_x << "; " << m_endPoint.m_y << ")" << std::endl;
    ss << "Length: " << CLineSegment::GetPerimeter() << std::endl;
    return ss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

void CLineSegment::Draw(std::shared_ptr<ICanvas> canvas)
{
    canvas->DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}