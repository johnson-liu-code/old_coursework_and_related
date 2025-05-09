

rhs = @(t, x) cos(3*t) - 2*x;

% x0_list = [-2:2];

hold on
grid on

xlabel('t')
ylabel('x')

% for x0 = x0_list
%     [t, x] = ode45(rhs, [0, 2*pi], x0);
%     plot(t, x)
% end

x0 = 10;
[t, x] = ode45(rhs, [0, 3*pi], x0);

% plot(t, x)
% 
ind = t > 4;
tt = t(ind);
xx = x(ind);
% 
A = [cos(3*tt) sin(3*tt)];
v = linsolve(A, xx)

% y = v(1)*cos(3*tt) + v(2)*sin(3*tt);
% plot(tt, y, 'o')


ind = t < .4;
tt = t(ind);
xx = x(ind);

A = [cos(3*tt) sin(3*tt)];
yy = xx - A*v;

% plot(tt, yy)
% 
zz = log(yy);
% 
% p = polyfit(tt, zz, 1)
% 
% plot(tt, zz)
% 
z = v(1)*cos(3*t) + v(2)*sin(3*t) + (exp(p(2)))*exp(p(1)*t);
% 
plot(t, x)
plot(t, z, 'o')




