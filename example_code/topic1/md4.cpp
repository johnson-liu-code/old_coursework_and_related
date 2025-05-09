// Molecular Dynamics Simulation of Argon Atoms: OpenGL Visualization

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#ifdef __APPLE__
#   include <GLUT/glut.h>
#else
#   include <GL/freeglut.h>
#endif

// simulation parameters
int N;                    // number of particles
double rho;               // density (number per unit volume)
double T;                 // temperature
double dt;                // integration time step

void getInput() {
    cout << "Molecular Dynamics of 3D Lennard-Jones Gas" << endl
         << "------------------------------------------" << endl;
    cout << "Enter desired number of particles N = ";
    cin >> N;
    cout << "Enter density (particles/unit vol) rho = ";
    cin >> rho;
    cout << "Enter desired temperature T = ";
    cin >> T;
    cout << "Enter desired integration time step dt = ";
    cin >> dt;
}

double L;                 // will be computed from N and rho

double **r, **v, **a;     // positions, velocities, accelerations

// declare functions repeated from md2.cpp
void initPositions();
void initVelocities();
void rescaleVelocities();
double instantaneousTemperature();

// variables to implement Verlet's neighbor list
double rCutOff = 2.5;     // cut-off on Lennard-Jones potential and force
double rMax = 3.3;        // maximum separation to include in pair list
int nPairs;               // number of pairs currently in pair list
int **pairList;           // the list of pair indices (i,j)
double **drPair;          // vector separations of each pair (i,j)
double *rSqdPair;         // squared separation of each pair (i,j)
int updateInterval = 10;  // number of time steps between updates of pair list

// declare functions repeated from md3.cpp
void initialize();
void computeSeparation(int, int, double[], double&);
void updatePairList();
void updatePairSeparations();
void computeAccelerations();
void velocityVerlet(double dt);

int step;                 // keeps track of integration step number
int displayInterval = 5;  // display molecules every so many steps

void makeMolecules();     // this function re-draws the molecules

void takeStep() {
    velocityVerlet(dt);
    ++step;
    if (step % 200 == 0)
        rescaleVelocities();
    if (step % updateInterval == 0) {
        updatePairList();
        updatePairSeparations();
    }
    if (step % displayInterval == 0) {
        makeMolecules();
        glutPostRedisplay();
    }
}

const double pi = 4 * atan(1.0);
double radius = 0.5;                      // radius of molecule
double minExtent[3], maxExtent[3];        // extent of system volume
int xWindowSize = 640, yWindowSize = 640; // window size in screen pixels
GLdouble aspectRatio;                     // window aspect ratio
GLdouble fovy, nearClip, farClip;         // variables for 3D projection
GLdouble eye[3], center[3], up[3];        // more projection variables
GLuint sphereID, configID;                // display list ID numbers
int phi, theta;                           // to rotate system using arrow keys
int angle = 5;                            // rotation angle in degrees

void makeSphere(GLuint listID, double radius) {
    int nTheta = 9;                       // number of polar angle slices
    int nPhi = 18;                        // number of azimuthal angle slices
    glNewList(listID, GL_COMPILE);
        glutSolidSphere(radius, nPhi, nTheta);
    glEndList();
}

void makeMolecules() {
    glNewList(configID, GL_COMPILE);
    glColor3f(0.0, 0.0, 1.0);             // color the molecules blue
    glPushMatrix();
    glRotated(phi, 0, 1, 0);              // rotate about y axis
    glPushMatrix();
    glRotated(theta, 1, 0, 0);            // rotate about x axis
    for (int i = 0; i < N; i++) {
        glPushMatrix();
        glTranslated(r[i][0] - L/2, r[i][1] - L/2, r[i][2] - L/2);
        glCallList(sphereID);
        glPopMatrix();
    }
    glColor3ub(255, 255, 255);            // white
    glutWireCube(L);                      // cubical system volume
    glPopMatrix();
    glPopMatrix();
    glEndList();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);
    glCallList(configID);                 // draw molecules
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    aspectRatio = w / double(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspectRatio, nearClip, farClip);
    glMatrixMode(GL_MODELVIEW);
}

void initView(double *minExtent, double *maxExtent) {

    // use a single light source to illuminate the scene
    GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {0.5, 0.5, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);              // use single light number 0
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    // compute the distance scale of the system
    double difExtent[3];
    for (int i = 0; i < 3; i++)
        difExtent[i] = maxExtent[i] - minExtent[i];
    double dist = 0;
    for (int i = 0; i < 3; i++)
        dist += difExtent[i] * difExtent[i];
    dist = sqrt(dist);

    // locate the center of the system, camera position, and orientation
    for (int i = 0; i < 3; i++)
        center[i] = minExtent[i] + difExtent[i] / 2;
    eye[0] = center[0];
    eye[1] = center[1];
    eye[2] = center[2] + dist;        // along z axis is towards viewer
    up[0] = 0;
    up[1] = 1;                        // y axis is up
    up[2] = 0;

    // set up clipping planes, field of view angle in degrees in y direction
    nearClip = (dist - difExtent[2] / 2) / 2;
    farClip = 2 * (dist + difExtent[2] / 2);
    fovy = difExtent[1] / (dist - difExtent[2] / 2) / 2;
    fovy = 2 * atan(fovy) / pi * 180;
    fovy *= 1.2;
}

void special(int key, int x, int y) {
    switch(key) {
      case GLUT_KEY_LEFT:   phi = (phi - angle) % 360;      break;
      case GLUT_KEY_RIGHT:  phi = (phi + angle) % 360;      break;
      case GLUT_KEY_UP:     theta = (theta - angle) % 360;  break;
      case GLUT_KEY_DOWN:   theta = (theta + angle) % 360;  break;
      default: break;
    }
}

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);

    getInput();
    initialize();
    updatePairList();
    updatePairSeparations();
    computeAccelerations();
    dt = 0.01;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(xWindowSize, yWindowSize);
    glutCreateWindow("Molecular Dynamics of Lennard-Jones Gas");

    for (int i = 0; i < 3; i++) {
        minExtent[i] = -L/2;
        maxExtent[i] = L/2;
    }
    initView(minExtent, maxExtent);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(takeStep);
    glutSpecialFunc(special);

    sphereID = glGenLists(1);
    makeSphere(sphereID, radius);
    configID = glGenLists(1);
    makeMolecules();

    glutMainLoop();
}

void initialize() {
    r = new double* [N];
    v = new double* [N];
    a = new double* [N];
    for (int i = 0; i < N; i++) {
        r[i] = new double [3];
        v[i] = new double [3];
        a[i] = new double [3];
    }
    initPositions();
    initVelocities();

    // allocate memory for neighbor list variables
    nPairs = N * (N - 1) / 2;
    pairList = new int* [nPairs];
    drPair = new double* [nPairs];
    for (int p = 0; p < nPairs; p++) {
        pairList[p] = new int [2];      // to store indices i and j
        drPair[p] = new double [3];     // to store components x,y,z
    }
    rSqdPair = new double [nPairs];
}

void computeSeparation (int i, int j, double dr[], double& rSqd) {

    // find separation using closest image convention
    rSqd = 0;
    for (int d = 0; d < 3; d++) {
        dr[d] = r[i][d] - r[j][d];
        if (dr[d] >= 0.5*L)
            dr[d] -= L;
        if (dr[d] < -0.5*L)
            dr[d] += L;
        rSqd += dr[d]*dr[d];
    }
}

void updatePairList() {
    nPairs = 0;
    double dr[3];
    for (int i = 0; i < N-1; i++)               // all distinct pairs
        for (int j = i+1; j < N; j++) {         // of particles i,j
            double rSqd;
            computeSeparation(i, j, dr, rSqd);
            if (rSqd < rMax*rMax) {
                pairList[nPairs][0] = i;
                pairList[nPairs][1] = j;
                ++nPairs;
            }
        }
}

void updatePairSeparations() {
    double dr[3];
    for (int p = 0; p < nPairs; p++) {
        int i = pairList[p][0];
        int j = pairList[p][1];
        double rSqd;
        computeSeparation(i, j, dr, rSqd);
        for (int d = 0; d < 3; d++)
            drPair[p][d] = dr[d];
        rSqdPair[p] = rSqd;
    }
}

void computeAccelerations() {

    for (int i = 0; i < N; i++)          // set all accelerations to zero
        for (int k = 0; k < 3; k++)
            a[i][k] = 0;

    for (int p = 0; p < nPairs; p++) {
        int i = pairList[p][0];
        int j = pairList[p][1];
        if (rSqdPair[p] < rCutOff*rCutOff) {
            double r2Inv = 1 / rSqdPair[p];
            double r6Inv = r2Inv*r2Inv*r2Inv;
            double f = 24*r2Inv*r6Inv*(2*r6Inv - 1);
            for (int d = 0; d < 3; d++) {
                a[i][d] += f * drPair[p][d];
                a[j][d] -= f * drPair[p][d];
            }
        }
    }
}

void velocityVerlet(double dt) {
    // assume accelerations have been computed
    for (int i = 0; i < N; i++)
        for (int k = 0; k < 3; k++) {
            r[i][k] += v[i][k] * dt + 0.5 * a[i][k] * dt * dt;

            // use periodic boundary conditions
            if (r[i][k] < 0)
                r[i][k] += L;
            if (r[i][k] >= L)
                r[i][k] -= L;
            v[i][k] += 0.5 * a[i][k] * dt;
        }
    updatePairSeparations();
    computeAccelerations();
    for (int i = 0; i < N; i++)
        for (int k = 0; k < 3; k++)
            v[i][k] += 0.5 * a[i][k] * dt;
}

void initPositions() {

    // compute side of cube from number of particles and number density
    L = pow(N / rho, 1.0/3);

    // find M large enough to fit N atoms on an fcc lattice
    int M = 1;
    while (4 * M * M * M < N)
        ++M;
    double a = L / M;           // lattice constant of conventional cell

    // 4 atomic positions in fcc unit cell
    double xCell[4] = {0.25, 0.75, 0.75, 0.25};
    double yCell[4] = {0.25, 0.75, 0.25, 0.75};
    double zCell[4] = {0.25, 0.25, 0.75, 0.75};

    int n = 0;                  // atoms placed so far
    for (int x = 0; x < M; x++)
        for (int y = 0; y < M; y++)
            for (int z = 0; z < M; z++)
                for (int k = 0; k < 4; k++)
                    if (n < N) {
                        r[n][0] = (x + xCell[k]) * a;
                        r[n][1] = (y + yCell[k]) * a;
                        r[n][2] = (z + zCell[k]) * a;
                        ++n;
                    }
}

double gasdev () {
     static bool available = false;
     static double gset;
     double fac, rsq, v1, v2;
     if (!available) {
          do {
               v1 = 2.0 * rand() / double(RAND_MAX) - 1.0;
               v2 = 2.0 * rand() / double(RAND_MAX) - 1.0;
               rsq = v1 * v1 + v2 * v2;
          } while (rsq >= 1.0 || rsq == 0.0);
          fac = sqrt(-2.0 * log(rsq) / rsq);
          gset = v1 * fac;
          available = true;
          return v2*fac;
     } else {
          available = false;
          return gset;
     }
}

void initVelocities() {

    // Gaussian with unit variance
    for (int n = 0; n < N; n++)
        for (int i = 0; i < 3; i++)
            v[n][i] = gasdev();
    // Adjust velocities so center-of-mass velocity is zero
    double vCM[3] = {0, 0, 0};
    for (int n = 0; n < N; n++)
        for (int i = 0; i < 3; i++)
            vCM[i] += v[n][i];
    for (int i = 0; i < 3; i++)
        vCM[i] /= N;
    for (int n = 0; n < N; n++)
        for (int i = 0; i < 3; i++)
            v[n][i] -= vCM[i];

    // Rescale velocities to get the desired instantaneous temperature
    rescaleVelocities();
}

void rescaleVelocities() {
    double vSqdSum = 0;
    for (int n = 0; n < N; n++)
        for (int i = 0; i < 3; i++)
            vSqdSum += v[n][i] * v[n][i];
    double lambda = sqrt( 3 * (N-1) * T / vSqdSum );
    for (int n = 0; n < N; n++)
        for (int i = 0; i < 3; i++)
            v[n][i] *= lambda;
}

double instantaneousTemperature() {
    double sum = 0;
    for (int i = 0; i < N; i++)
        for (int k = 0; k < 3; k++)
            sum += v[i][k] * v[i][k];
    return sum / (3 * (N - 1));
}
