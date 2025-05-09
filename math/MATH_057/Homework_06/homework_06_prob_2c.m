

tspan = [0 1];
y0 = -1;
% [t,y] = ode45(@(t,y) 2*t, tspan, y0);
[t, y] = ode45(@(t,y) 5*y+5-4*exp(t), tspan, y0);

x = linspace(0, 1);
y2 = -1 + exp(x) - exp(5*x);

hold on
plot(t, y, 'o')
plot(x, y2)

xlabel('t')
ylabel('y')

grid on

legend('ODE45 solution', 'Analytical solution', 'location', 'SouthWest')