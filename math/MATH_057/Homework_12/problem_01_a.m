


hold on

t = linspace(0, 10, 100);
initial_x = 0;
initial_y = 1;
[t, x] = ode45(@rhs, t, [initial_x initial_y]);
% plot(t, x(:,1))
plot(t, x(:,2))

x1 = -1i * exp((-1+2i)*t) + 1i * exp((-1-2i)*t);
x2 = .5 * exp((-1+2i)*t) + .5 * exp((-1-2i)*t);

% plot(t, x1, 'o')
plot(t, x2, 'o')

function dxdt = rhs(t, x)
    dxdt_1 = -x(1) + 4*x(2);
    dxdt_2 = -x(1) - x(2);
    dxdt = [dxdt_1; dxdt_2];
end