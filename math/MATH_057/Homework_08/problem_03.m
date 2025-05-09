

t = linspace(0, 20);
A1 = 1;
A2 = .001;
A3 = .001;
A4 = .001;

[t, x] = ode45(@rhs, t, [A1 A2 A3 A4]);

hold on
grid on
xlabel('t')
ylabel('x')

plot(t, x(:,1))

y = -A3*cos(t) - A4*sin(t) + (A2+A4)*t + (A1+A3);

plot(t, y, 'o')
title(sprintf('A1: %f, A2: %f, A3: %f, A4: %f', A1, A2, A3, A4))


function dxdt = rhs(t, x)
    dxdt_1 = x(2);
    dxdt_2 = x(3);
    dxdt_3 = x(4);
    dxdt_4 = -x(3);
    
    dxdt = [dxdt_1; dxdt_2; dxdt_3; dxdt_4];
end