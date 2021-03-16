






f = @ff;
ode = @(t, x) f(t) - 5*x;
tspan = [0, 4];
x0 = 0;
[t, x] = ode45(ode, tspan, x0);


hold on
plot(t, x)

% M = [];
% p = linsolve(M, x);
% 
% y = p(1)*exp(-2*t) + p(2)*t.*exp(-2*t);
% 
% y = -21*exp(-5*t) + 21*cos(2*t) - 9/29 *sin(2*t);
% 
% plot(t, y, 'o')

y = -exp(-5*t) + exp(-2*t);

plot(t, y, '+')

grid on

function y = ff(xt)
    y = 3*exp(-2*xt);
end