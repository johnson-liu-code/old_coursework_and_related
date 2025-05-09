

t = linspace(0, 3);
initial_x = 0;
initial_dxdt = 1;

[t, x] = ode45(@rhs, t, [initial_x initial_dxdt]);

hold on
grid on
xlabel('t')
ylabel('x')

plot(t, x)

y = (initial_dxdt/(6^.5)) * exp(-2*t) .* sin(6^.5 * t);

plot(t, y, 'o')

function dxdt = rhs(t, x)
    dxdt_1 = x(2);
    dxdt_2 = -4*x(2) - 10*x(1);
    
    dxdt = [dxdt_1; dxdt_2];
end