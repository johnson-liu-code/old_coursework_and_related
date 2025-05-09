function [psi_time_real, psi_time_imag] = time_depedence(E, h_bar, psi)
    psi_repeat = repmat(psi.', 1000, 1);
    time_real = [cos( (E/h_bar)*(0:.001:1-.001) )].';
    time_imag = [sin( (E/h_bar)*(0:.001:1-.001) )].';
    psi_time_real = psi_repeat .* time_real;
    psi_time_imag = psi_repeat .* time_imag;
end