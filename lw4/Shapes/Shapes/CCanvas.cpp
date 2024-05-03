#include "CCanvas.h"
#include <sstream>
#include <iostream>

void HexToRGB(uint32_t color, unsigned int& r, unsigned int& g, unsigned int& b)
{
    std::stringstream ss;
    ss << std::hex << color;
    std::string res(ss.str());

    while (res.length() < 6)
    {
        res.insert(0, "0");
    }

    std::stringstream ss1(res.substr(0, 2));
    ss1 >> std::hex >> r;
    std::stringstream ss2(res.substr(2, 2));
    ss2 >> std::hex >> g;
    std::stringstream ss3(res.substr(4, 2));
    ss3 >> std::hex >> b;
}

void CCanvas::DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(static_cast<float>(startPoint.m_x), static_cast<float>(startPoint.m_y));
    line[1].position = sf::Vector2f(static_cast<float>(endPoint.m_x), static_cast<float>(endPoint.m_y));

    unsigned int r, g, b;
    HexToRGB(lineColor, r, g, b);
    line[0].color = sf::Color(r, g, b);
    line[1].color = sf::Color(r, g, b);

    m_window->draw(line);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
    if (points.empty())
    {
        return;
    }

    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());

    for (size_t i = 0; i < points.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].m_x), static_cast<float>(points[i].m_y)));
    }

    unsigned int r, g, b;
    HexToRGB(fillColor, r, g, b);
    polygon.setFillColor(sf::Color(r, g, b));

    m_window->draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.m_x), static_cast<float>(center.m_y));
    circle.setFillColor(sf::Color::Transparent);

    unsigned int r, g, b;
    HexToRGB(lineColor, r, g, b);
    circle.setOutlineColor(sf::Color(r, g, b));
    circle.setOutlineThickness(2);

    m_window->draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.m_x), static_cast<float>(center.m_y));

    unsigned int r, g, b;
    HexToRGB(fillColor, r, g, b);
    circle.setFillColor(sf::Color(r, g, b));
    circle.setOutlineColor(sf::Color::Transparent);

    m_window->draw(circle);
}