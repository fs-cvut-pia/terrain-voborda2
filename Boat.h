#ifndef BOAT_H
#define BOAT_H

#include "Path.h"

class Boat : public Path {
public:
    Boat(TerrainMap& m, std::string name, Point start, Point finish);

    bool find() override; // Implements Dijkstra's algorithm with elevation constraint for the Boat path
};

#endif