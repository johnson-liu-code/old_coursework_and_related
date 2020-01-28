function psi_n2 = finite_difference(psi_n, psi_n1, h, m, k, h_bar, E, V)
    psi_n2 = ( (-2*m / h_bar^2) * (E - V) * h^2 + 2) * psi_n1 - psi_n;
end