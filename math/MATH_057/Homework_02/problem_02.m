
t = linspace(0, 5);

x2 = t.^2 - 2*t + 2 - 2.*exp(-t);
x3 = t.^3 - 3*t.^2 + 6*t - 6 + 6.*exp(-t);

x2_x3 = x2 + x3;



hold on

plot(x2); L1 = '$f(t) = t^2$';
plot(x3); L2 = '$f(t) = t^3$';
plot(x2_x3); L3 = '$f(t) = t^2 + t^3$';

grid on

ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;

legend_handle = legend( {L1, L2, L3} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'northwest');

xlabel('t');
ylabel('x');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('A family of simple differential equations')