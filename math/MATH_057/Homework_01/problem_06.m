


t = linspace(0, pi);


s3 = sine_sum(3, t);
s6 = sine_sum(6, t);
s9 = sine_sum(9, t);
s12 = sine_sum(12, t);

hold on

a3 = plot(t, s3); L3 = 'N = 3';
a6 = plot(t, s6); L6 = 'N = 6';
a9 = plot(t, s9); L9 = 'N = 9';
a12 = plot(t, s12); L12 = 'N = 12';

grid on

ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;

legend_handle = legend( {L3, L6, L9, L12} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'south');

xlabel('x');
ylabel('y');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('Approximating a Step Function with Sines')