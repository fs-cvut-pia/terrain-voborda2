#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "Path.h"

class Airplane : public Path {
public:
    Airplane(TerrainMap& m, std::string name, Point start, Point finish);

    bool find() override;  // Hledání nejkratší cesty
};

#endif