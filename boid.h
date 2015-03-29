#ifndef BOID_H
#define BOID_H

class Boid {

private:
    
    double pos_x;
    double pos_y;
    double pos_z;

public:
    
    void set_x(double x) {
        this->pos_x = x;
    }
    void set_y(double y) {
        this->pos_y = y;
    }

    void set_z(double z) {
        this->pos_z = z;
    }

    double get_x() const {
        return pos_x;
    }

    double get_y() const {
        return pos_y;
    }

    double get_z() const {
        return pos_z;
    }

    bool operator==(const Boid& other) {
        return this->get_x() == other.get_x()
        && this->get_y() == other.get_y()
        && this->get_z() == other.get_z();
    }

    Boid(double pos_x, double pos_y, double pos_z) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->pos_z = pos_z;
    }

};

#endif
