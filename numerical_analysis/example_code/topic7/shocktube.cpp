#include "shocktube.hpp"

void solve(void stepAlgorithm(), double tMax, string fileName, int plots=5)
{
    initialize();
    double t = 0.0;
    int step = 0;
    int plot = 0;

    cout << " Time t\t\trho_avg\t\tu_avg\t\te_avg\t\tP_avg" << endl;
    while(true) {

        // write solution in plot files and print averages
        ostringstream oss;
        oss << plot << "-" << fileName << ends;
        ofstream file(oss.str().c_str());
        double rho_avg = 0.0, u_avg = 0.0, e_avg = 0.0, P_avg = 0.0;
        for (int j = 0; j < N; j++) {
            double rho = U[j][0];
            double u = U[j][1] / U[j][0];
            double e = U[j][2];
            double P = (U[j][2] - U[j][1] * U[j][1] / U[j][0] / 2)
                * (gama - 1);
            rho_avg += rho;
            u_avg += u;
            e_avg += e;
            P_avg += P;
            file << j << '\t' << rho << '\t' << u << '\t'
                 << e << '\t' << P << '\n';
        }
        if (rho_avg != 0.0) rho_avg /= N;
        if (u_avg != 0.0)   u_avg /= N;
        if (e_avg != 0.0)   e_avg /= N;
        if (P_avg != 0.0)   P_avg /= N;
        cout << " " << t << '\t' << rho_avg << '\t' << u_avg << '\t'
             << e_avg << '\t' << P_avg << endl;
        file.close();

        if (++plot > plots) {
            cout << " Solutions in files " << "0-.." << plots
                 << "-" << fileName << endl;
            break;
        }

        while (t < tMax * plot / double(plots)) {
            boundaryConditions(U);
            tau = CFL * h / cMax();
            stepAlgorithm();
            LapidusViscosity();
            t += tau;
            ++step;
        }
    }
}

int main()
{
    cout << " Sod's Shocktube Problem using various algorithms:\n"
         << " 1. A two-step Lax-Wendroff algorithm\n"
         << " 2. Mellema's Roe solver\n"
         << " N = " << N << ", CFL Number = " << CFL
         << ", nu = " << nu << endl;

    cout << "\n Lax-Wendroff Algorithm" << endl;
    solve(LaxWendroffStep, 1.0, "lax.data");
    cout << "\n Roe Solver Algorithm" << endl;
    solve(RoeStep, 1.0, "roe.data");
}
