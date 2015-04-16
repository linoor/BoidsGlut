#include <GL/glut.h>
#include "boid.h"
#include "boid.cpp"
#include <iostream>
#include "rules.cpp"

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };

std::vector<Boid> boids = {
  Boid(1,1,1,0.1,0.1,0),
  Boid(0,5,1,0.1,0.1,0),
  Boid(-1,0,1,0.1,0.1,0),
  Boid(-2,2,1,0.1,0.1,0)
};

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // displaying the boids
  for (int i = 0; i < boids.size(); i++) {
    Boid boid = boids[i];
    boid.draw();
  }

  glutSwapBuffers();
}

void init(void) {
  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);
  glMatrixMode(GL_MODELVIEW);

  // camera 
  gluLookAt(0.0, 0.0, 10.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
}

void update(int value) {

  // updating boids positions
  for (int i = 0; i < boids.size(); i++) {
    Boid boid = boids[i]; 

    std::vector<double> rule_cohesion = rule1(boids, boid);
    std::vector<double> rule_separation = rule2(boids, boid);
    std::vector<double> rule_aligment = rule3(boids, boid);

    for (int i = 0; i < 3; i++) {
      boid.set_vel_x(boid.get_vel_x() + rule_cohesion[0]);
      boid.set_vel_y(boid.get_vel_y() + rule_cohesion[1]);
      boid.set_vel_z(boid.get_vel_z() + rule_cohesion[2]);

      boid.set_vel_x(boid.get_vel_x() + rule_separation[0]);
      boid.set_vel_y(boid.get_vel_y() + rule_separation[1]);
      boid.set_vel_z(boid.get_vel_z() + rule_separation[2]);

      boid.set_vel_x(boid.get_vel_x() + rule_aligment[0]);
      boid.set_vel_y(boid.get_vel_y() + rule_aligment[1]);
      boid.set_vel_z(boid.get_vel_z() + rule_aligment[2]);
    }

    boid.set_x(boid.get_x() + boid.get_vel_x());
    boid.set_y(boid.get_y() + boid.get_vel_y());
    boid.set_z(boid.get_z() + boid.get_vel_z());
    boids[i] = boid;
}

  glutPostRedisplay();
  glutTimerFunc(50, update, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700, 800);
  glutCreateWindow("Boids algorithm");
  glutDisplayFunc(display);
  glutTimerFunc(1, update, 0);
  init();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}