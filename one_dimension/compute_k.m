function k = compute_k(E, V, m, h_bar)
    k = ( (2*m / h_bar^2) * (E - V) ).^.5;
end