


hold on
grid on

xlabel('t')
ylabel('x')

rhs = @(t, x) t -3*x;
x0 = 10;
[t, x] = ode45(rhs, [0, 10], x0);

plot(t, x)

A = [exp(-3*t) t ones(size(t))];
v = linsolve(A, x)

y = v(1)*exp(-3*t) + v(2) * t + v(3);

plot(t, y, '+')

yy = 91/9 * exp(-3*t) + 1/3 * t - 1/9;

plot(t, yy, 'go')