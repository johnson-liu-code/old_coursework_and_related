

t = linspace(0, 5);
initial_x = 0;
initial_dxdt = 1;

[t, x] = ode45(@rhs, t, [initial_x initial_dxdt]);

hold on
grid on
xlabel('t')
ylabel('x')

plot(t, x)

y = -1/2 * exp(-3*t) + 1/2 * exp(-t);

plot(t, y, 'o')

function dxdt = rhs(t, x)
    dxdt_1 = x(2);
    dxdt_2 = -4*x(2) - 3*x(1);
    
    dxdt = [dxdt_1; dxdt_2];
end