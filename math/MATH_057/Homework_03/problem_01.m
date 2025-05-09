

t = linspace(-20, 20)


% x1 = t;
% x3 = x1 - 1/6 * t.^3;
% x5 = x3 + 1/120 * t.^5;

% plot(t, x1);
% plot(t, x3);
% plot(t, x5);

% N = 3
% y = cos_sin_x(t, N)
% 
% plot(t, y, 'ro')

hold on

x0 = cos_sin_x(t, 0);
x1 = cos_sin_x(t, 1);
x2 = cos_sin_x(t, 2);
x3 = cos_sin_x(t, 3);
x4 = cos_sin_x(t, 4);
% x5 = cos_sin_x(t, 5);
% x6 = cos_sin_x(t, 6);
% x7 = cos_sin_x(t, 7);
% x8 = cos_sin_x(t, 8);

a0 = plot(t, x0); L0 = 'N = 0';
a1 = plot(t, x1); L1 = 'N = 1';
a2 = plot(t, x2); L2 = 'N = 2';
a3 = plot(t, x3); L3 = 'N = 3';
a4 = plot(t, x4); L4 = 'N = 4';
% a5 = plot(t, x5); L5 = 'N = 5';
% a6 = plot(t, x6); L6 = 'N = 6';
% a7 = plot(t, x7); L7 = 'N = 7';
% a8 = plot(t, x8); L8 = 'N = 8';

grid on

ylim([-3 3])

ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;

legend_handle = legend( {L0, L1, L2, L3, L4} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'southwest');

xlabel('t');
ylabel('x');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('The Taylor Polynomial for a Differential Equation')