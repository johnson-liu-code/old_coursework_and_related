
function s = sine_sum(N, t)
    n = linspace(1, N, N);
    s = ( 2.*n-1 ).^(-1) * sin( (2.*n - 1)' * t)
end