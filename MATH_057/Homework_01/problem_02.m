





%function t = taylor(n, x)
%    t = 


x = linspace(0, 2);
y1 = exp(-x.^2 / 2);
% y2 = 1 - 1/2 * x.^2 + 1/8 * x.^4

N = 100;

t1 = exponential_taylor(1, N);
t2 = exponential_taylor(2, N);
t3 = exponential_taylor(3, N);
t4 = exponential_taylor(4, N);
t5 = exponential_taylor(5, N);



hold on

a0 = plot(x, y1); L0 = '$e^{-x^2 / 2}$';
a1 = plot(x, t1, '+'); L1 = 'n = 1';
a2 = plot(x, t2, '+'); L2 = 'n = 2';
a3 = plot(x, t3, '+'); L3 = 'n = 3';
a4 = plot(x, t4, '+'); L4 = 'n = 4';
a5 = plot(x, t5, '+'); L5 = 'n = 5';

grid on


ax = gca;
ax.LineWidth = 0.1;
ax.GridLineStyle = '--';
ax.GridColor = 'k';
ax.GridAlpha = 0.3;


legend_handle = legend( {L0, L1, L2, L3, L4, L5} );
set(legend_handle,'Interpreter','latex');

set(legend_handle, 'FontSize', 12, 'Location', 'southwest');

xlabel('x');
ylabel('y');
ylh = get(gca, 'ylabel');
gyl = get(ylh);
ylp = get(ylh, 'Position');
set(ylh, 'Rotation', 0, 'Position', ylp, 'VerticalAlignment', 'middle', 'HorizontalAlignment', 'right');

title('Taylor Polynomial of an Exponential Function')







