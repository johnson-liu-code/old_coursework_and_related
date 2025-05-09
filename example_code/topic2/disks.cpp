#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/freeglut.h>
#endif

const double pi = 4 * atan(1.0);

inline double std_rand()
{
    return rand() / (RAND_MAX + 1.0);
}

const double A = 1;         // side of periodic volume
const int N = 224;          // number of disk in periodic volume

vector< vector<double> > r; // r = (x,y) coordinates of the N disks

double d_0;                 // disk diameter determined by nu
double alpha;               // maximum step in x or y for Metropolis algorithm

void initialize(            // set d_0, alpha, and position the disks
    double nu,              // auxiliary parameter varied from 0 to 7
    int rows=16,            // number of rows
    int columns=14)         // number of columns
{
    r.resize(N);            // N position vectors
    for (int i = 0; i < N; ++i)
        r[i].resize(2, 0);  // each has 2 components

    double d = 1 / double(columns);
    d_0 = d * (1 - pow(2.0, nu - 8));
    alpha = d - d_0;
    double dx = d;
    double dy = d * sqrt(3.0) / 2;
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < columns; i++) {
            int n = i + j * columns;
            r[n][0] = i * dx + (j % 2) * dx / 2.0;
            r[n][1] = j * dy;
       }
    }
}

bool overlap(                           // return true if overlap, else false
    const vector<double>& r1,           // position vector of first disk
    const vector<double>& r2)           // position vector of second disk
{
    vector<double> dr(2);
    double drsqd = 0;
    for (int k = 0; k < 2; ++k) {
        dr[k] = r1[k] - r2[k];
        drsqd += dr[k] * dr[k];
    }
    // if separation in x or y is > A/2 check overlap with closest image
    for (int k = 0; k < 2; k++)
        if (sqrt(drsqd) > 0.5 * A)
            dr[k] *= 1 - 1 / sqrt(drsqd);
    return drsqd < d_0 * d_0;
}

bool metropolis_step(int i) // apply Metropolis algorithm to disk i
{
    vector<double> r_trial = r[i];
    for (int k = 0; k < 2; k++) {
        r_trial[k] += alpha * (2 * std_rand() - 1.0);
        // apply periodic boundary conditions
        if (r_trial[k] < 0)
            r_trial[k] += A;
        if (r_trial[k] >= A)
            r_trial[k] -= A;
    }
    // accept move if there is no overlap with any other disk
    bool accept = true;
    for (int j = 0; j < N; j++)
        if (j != i && overlap(r_trial, r[j])) {
            accept = false;
            break;
        }
    if (accept)
        r[i] = r_trial;
    return accept;
}

void monte_carlo_step()
{
    for (int i = 0; i < N; i++)
        metropolis_step(i);
}

void take_step()
{
    monte_carlo_step();
    glutPostRedisplay();                // request glut to repaint window
}

void display()                          // display callback function
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 255);
    const double pi = 4 * atan(1.0);
    for (int i = 0; i < N; i++) {
        glBegin(GL_TRIANGLE_FAN);
            double x = r[i][0], y = r[i][1];
            glVertex2d(x, y);
            double phi = 2 * pi / 24;
            for (int j = 0; j < 25; j++)
                glVertex2d(x + 0.5 * d_0 * cos(phi * j),
                           y + 0.5 * d_0 * sin(phi * j));
        glEnd();
    }
    glColor3ub(255, 255, 255);
    glutSwapBuffers();                  // copy drawing buffer to screen
}

void reshape(int w, int h)              // window reshape callback function
{
    glViewport(0, 0, w, h);             // use whole window for drawing
    glMatrixMode(GL_PROJECTION);        // select projection matrix
    glLoadIdentity();                   // make it the identity
    double ratio = w / double(h);
    double x0 = - d_0, x1 = A + d_0, y0 = x0, y1 = x1;
    if (ratio > 1.0) {
        double margin = (ratio - 1) * (x1 - x0) / 2;
        x0 -= margin;
        x1 += margin;
    } else if (ratio < 1.0) {
        double margin = (1 / ratio - 1) * (y1 - y0) / 2;
        y0 -= margin;
        y1 += margin;
    }
    glOrtho(x0, x1, y0, y1, -1.0, 1.0); // orthographic projection
    glMatrixMode(GL_MODELVIEW);         // select modeling matrix
    glLoadIdentity();                   // make it the identity
}

void mouse(                             // mouse callback function
    int button,
    int state, int x, int y)
{
    static bool stopped = true;
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            if (stopped)                // set idle function to take_step
                glutIdleFunc(take_step);
            else
                glutIdleFunc(NULL);     // set idle function to do nothing
            stopped = !stopped;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            glutIdleFunc(NULL);
            stopped = true;
            throw "Exiting glutMainLoop";
        }
        break;
    default:
        break;
    }
}

void initialize_glut(int* argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // use double buffering
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(1.0, 1.0, 1.0, 0.0);   // background color white
    glShadeModel(GL_FLAT);
    glutDisplayFunc(display);           // register display function
    glutReshapeFunc(reshape);           // register reshape function
    glutMouseFunc(mouse);               // register mouse function
    try {
        glutMainLoop();
    } catch (const char *msg) {
        cout << " Exiting glutMainLoop" << endl;
    }
}

void radial_distribution_histogram(
    double nu,
    double K = 1.5,
    int number_of_bins = 64,
    int monte_carlo_steps = 100,
    string file_name="disks.data")
{
    int equilibration_steps = monte_carlo_steps / 10;
    cout << " Taking " << equilibration_steps << " equilibration steps" << endl;
    for (int step = 0; step < equilibration_steps; step++)
        monte_carlo_step();
    cout << " Taking " << monte_carlo_steps << " Monte Carlo steps" << endl;
    vector<double> histogram(number_of_bins);
    for (int step = 0; step < monte_carlo_steps; step++) {
        monte_carlo_step();
        const double pi = 4 * atan(1.0);
        double Delta_A2 = (K * K - 1) * pi * d_0 * d_0 / double(number_of_bins);
        // loop over all pairs of disks
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                vector<double> dr(2);
                double drsqd = 0;
                for (int k = 0; k < 2; ++k) {
                    dr[k] = r[i][k] - r[j][k];
                    drsqd += dr[k] * dr[k];
                }
                // if x or y separation > A/2 use closest image separation
                for (int k = 0; k < 2; k++)
                    if (sqrt(drsqd) > 0.5 * A)
                        dr[k] *= 1 - 1 / sqrt(drsqd);
                int bin = int(pi * (drsqd - d_0 * d_0) / Delta_A2);
                if (bin >= 0 && bin < number_of_bins)
                    histogram[bin] += 1;
            }
        }
    }
    ofstream data_file(file_name.c_str());
    for (int bin = 0; bin < number_of_bins; bin++)
        data_file << bin + 1 << '\t' << histogram[bin] << '\n';
    data_file.close();
    cout << " Radial distribution histogram in file " << file_name << endl;
}

int main(int argc, char *argv[])
{
    cout << " Monte Carlo simulation of hard disk gas\n"
         << " ---------------------------------------\n"
         << " Enter value of nu [0..7]: ";
    double nu;
    cin >> nu;
    initialize(nu);
    radial_distribution_histogram(nu);

    cout << " Enter y to run animation: ";
    string yes;
    cin >> yes;
    if (yes[0] == 'y' || yes[0] == 'Y') {
        initialize(nu);
        initialize_glut(&argc, argv);
    }
}
