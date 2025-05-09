
tspan = [0 10];
y0 = 1;
[t, y] = ode45(@(t,y) -y + 5*cos(2*t), tspan, y0);

x = linspace(0, 10);
y2 = 5^.5 * sin(2*x + atan2(1, 2));

hold on
plot(t, y, 'o')
plot(x, y2)

xlabel('t')
ylabel('y')

grid on

legend('ODE45 solution', 'Analytical solution')