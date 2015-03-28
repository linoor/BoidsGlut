#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "boid.h"
#include <vector>
#include <array>
#include "rules.cpp"

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
