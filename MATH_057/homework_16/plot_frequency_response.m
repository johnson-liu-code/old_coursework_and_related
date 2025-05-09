
x = linspace(-10, 10, 1000);

y = (x.^4 + 2*x.^2 + 1).^-.5;

plot(x, y)
grid on

xlabel('\omega')
ylabel('H')
