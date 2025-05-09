


% inter = [10 20 40 80 160 320];
inter = [190, 192, 194, 195, 196, 198]

figure

for k = 1:6
    N = inter(k);
    
    t = linspace(0, 20, N+1);

    x0 = 0;
    dt = t(2) - t(1);
    x = zeros(size(t));
    x(1) = x0;

    for n = 2:N
        x(n) = x(n-1) + (cos(t(n-1)) + 20 * sin(t(n-1)) - 20*x(n-1)) * dt;
    end
    
    subplot(2, 3, k)
    plot(t, x)
    grid on
    xlabel('t')
    ylabel('x')
    title(sprintf('N = %g', inter(k)))
end