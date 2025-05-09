
% 
% f = @sin;
% ode = @(t, x) f(t) - x;
% tspan = [0 8*pi];
% x0 = 5;
% [t, x] = ode45(ode, tspan, x0);

% hold on
% plot(t, x)
% plot(t, f(t))
% xlim(tspan)

% M = [exp(-t) cos(t) sin(t)];
% p = linsolve(M, x)



f = @ff;
ode = @(t, x) f(t) - 2*x;
tspan = [0, 50];
x0 = 10;
[t, x] = ode45(ode, tspan, x0);

hold on
plot(t, x); L1 = 'ODE solver solution';
% grid on
% xlabel('t')
% ylabel('x')
% 
% title('The solution to a differential equation')

M = [exp(-t) cos(t) sin(t) t ones(size(t))];
p = linsolve(M, x);

y = p(1)*exp(-t) + p(2)*cos(t) + p(3)*sin(t) + p(4)*t + p(5)*ones(size(t));
% 
% y = p(1)*exp(-t) + p(2)*cos(t) + p(3)*sin(t) + p(4)*t;
plot(t, y); L2 = 'Fitted function';
% 
% legend_handle = legend( {L1, L2} );
% set(legend_handle,'Interpreter','latex');
% 
% set(legend_handle, 'FontSize', 12, 'Location', 'southeast');

function y = ff(xt)
    y = xt + sin(xt);
end

























