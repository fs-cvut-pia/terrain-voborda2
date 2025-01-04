#include "Airplane.h"

Airplane::Airplane(TerrainMap& m, std::string name, Point start, Point finish)
    : Path(m, name, start, finish) {}

bool Airplane::find() {
    // Bresenham's line algorithm
    int x1 = start.x, y1 = start.y;
    int x2 = finish.x, y2 = finish.y;

    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    path.clear();  // Clear any existing path data
    path.push_back(Point(x1, y1));

    while (x1 != x2 || y1 != y2) {
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
        path.push_back(Point(x1, y1));
    }

    return true;  // Path successfully generated
}