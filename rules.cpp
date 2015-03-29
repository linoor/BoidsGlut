#include "boid.h"
#include <vector>
#include <algorithm>

std::vector<double> center_of_mass(std::vector<Boid> boids) {

    std::vector<double> results = {
        0.0,
        0.0,
        0.0
    };

    for (int i = 0; i < boids.size(); i++) {
        Boid boid = boids[i];

        results[0] += boid.get_x();
        results[1] += boid.get_y();
        results[2] += boid.get_z();
    }

    const int N = boids.size();
    for (int i = 0; i < 3; i++) {
        results[i] /= N;
    }

    return results;
}

std::vector<Boid> get_others(std::vector<Boid> boids, Boid current) {
    std::vector<Boid> others = boids;
    // removing current boid from the vector
    others.erase(std::remove(others.begin(), others.end(), current), others.end());

    return others;
}

std::vector<double> perceived_center(std::vector<Boid> boids, Boid current) {
    return center_of_mass(get_others(boids, current));
}

// returns offset vector for a specific boid (moves the boid 1% to the perceived center)
std::vector<double> rule1(std::vector<Boid> boids, Boid current) {
    const double factor = 0.01;

    std::vector<double> pc = perceived_center(boids, current);

    pc[0] -= current.get_x();
    pc[1] -= current.get_y();
    pc[2] -= current.get_z();

    for (int i = 0; i < pc.size(); i++) {
        pc[i] *= factor;
    }

    return pc;
}