

figure
hold on
grid on

xlabel('t')
ylabel('x')

rhs = @(t, x) sin(t) + sin(3*t)/3 + sin(5*t)/5 + sin(7*t)/7 + sin(9*t)/9 + sin(11*t)/11 + sin(13*t)/13 + sin(15*t)/15 + sin(17*t)/17 + sin(19*t)/19 - x;
[t, x] = ode45(rhs, [0, 30], 10);

plot(t, x)

n = 1:10;
m1 = -1 ./ (1+(2*n-1).^2);
m2 = 1 ./ ( (1+(2*n-1).^2) .* (2*n-1));

c = cos( (2*n-1).*t );
s = sin( (2*n-1).*t );
A = 81103/7583;

y = A*exp(-t') + m1*c' + m2*s'

plot(t, y, 'r--')



