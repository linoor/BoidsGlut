#ifndef BOID_H
#define BOID_H

#include <vector>

class Boid {

private:
    
    double pos_x;
    double pos_y;
    double pos_z;

    double vel_x;
    double vel_y;
    double vel_z;

public:
    
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
    void set_vel_x(double vel_x);
    void set_vel_y(double vel_y);
    void set_vel_z(double vel_z);
    double get_vel_x() const;
    double get_vel_y() const;
    double get_vel_z() const;
    double get_x() const;
    double get_y() const;
    double get_z() const;

    std::vector<double> get_vector();
    bool operator==(const Boid& other);
    double get_distance(Boid boid);
    Boid(double pos_x, double pos_y, double pos_z);
    Boid(double pos_x, double pos_y, double pos_z, double vel_x, double vel_y, double vel_z);

    void draw();
};

#endif
