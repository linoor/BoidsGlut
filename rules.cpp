#include "boid.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

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

std::vector<double> rule2(std::vector<Boid> boids, Boid current) {
    const double distance_factor = 100.0;

    std::vector<double> c = {
        0.0,
        0.0,
        0.0
    };

    std::vector<Boid> others = get_others(boids, current);

    for (int i = 0; i < others.size(); i++) {
        Boid boid = others[i];
        double distance = boid.get_distance(current);

        if (distance < distance_factor) {
            std::vector<double> diff = {
                boid.get_x() - current.get_x(),
                boid.get_y() - current.get_y(),
                boid.get_z() - current.get_z()
            };

            c[0] -= diff[0];
            c[1] -= diff[1];
            c[2] -= diff[2];
        }
    }

    return c;
}

std::vector<double> avg_velocity(std::vector<Boid> boids) {
    std::vector<double> result = accumulate(
                      boids.begin(),
                      boids.end(),
                      std::vector<double> {0.0, 0.0, 0.0},
                      [](std::vector<double> res, Boid b) {
                       res[0] += b.get_vel_x();
                       res[1] += b.get_vel_y();
                       res[2] += b.get_vel_z();
                       return res;
                   });

    result[0] /= boids.size();
    result[1] /= boids.size();
    result[2] /= boids.size();

    return result;
}

std::vector<double> per_avg_velocity(std::vector<Boid> boids, Boid current) {
    return avg_velocity(get_others(boids, current));
}

std::vector<double> rule3(std::vector<Boid> boids, Boid current) {
    const int factor = 8;

    std::vector<double> result = per_avg_velocity(boids, current);
    std::cout << result[0] << std::endl;

    result[0] = (result[0] - current.get_vel_x()) / factor;
    result[1] = (result[1] - current.get_vel_y()) / factor;
    result[2] = (result[2] - current.get_vel_z()) / factor;

    return result;
}