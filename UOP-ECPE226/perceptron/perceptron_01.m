
% rand('seed', 1994);

% num_dots = 20;
num_dots = 10:5:200;
% num_dots = 200;

x_range = linspace(-1,1);   % For y = x slope.
y_range = x_range;          % For y = x slope.


% 
% pos = [];
% neg = [];
% 
% sz = 30;
% cp = 'red';
% cn = 'blue';
% 
% for i=1:size(y,1)
%     if y(i) == 1
%         pos = [pos; x(i,1:2)];
%     else
%         neg = [neg; x(i,1:2)];
%     end
% end
% 
% p = size(pos);
% p = p(1);
% n = size(neg);
% n = n(1);

% x = -1 + (2).*rand(num_dots, 2);
% x = [ones(200,1) x];
% w = [-1 + (2).*rand(3, 1)];
% w = [0;1;1];
% x21 = -(w(2)/w(3)) * x_range - w(1)/w(3);

% figure
% hold on

convergence_vs_num_points = zeros(size(num_dots));
s = size(num_dots);
hypothesis_w_list = zeros(s(2),3);
for n=1:s(2)
    wrap = 2000;
%     N = 10;

%     difference = zeros(1, 1000);
%     expected_w = [0;1;1];

    converge_time = zeros(1, wrap);
w_list = zeros(10, 3);
for i=1:N
    i;
%     for j=1:wrap
%         x = -1 + (2).*rand(num_dots(n), 2);                    % Pairs of random numbers between -1 and 1.
%         y = double(x(1:num_dots(n),1) > x(1:num_dots(n),2));      % Check if point is above or below the y = x line.
        y = double(x(1:200,1) > x(1:200,2));
        y(find(y==0)) = -1;
%         x = [ones(num_dots(n), 1) x];

%         w = [-1 + (2).*rand(3, 1)];
%         previous_w = [];
%         num_iterations = 0;
%         converged = false;
%         while converged == false;
%             index = 1;
         h = sign(w' * x')';
         index = find(h~=y);
         if size(index) > 0
             index = index(1);
         else
             index = 1;
%              end
         end
%             previous_w = w;
         w = w + y(index) * x(index, 1:3)';
         w_list(i,1:3) = w;
%             previous_w_diff = w - previous_w;
%             if sum(previous_w_diff.^2) < 1e-3
%                 converged = true;
%                 break
%             else
%                 num_iterations = num_iterations + 1;
%             end
%         end
%         converge_time(j) = num_iterations;
    %     x22 = -(w(2)/w(3)) * x_range - w(1)/w(3);
    %     plot(x_range, x22, 'color', c(i+1,:))
end
% w_list
%     convergence_vs_num_points(n) = mean(converge_time);
%     hypothesis_w_list(n,:) = w';
% end
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