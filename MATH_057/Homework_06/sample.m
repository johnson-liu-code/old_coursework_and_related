

rhs = @(t, x) 2*sin(t) - x;

% x0_list = [-10:10];
hold on
grid on
% 
% for x0 = x0_list
%     [t, x] = ode45(rhs, [0, 6*pi], x0);
%     plot(t, x)
% end
% 
xlabel('t')
ylabel('x')


[t, x] = ode45(rhs, [0, 6*pi], 10);

ind = t > 5;
tt = t(ind);
xx = x(ind);

% plot(tt, xx)

A = [cos(tt) sin(tt)];
v = linsolve(A, xx);

ind = t < 5;
tt = t(ind);
xx = x(ind);

A = [cos(tt) sin(tt)];
yy = xx - A*v;

% plot(tt, yy)

zz = log(yy);
p = polyfit(tt, zz, 1);

plot(tt, zz, 'ro')
plot(tt, polyval(p, tt), 'b-')
