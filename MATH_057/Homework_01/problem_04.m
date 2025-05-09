



t = 0;
x = 1;
v = 2;
a = -3;

dt = .001;

n = 1000;

p = linspace(1, 10, n);

x_vec = zeros(1, length(p));
v_vec = zeros(1, length(p));
t_vec = zeros(1, length(p));
a_vec = zeros(1, length(p));


m = 1;

for i = p
    x = x + v*dt;
    x_vec(1, m) = x;
    v = v + a*dt;
    v_vec(1, m) = v;
    t = t + dt;
    t_vec(1, m) = t;
    a_vec(1, m) = a;
    
    m = m + 1;
end

hold on

a1 = plot(t_vec, x_vec); L1 = 'Position';
a2 = plot(t_vec, v_vec); L2 = 'Velocity';
a3 = plot(t_vec, a_vec); L3 = 'Acceleration';

grid on

ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;

legend_handle = legend( {L1, L2, L3} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'southwest');

xlabel('Time');
ylabel('');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('Euler Method for Approximating Unknown Function')