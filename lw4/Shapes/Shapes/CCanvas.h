#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {};

	void DrawLine(CPoint startPoint, CPoint endPoint, uint32_t lineColor) override;

	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;

	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;

	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;

private:
	std::shared_ptr<sf::RenderWindow> m_window;
};