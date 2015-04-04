#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "boid.h"
#include <vector>
#include <array>
#include "rules.cpp"
#include <iostream>

/* example testing code
unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
*/

// Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.

TEST_CASE("Test calculating center of mass") {
    std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0),
        Boid(10.0, 20.0, 30.0),
        Boid(30.0, 20.0, 30.0)
    };

    std::vector<double> boids_results = center_of_mass(boids);
    REQUIRE(boids_results[0] == 20.0);
    REQUIRE(boids_results[1] == 20.0);
    REQUIRE(boids_results[2] == 30.0);
}

TEST_CASE("Calculate perceived center of mass") {
    std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0),
        Boid(10.0, 20.0, 30.0),
        Boid(10.0, 40.0, 60.0)
    };

    std::vector<double> boids_results_perceived = perceived_center(boids, boids[0]);
    REQUIRE(boids_results_perceived[0] == 10.0);
    REQUIRE(boids_results_perceived[1] == 30.0);
    REQUIRE(boids_results_perceived[2] == 45.0);
}

TEST_CASE("Calculate vector offset for one boid (first rule)") {
     std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0),
        Boid(10.0, 20.0, 30.0),
        Boid(10.0, 40.0, 60.0)
    };

    std::vector<double> offset_vector = rule1(boids, boids[0]);
    REQUIRE(offset_vector[0] == -0.10);
    REQUIRE(offset_vector[1] == 0.10);
    REQUIRE(offset_vector[2] == 0.15);
}

TEST_CASE("get distance test") {
    Boid boid1 = Boid(20.0, 20.0, 30.0);
    Boid boid2 = Boid(10.0, 20.0, 30.0);

    double result = boid1.get_distance(boid2);
    REQUIRE(result == 10.0);
}

TEST_CASE("Rule 2: Boids try to keep a small distance away from other objects (including other boids)") {
    std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0),
        Boid(10.0, 20.0, 30.0)
        // Boid(10.0, 40.0, 60.0)
    };

    std::vector<double> c = rule2(boids, boids[0]);

    // c = [0.0, 0.0, 0.0]
    // b - bj = [-10.0, 0.0, 0.0]
    // c = [10.0, 0.0, 0.0]
    // b - bj = [-10.0, 20.0, 0.0]
    // c = [20.0, -20.0, 0.0]
    REQUIRE(c[0] == 10.0);
    REQUIRE(c[1] == 0.0);
    REQUIRE(c[2] == 0.0);

    std::vector<Boid> boids2 = {
        Boid(20.0, 20.0, 30.0),
        Boid(10.0, 20.0, 30.0),
        Boid(10.0, 40.0, 30.0)
    };

    std::vector<double> c2 = rule2(boids2, boids[0]);

    REQUIRE(c2[0] == 20.0);
    REQUIRE(c2[1] == -20.0);
    REQUIRE(c2[2] == 0.0);
}

TEST_CASE("Calculate average velocity") {
    std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0, 10.0, 10.0, 10.0),
        Boid(10.0, 20.0, 30.0, 50.0, 70.0, 40.0),
        Boid(30.0, 20.0, 30.0, 30.0, 40.0, 10.0)
    };

    std::vector<double> vel_results = avg_velocity(boids); 
    REQUIRE(vel_results[0] == 30.0);
    REQUIRE(vel_results[1] == 40.0);
    REQUIRE(vel_results[2] == 20.0);
}

TEST_CASE("Calculating perceived velocity") {
    std::vector<Boid> boids = {
        Boid(20.0, 20.0, 30.0, 10.0, 10.0, 10.0),
        Boid(10.0, 20.0, 30.0, 50.0, 70.0, 50.0),
        Boid(30.0, 20.0, 30.0, 30.0, 50.0, 20.0)
    };

    std::vector<double> vel_results = per_avg_velocity(boids, boids[0]); 
    REQUIRE(vel_results[0] == 40.0);
    REQUIRE(vel_results[1] == 60.0);
    REQUIRE(vel_results[2] == 35.0);
}

// TEST_CASE("Rule 3") {
//     std::vector<Boid> boids = {
//         Boid(20.0, 20.0, 30.0, 8.0),
//         Boid(10.0, 20.0, 30.0, 50.0),
//         Boid(30.0, 20.0, 30.0, 30.0)
//     };

//     double offset_vel = rule3(boids, boids[0]);
//     REQUIRE(offset_vel == 4.0);
// }