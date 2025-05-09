import math
import cmath

a = 1.0                             # size of unit cell - lattice spacing
V_0 = -5.0                          # height of potential barrier
Delta = 0.2                         # width of potential barrier

def solve_for_E(E, k):              # to solve 2x2 eigenvalue problem
    # E is the desired enegy (input)
    # k is a list of the two solutions
    q = math.sqrt(2 * E)
    kappa = math.sqrt(2 * (E - V_0))
    i = 1.0j
    T11 = ( cmath.exp(i * q * (a - Delta)) / (4 * q * kappa) *
            ( cmath.exp(i * kappa * Delta)  * (q + kappa)**2 -
              cmath.exp(-i * kappa * Delta) * (q - kappa)**2   ) )
    T22 = T11.conjugate()
    T12 = ( -i * cmath.exp(i * q * (a - Delta)) / (2 * q * kappa) *
            (q**2 - kappa**2) * math.sin(kappa * Delta)  )
    T21 = T12.conjugate()

    # solve quadratic determinantal equation
    b = - (T11 + T22)
    c = (T11 * T22 - T12 * T21)
    k[0] = (- b + cmath.sqrt(b**2 - 4*c)) / 2.0
    k[1] = (- b - cmath.sqrt(b**2 - 4*c)) / 2.0
    for j in range(2):
        k[j] = cmath.log(k[j]) / (i * a)

def compute_bands(dE, steps, band_file_name):
    # dE = step size in E for search
    # steps = number of steps
    file = open(band_file_name, "w")
    E = dE
    for step in range(steps):
        q = [ 0.0 + 0.0j, 0.0 + 0.0j ]
        solve_for_E(E, q)
        for j in range(2):
            rq = q[j].real
            if rq > 0.0 and rq < math.pi / a:
                file.write(str(rq) + "\t" + str(E) + "\n")
                file.write(str(-rq) + "\t" + str(E) + "\n")
        E += dE
    file.close()
    print(" Energy bands written in file", band_file_name)

print(" Kronig-Penney Model")
dE = 0.01
steps = 3000

print(" V_0 =", V_0, " Delta =", Delta)
compute_bands(dE, steps, "band.data")
V_0 = 0.0
print(" V_0 =", V_0, " Delta =", Delta)
compute_bands(dE, steps, "band0.data")
