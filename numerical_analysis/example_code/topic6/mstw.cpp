// Adapted from the MSTW2008 code file example.cc
// Needs mstwpdf.cc mstwpdf.h mstw2008lo.00.dat
// c++  mstw.cpp  mstwpdf.cc

#include "mstwpdf.h"

int main()
{
    string grid_file_name("mstw2008lo.00.dat");
    c_mstwpdf *pdf = new c_mstwpdf(grid_file_name.c_str());

    // Specify the momentum fraction "x" and scale "q".
    double x = 1e-3, q = 1e1;
    cout << "x = " << x << ", q = " << q << endl;

    // Here the PDG notation is used for the parton flavour
    // (apart from the gluon has f=0, not 21):
    //  f =   -6,  -5,  -4,  -3,  -2,  -1,0,1,2,3,4,5,6
    //    = tbar,bbar,cbar,sbar,ubar,dbar,g,d,u,s,c,b,t.
    // Can also get valence quarks directly:
    //  f =  7, 8, 9,10,11,12.
    //    = dv,uv,sv,cv,bv,tv.
    // Photon: f = 13.

    double up,down,ubar,dbar,upv,dnv,usea,dsea,
        str,sbar,chm,cbar,bot,bbar,glu,phot;
    up = pdf->parton(2,x,q);
    down = pdf->parton(1,x,q);
    ubar = pdf->parton(-2,x,q);
    dbar = pdf->parton(-1,x,q);
    upv = pdf->parton(8,x,q);
    dnv = pdf->parton(7,x,q);
    usea = pdf->parton(-2,x,q);
    dsea = pdf->parton(-1,x,q);
    str = pdf->parton(3,x,q);
    sbar = pdf->parton(-3,x,q);
    chm = pdf->parton(4,x,q);
    cbar = pdf->parton(-4,x,q);
    bot = pdf->parton(5,x,q);
    bbar = pdf->parton(-5,x,q);
    glu = pdf->parton(0,x,q);
    phot = pdf->parton(13,x,q);

    // Print out grid ranges, heavy quark masses, and alphaS values

    cout << "xmin = " << pdf->xmin << ", "
         << "xmax = " << pdf->xmax << ", "
         << "qsqmin = " << pdf->qsqmin << ", "
         << "qsqmax = " << pdf->qsqmax << endl;

    cout << "mCharm = " << pdf->mCharm << ", "
         << "mBottom = " << pdf->mBottom << endl;

    cout << "alphaS(Q0) = " << pdf->alphaSQ0 << ", "
         << "alphaS(MZ) = " << pdf->alphaSMZ << ", "
         << "alphaSorder = " << pdf->alphaSorder << ", "
         << "alphaSnfmax = " << pdf->alphaSnfmax << endl;

    delete pdf;
    return 0;
}
