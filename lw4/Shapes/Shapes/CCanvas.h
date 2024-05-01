#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {};

	void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor);

	void FillPolygon(std::vector<CPoint> points, uint32_t lineColor, uint32_t fillColor);

	void DrawCircle(CPoint center, double radius, uint32_t lineColor);

	void FillCircle(CPoint center, double radius, uint32_t fillColor);

private:
	std::shared_ptr<sf::RenderWindow> m_window;
};