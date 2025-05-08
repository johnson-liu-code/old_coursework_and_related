
rand('seed', 1994);

% num_dots = 2000;
num_dots = 10:10:2000;
x_range = linspace(-1,1);   % For y = x slope.
y_range = x_range;          % For y = x slope.



% w = [-1 + (2).*rand(3, 1)];
w = [-.1678;13.982;-13.5078];
N = 1000;
% w_list = zeros(10, 3);
% for i=1:N
s = size(num_dots);

% error_list = zeros(s(2),1);
error = zeros(s(2), 1);
for num=1:s(2)
    error_list = zeros(1000,1);
    for n=1:N
        x = -1 + (2).*rand(num_dots(num), 2);
        x = [ones(num_dots(num),1) x];
        y = double(x(1:num_dots(num),2) > x(1:num_dots(num),3));
        y(find(y==0)) = -1;
        h = sign(w' * x')';
        index = find(h~=y);
        ss = size(index);
        error_list(n,1) = ss(1);
    end
    error(num,1) = mean(error_list);
%         if size(index) > 0
%             index = index(1);
%             w = w + y(index) * x(index, 1:3)';
%         else
%             w = w;
%         end
%     w_list(i,1:3) = w;
    %     x22 = -(w(2)/w(3)) * x_range - w(1)/w(3);
    %     plot(x_range, x22, 'color', c(i+1,:))
end

percent_correct = 1 - (error ./ num_dots');
plot(num_dots, percent_correct)
% x22 = -(w(2)/w(3)) * x_range - w(1)/w(3);
% plot([-1 1], [0 0], 'color', 'black')
% plot([0 0], [-1 1], 'color', 'black')
% % plot(x_range, x_range, 'LineWidth', 2, 'color', 'magenta')
% plot(x_range, x_range, 'color', 'magenta')
% scatter(pos(1:p,1), pos(1:p,2), sz, cp, 'filled')
% scatter(neg(1:n,1), neg(1:n,2), sz, cn, 'filled')
% % plot(x_range, x21, 'color', 'black')
% plot(x_range, x22, 'LineWidth', 2)
% xlim([-1 1])
% ylim([-1 1])
% set(gca, 'XTick', -1:.2:1)
% set(gca, 'YTick', -1:.2:1)
% grid on
% set(gca, 'GridLineStyle', '--')
% pbaspect([1 1 1])