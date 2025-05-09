#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "../tools/random.hpp"

#ifdef __APPLE__
#  include <GLUT/freeglut.h>
#else
#  include <GL/glut.h>
#endif

int L = 400;
int N = 400 * 400;

int **spin, **cluster, **stack, ***bond;
int *prev, *next, *labelLabel;
int stackp;

double J = 1;
double T = 2.25;
double H = 0;
double Tmin = 0.5, Tmax = 4.0, Tc = 2.267;
double w[17][3], expMinus2JOverT;

void computeBoltzmannFactors();
void initialize();
void oneMetropolisSweep();
void oneSwendsenWangStep();
void oneWolffStep();

int algorithm = 0;
void (*oneMonteCarloStep)() = oneMetropolisSweep;

void initialize (void) {
     int i, j, x, y;

     N = L * L;
     spin = new int* [L];
     cluster = new int* [L];
     bond = new int** [L];
     for (i = 0; i < L; i++) {
          spin[i] = new int [L];
          cluster[i] = new int [L];
          bond[i] = new int* [L];
          for (j = 0; j < L; j++)
              bond[i][j] = new int [2];
     }
     prev = new int [L];
     next = new int [L];
     labelLabel = new int [N];
     stack = new int* [N];
     for (i = 0; i < N; i++)
          stack[i] = new int[2];

     // seed = timeSeed();
     for (x = 0; x < L; x++)
          for (y = 0; y < L; y++)
               spin[x][y] = uniform_dist() > 0.5 ? +1 : -1;

     for (i = 0; i < L; i++) {
          prev[i] = i - 1;
          next[i] = i + 1;
     }
     prev[0] = L - 1;
     next[L - 1] = 0;

     computeBoltzmannFactors();
}

void computeBoltzmannFactors () {
     int i;

     for (i = -8; i <= 8; i += 4) {
          w[i + 8][0] = exp( - (i * J - 2 * H) / T);
          w[i + 8][2] = exp( - (i * J + 2 * H) / T);
     }
     expMinus2JOverT = exp(- 2 * J / T);
}

GLubyte *spinImage;

void oneMetropolisSweep (void) {
     int i, x, y, sum_of_neighbors, delta_SS;
     double ratio_of_Boltzmann_factors;

     for (x = 0; x < L; x++) {
          for (y = 0; y < L; y++) {
               sum_of_neighbors = spin[x][next[y]] + spin[x][prev[y]]
                    + spin[next[x]][y] + spin[prev[x]][y];
               delta_SS = 2 * spin[x][y] * sum_of_neighbors;
               ratio_of_Boltzmann_factors = w[delta_SS + 8][spin[x][y] + 1];
               if (uniform_dist() < ratio_of_Boltzmann_factors)
                    spin[x][y] = -spin[x][y];
               for (i = 0; i < 3; i++)
               spinImage[3 * (L * x + y) + i] =
                    (GLubyte) (spin[x][y] > 0 ? 0 : 255);
          }
     }

     glutPostRedisplay();
}

int proper (int i) {
     while (labelLabel[i] != i)
          i = labelLabel[i];
     return i;
}

void oneSwendsenWangStep () {
     int i, j, x, y, label, minLabel, bonds;
     int xBond[4], yBond[4];
     int **newSpin = stack;
     double freezeProb = 1 - expMinus2JOverT;

     /* freeze or delete bonds */
     for (x = 0; x < L; x++)
          for(y = 0; y < L; y++) {
               bond[x][y][0] = bond[x][y][1] = 0;
               if (spin[x][y] == spin[next[x]][y] && uniform_dist() < freezeProb)
                    bond[x][y][0] = 1;
               if (spin[x][y] == spin[x][next[y]] && uniform_dist() < freezeProb)
                    bond[x][y][1] = 1;
          }

     /* Hoshen-Kopelman identification of clusters */
     label = 0;
     for (x = 0; x < L; x++)
          for (y = 0; y < L; y++) {
               /* find sites connected to x,y by frozen bonds */
               bonds = 0;
               if (x > 0 && bond[x - 1][y][0]) {   /* check x-prev neighbor */
                    xBond[bonds] = prev[x];
                    yBond[bonds++] = y;
               }
               if (x == L - 1 && bond[x][y][0]) {  /* check x-next neighbor */
                    xBond[bonds] = 0;
                    yBond[bonds++] = y;
               }
               if (y > 0 && bond[x][y - 1][1]) {   /* check y-prev neighbor */
                    xBond[bonds] = x;
                    yBond[bonds++] = prev[y];
               }
               if (y == L - 1 && bond[x][y][1]) {  /* check y-next neighbor */
                    xBond[bonds] = x;
                    yBond[bonds++] = 0;
               }

               if (bonds == 0) {    /* start new cluster */
                    cluster[x][y] = label;
                    labelLabel[label] = label;
                    ++label;
               } else {   /* relabel bonded spins with smallest proper label */
                    minLabel = label;
                    for (i = 0; i < bonds; i++) {
                         j = proper(cluster[xBond[i]][yBond[i]]);
                         if (minLabel > j)
                              minLabel = j;
                    }
                    cluster[x][y] = minLabel;
                    for (i = 0; i < bonds; i++) {
                         j = cluster[xBond[i]][yBond[i]];
                         labelLabel[j] = minLabel;
                         cluster[xBond[i]][yBond[i]] = minLabel;
                    }
               }
          }

     /* set cluster spins randomly up or down */
     for (i = x = 0; x < L; x++)
          for (y = 0; y < L; y++, i++) {
               cluster[x][y] = proper(cluster[x][y]);
               newSpin[i][0] = newSpin[i][1] = 0;
          }
     for (x = 0; x < L; x++)
          for (y = 0; y < L; y++) {
               i = cluster[x][y];
               if (!newSpin[i][0]) {
                    newSpin[i][1] = uniform_dist() < 0.5 ? +1 : -1;
                    newSpin[i][0] = 1;
               }
               spin[x][y] = newSpin[i][1];
               for (i = 0; i < 3; i++)
               spinImage[3 * (L * x + y) + i] =
                    (GLubyte) (spin[x][y] > 0 ? 0 : 255);
          }

     glutPostRedisplay();
}

int try_add_count;

void tryAdd (int x, int y, int cluster_spin) {
    ++try_add_count;
    if (!cluster[x][y] && spin[x][y] == cluster_spin)
        if (uniform_dist() < 1 - expMinus2JOverT) {
            spin[x][y] = -spin[x][y]; /* flip spin */
            cluster[x][y] = 1;        /* mark as cluster*/
            ++stackp;                 /* push onto stack */
            stack[stackp][0] = x;
            stack[stackp][1] = y;
        }
}

void oneWolffStep (void) {
    int i, x, y, cluster_spin;

    try_add_count = 0;
    while (try_add_count < L * L) {
        /* zero cluster spin markers */
        for (x = 0; x < L; x++)
            for (y = 0; y < L; y++)
                cluster[x][y] = 0;
        /* initialize stack */
        stackp = -1;

        /* choose a random spin */
        x = (int) (L * uniform_dist());
        y = (int) (L * uniform_dist());

        /* grow cluster */
        cluster_spin = spin[x][y];
        spin[x][y] = -spin[x][y];  /* flip the seed spin */
        cluster[x][y] = 1;         /* mark as cluster */
        ++stackp;                  /* push onto stack */
        stack[stackp][0] = x;
        stack[stackp][1] = y;
        while (stackp > -1) {
            x = stack[stackp][0];      /* pop from stack */
            y = stack[stackp][1];
            --stackp;
            /* try add each neighbor to cluster */
            tryAdd(next[x], y, cluster_spin);
            tryAdd(prev[x], y, cluster_spin);
            tryAdd(x, next[y], cluster_spin);
            tryAdd(x, prev[y], cluster_spin);
        }
    }

    for (x = 0; x < L; x++) {
        for (y = 0; y < L; y++) {
            for (i = 0; i < 3; i++)
                spinImage[3 * (L * x + y) + i] =
                    (GLubyte) (spin[x][y] > 0 ? 0 : 255);
        }
    }

    glutPostRedisplay();
}

void init();
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);

struct Box {    /* pixel coordinates for mouse events */
     int left;
     int right;
     int top;
     int bottom;
} T_box, spin_box, algorithm_box[3];

int isInside (struct Box *box, int x, int y) {
     return box->left < x && box->right > x
          && box->top < y && box->bottom > y;
}

void init (void) {
     int x, y;

     spinImage = new GLubyte [L * L * 3];

     glClearColor(1.0, 195 / 255.0, 0.0, 0.0);
     glShadeModel(GL_FLAT);
     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

     initialize();
}

void drawText(const string& str, int x, int y) {
     glRasterPos2i(x, y);
     int len = str.find('\0');
     for (int i = 0; i < len; i++)
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}

void display (void) {
     int i;
     double w, h, dxy;
     string name[3] = {"Metropolis", "Swendsen-Wang", "Wolff"};

     dxy = T_box.bottom - T_box.top;
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3ub(192, 192, 192);
     h = dxy * (T - Tmin) / (Tmax - Tmin);
     glRectf(-30.0, 0.0, -6.0, h);
     glColor3ub(0, 0, 0);
     ostringstream os;
     os.precision(3);
     os << T << ends;
     drawText(os.str(), -33, int(h) - 12);
     os.seekp(0);
     glColor3f(1.0, 0.0, 0.0);
     h = dxy * (Tc - Tmin) / (Tmax - Tmin);
     glRectf(-33.0, h - 2, -3.0, h + 2);
     w = dxy / 3;
     for (i = 0; i < 3; i++) {
          if (i == algorithm)
               glColor3ub(230, 0, 0);
          else glColor3ub(0, 230, 0);
          glRectf(i * w + 3, -30.0, (i + 1) * w - 3, -6.0);
          glColor3ub(0, 0, 0);
          os << name[i] << ends;
          drawText(os.str(), i * int(w) + 10, -20);
          os.seekp(0);
     }
     glRasterPos2i(0, 0);
     glDrawPixels(L, L, GL_RGB, GL_UNSIGNED_BYTE, spinImage);
     glutSwapBuffers();
     glFlush();
}

void reshape (int w, int h) {
     int min_size = 339, widget_size = 30, pad = 3;
     int i, x, y, dx, dy, dxy, widget_area_size;

     widget_area_size = L > 300 ? L : 300;
     dx = dy = pad + widget_size + pad + L + pad;
     if (dx < min_size)
          dx = min_size;
     if (dy < min_size)
          dy = min_size;

     x = w > dx ? (w - dx) / 2 : 0;
     y = h > dy ? (h - dy) / 2 : 0;
     glViewport((GLint) x, (GLint) y, (GLsizei) dx, (GLsizei) dy);

     T_box.left = x + pad;
     T_box.right = T_box.left + widget_size;
     T_box.bottom = h - y - pad - widget_size - pad;
     T_box.top = T_box.bottom - widget_area_size;

     spin_box.left = x + pad + widget_size + pad;
     spin_box.right = spin_box.left + L;
     spin_box.bottom = T_box.bottom;
     spin_box.top = spin_box.bottom - L;

     dxy = widget_area_size / 3;
     for (i = 0; i < 3; i++) {
          algorithm_box[i].left = spin_box.left + i * dxy + pad;
          algorithm_box[i].right = spin_box.left + (i + 1) * dxy - pad;
          algorithm_box[i].top = spin_box.bottom + pad;
          algorithm_box[i].bottom = algorithm_box[i].top + widget_size;
     }

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     x = y = - pad - widget_size - pad;
     glOrtho(x, x + dx, y, y + dy, -1.0, 1.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

int running = 1;

void mouse (int button, int state, int x, int y) {
     int i;

     switch (button) {
     case GLUT_LEFT_BUTTON:
          if (state == GLUT_DOWN) {
               if (isInside(&T_box, x, y)) {
                    T = Tmin + (T_box.bottom - y) * (Tmax - Tmin)
                         / (T_box.bottom - T_box.top);
                    computeBoltzmannFactors();
               } else if (isInside(&spin_box, x, y)) {
                    if (running) {
                         running = 0;
                         glutIdleFunc(NULL);
                    } else {
                         running = 1;
                         glutIdleFunc(oneMonteCarloStep);
                    }
               } else {
                    for (i = 0; i < 3; i++) {
                         if (isInside(&algorithm_box[i], x, y))
                              algorithm = i;
                    }
                    switch (algorithm) {
                    case 0:
                         oneMonteCarloStep = oneMetropolisSweep;
                         break;
                    case 1:
                         oneMonteCarloStep = oneSwendsenWangStep;
                         break;
                    case 2:
                         oneMonteCarloStep = oneWolffStep;
                         break;
                    }
                    glutIdleFunc(oneMonteCarloStep);
               }
          }
          glutPostRedisplay();
          break;
     default:
          break;
     }
}

int main (int argc, char *argv[]) {
     int size = 300;

     glutInit(&argc, argv);
     if (argc > 1) {
          istringstream is(argv[1]);
          is >> L;
          cout << "Setting L = " << L << endl;
     }
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     if (L > size)
          size = L;
     glutInitWindowSize(size + 39, size + 39);
     glutInitWindowPosition(100, 100);
     glutCreateWindow("2-D Ising Model: Cluster Algorithms");
     init();
     glutDisplayFunc(display);
     glutReshapeFunc(reshape);
     glutMouseFunc(mouse);
     glutIdleFunc(oneMonteCarloStep);
     glutMainLoop();
}
