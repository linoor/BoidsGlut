void Boid::set_x(double x) {
        this->pos_x = x;
}
void Boid::set_y(double y) {
        this->pos_y = y;
}

void Boid::set_z(double z) {
        this->pos_z = z;
}

void Boid::set_vel_x(double vel_x) {
        this->vel_x = vel_x;
}

void Boid::set_vel_y(double vel_y) {
        this->vel_y = vel_y;
}

void Boid::set_vel_z(double vel_z) {
        this->vel_z = vel_z;
}

double Boid::get_vel_x() const {
        return this->vel_x;
}

double Boid::get_vel_y() const {
        return this->vel_y;
}

double Boid::get_vel_z() const {
        return this->vel_z;
}

double Boid::get_x() const {
        return pos_x;
}

double Boid::get_y() const {
        return pos_y;
}

double Boid::get_z() const {
        return pos_z;
}


std::vector<double> Boid::get_vector() {
        std::vector<double> result = {
            pos_x,
            pos_y,
            pos_z
        };
        return result;
}

bool Boid::operator==(const Boid& other) {
        return this->get_x() == other.get_x()
        && this->get_y() == other.get_y()
        && this->get_z() == other.get_z();
}

double Boid::get_distance(Boid boid) {
        double result = 0;
        std::vector<double> diffs = {
           this->get_x() - boid.get_x(),
           this->get_y() - boid.get_y(),
           this->get_z() - boid.get_z() 
        };

        for (int i = 0 ; i < diffs.size(); i++) {
            result += diffs[i]*diffs[i];
        }

        return sqrt(result);
}

Boid::Boid(double pos_x, double pos_y, double pos_z) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->pos_z = pos_z;
}

Boid::Boid(double pos_x, double pos_y, double pos_z, double vel_x, double vel_y, double vel_z) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->pos_z = pos_z;

        this->vel_x = vel_x;
        this->vel_y = vel_y;
        this->vel_z = vel_z;
}