

t = linspace(-5, 5);

x1 = 1 - t;
x2 = x1 + t.^2;
x3 = x2 - t.^3;
x4 = x3 + t.^4;
x5 = x4 - t.^5;
x6 = x5 + t.^6;

hold on

a1 = plot(t, x1); L1 = 'N = 1';
a2 = plot(t, x2); L2 = 'N = 2';
a3 = plot(t, x3); L3 = 'N = 3';
a4 = plot(t, x4); L4 = 'N = 4';
a5 = plot(t, x5); L5 = 'N = 5';
a6 = plot(t, x6); L6 = 'N = 6';

grid on

ylim([-3 20])

ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;

legend_handle = legend( {L1, L2, L3, L4, L5, L6} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'southwest');

xlabel('t');
ylabel('x');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('The Taylor Polynomial for a Differential Equation')
