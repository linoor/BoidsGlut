#ifndef BOID_H
#define BOID_H

class Boid {

public:
    void set_x(double x) {
        this->pos_x = x;
    }
    void set_y(double y) {
        this->pos_y = y;
    }

    Boid(double pos_x, double pos_y, double pos_z) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->pos_z = pos_z;
    }
private:
    
    double pos_x;
    double pos_y;
    double pos_z;


};

#endif
