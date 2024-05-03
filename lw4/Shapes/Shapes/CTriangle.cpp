#include "CTriangle.h"
#include <cmath>

const std::string CTriangle::NAME = "triangle";

double CTriangle::GetSide(const CPoint& vertex1, const CPoint& vertex2) const
{
    return std::sqrt(std::pow(vertex1.m_x - vertex2.m_x, 2) + std::pow(vertex1.m_y - vertex2.m_y, 2));
}

double CTriangle::GetArea() const
{
    return 0, 5 * abs(
        (m_vertex1.m_x - m_vertex3.m_x) *
        (m_vertex2.m_y - m_vertex3.m_y) -
        (m_vertex2.m_x - m_vertex3.m_x) *
        (m_vertex1.m_y - m_vertex3.m_y));
}

double CTriangle::GetPerimeter() const
{
    return CTriangle::GetSide(m_vertex1, m_vertex2) +
        CTriangle::GetSide(m_vertex2, m_vertex3) +
        CTriangle::GetSide(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString() const
{
    std::stringstream ss;
    ss << "Name: triangle" << std::endl;
    ss << ISolidShape::ToString();
    ss << "Vertex ¹1: (" << m_vertex1.m_x << "; " << m_vertex1.m_y << ")" << std::endl;
    ss << "Vertex ¹2: (" << m_vertex2.m_x << "; " << m_vertex2.m_y << ")" << std::endl;
    ss << "Vertex ¹3: (" << m_vertex3.m_x << "; " << m_vertex3.m_y << ")" << std::endl;
    ss << "Side (1)-(2): " << GetSide(m_vertex1, m_vertex2) << std::endl;
    ss << "Side (2)-(3): " << GetSide(m_vertex2, m_vertex3) << std::endl;
    ss << "Side (3)-(1): " << GetSide(m_vertex3, m_vertex1) << std::endl;
    return ss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}

void CTriangle::Draw(std::shared_ptr<ICanvas> canvas)
{
    std::vector<CPoint> points = { m_vertex1, m_vertex2, m_vertex3 };

    canvas->FillPolygon(points, m_fillColor);
    canvas->DrawLine(m_vertex1, m_vertex2, m_outlineColor);
    canvas->DrawLine(m_vertex2, m_vertex3, m_outlineColor);
    canvas->DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}