#pragma once

#include <vector>
#include "ShapeCreator.h"
#include "CCanvas.h"

class ShapeService
{
public:
    void ConstructShape(const std::string& line);

    std::shared_ptr<IShape> GetMaxAreaShape() const;

    std::shared_ptr<IShape> GetMinPerimeterShape() const;

    void DrawShapes();

private:
    const int WIDTH_WINDOW = 1500;
    const int HEIGHT_WINDOW = 900;
    const std::string TITLE_WINDOW = "Window";

    std::vector<std::shared_ptr<IShape>> m_shapes = {};
    std::shared_ptr<ICanvas> m_canvas;
};