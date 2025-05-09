


hold on
grid on

xlabel('t')
ylabel('x')

% rhs_01 = @(t, v) sin(t) - v;
% [t, v] = ode45(rhs_01, [0, 6*pi], 0);
% 
% plot(t, v)


t = linspace(0, 6*pi, 1000);
initial_x = 0;
initial_dxdt = 0;
[t, x] = ode45(@rhs, t, [initial_x initial_dxdt]);
plot(t, x(:,1))

r = 10;
m = 20;
A = 30;
w = 1;

title(sprintf('r = %d, m = %d, A = %d, w = %d', r, m, A, w))


y = (r/m + (w^2*m)/r)^(-1) * ((-m*w*A)/(r^2) * exp(-r/m * t) - A/r * sin(w*t) - A/(m*w) * cos(w*t) + (m*w*A)/(r^2) + A/(m*w));

plot(t, y, 'r--')

function dxdt = rhs(t, x)
    r = 10;
    m = 20;
    A = 30;
    w = 1;
    dxdt_1 = x(2);
    dxdt_2 = -r/m * x(2) + A/m * sin(w*t);
    dxdt = [dxdt_1; dxdt_2];
end


% function dxdt = rhs(t, x)
%     dxdt_1 = x(2);
%     dxdt_2 = -5*x(2) + 4*x(1) + sin(10*t);
%     dxdt = [dxdt_1; dxdt_2];
% end
    