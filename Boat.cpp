#include "Boat.h"
#include <queue>
#include <limits>
#include <map>
#include <algorithm>

Boat::Boat(TerrainMap& m, std::string name, Point start, Point finish)
    : Path(m, name, start, finish) {}

bool Boat::find() {
    // Priority queue for Dijkstra's algorithm
    std::priority_queue<
        std::pair<double, Point>,
        std::vector<std::pair<double, Point>>,
        std::greater<std::pair<double, Point>>
    > pq;

    // 2D vectors for distances and previous points
    std::vector<std::vector<double>> distances(map.nx, std::vector<double>(map.ny, std::numeric_limits<double>::infinity()));
    std::vector<std::vector<Point>> previous(map.nx, std::vector<Point>(map.ny, {-1, -1}));

    // Initialize start point
    distances[start.x][start.y] = 0.0;
    pq.push({0.0, start});

    // Directions for 8 possible movements (including diagonals)
    const std::vector<Point> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}
    };

    while (!pq.empty()) {
        auto current_pair = pq.top();
        pq.pop();

        double current_dist = current_pair.first;
        Point current = current_pair.second;

        // If we reached the finish, exit loop
        if (current == finish) break;

        for (const auto& dir : directions) {
            Point neighbor = current + dir;
            if (!map.validCoords(neighbor)) continue;

            // Elevation constraint: Boat can only travel on water (altitude < 0)
            int neighbor_alt = map.alt(neighbor);
            if (neighbor_alt >= 0 && neighbor != start && neighbor != finish) continue;

            double new_dist = current_dist + dir.length();

            if (new_dist < distances[neighbor.x][neighbor.y]) {
                distances[neighbor.x][neighbor.y] = new_dist;
                previous[neighbor.x][neighbor.y] = current;
                pq.push({new_dist, neighbor});
            }
        }
    }

    // If the finish point is unreachable
    if (distances[finish.x][finish.y] == std::numeric_limits<double>::infinity()) {
        return false;
    }

    // Reconstruct path from finish to start
    Point step = finish;
    while (step != start) {
        path.push_back(step);
        step = previous[step.x][step.y];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return true;
}
