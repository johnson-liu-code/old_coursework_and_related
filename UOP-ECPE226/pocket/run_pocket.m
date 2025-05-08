

rand('seed', 1994)

file_name = 'usps_modified.mat';
load(file_name);
[x, y] = getfeatures(data);

save_x = x;
save_y = y;

num_in_sample = 25;                                             % Number of 1 dots and number of 5 dots together (N = 25 + 25 = 50)
% num_in_sample = 100;                                              % Number of 1 does and number of 5 dots together (N = 100 + 100 = 200)

x = [x(find(y==1), :); x(find(y==5), :)];                         % Collect x data points for 1 and 5 only.
x = [x(1:num_in_sample, :); x(501:501+num_in_sample-1, :)];       % Select data points to be in the in-sample (x values).
N = length(x);                                                    % Get the size of in-sample data.
x = [ ones(N,1) x ];                                              % Adding x_0 = 1 to the data points.

y = [y(find(y==1)); y(find(y==5))];                               % Collect y data points for 1 and 5 only.
y = [y(1:num_in_sample); y(501:501+num_in_sample-1)];             % Select data points to be in the in-sample (y values).
y(find(y==5)) = -1;                                               % Convert y = 5 to y = -1.

iterations = 20;                                                % Number of iterations.
num_experiments = 1000;                                           % Number of runs.

final_w_list = zeros(num_experiments, 3);                         % Array to save final hypothesis weights from each run.
Ein_list = zeros(num_experiments, 1);                             % Array to save in-sample error from each run.

for i=1:num_experiments                                           % Iterate over number of runs.
    w = [-1 + (2)*rand(3, 1)];                                    % Set initial weight vector randomly. Each weight is in the range [-1, 1].

    [ hypothesis_w_list, pla_hypothesis_w_list, Ein] = pocket(x, y, w, iterations);   % Run pocket algorithm.

    final_w = hypothesis_w_list(iterations, :);              % Collect final hypothesis weights.
    final_w_list(i, :) = final_w;                                 % Save final hypothesis weights to array.
    Ein_list(i, 1) = Ein;                                         % Save in-sample error to array.
end

x = [save_x(find(save_y==1), :); save_x(find(save_y==5), :)];     % Collect x data points for 1 and 5 only.
x = [x(num_in_sample+1:500, :); x(501+num_in_sample:1000, :)];    % Collect out-sample data.
N = length(x);                                                    % Get size of out-sample data.
x = [ ones(N,1) x ];                                              % Adding x_0 = 1 to the data points.

y = [save_y(find(save_y==1)); save_y(find(save_y==5))];           % Collect y data points for 1 and 5 only.
y = [y(num_in_sample+1:500); y(501+num_in_sample:1000)];
y(find(y==5)) = -1;                                               % Convert y = 5 to y = -1.

dat = (1/N) * sum(sign(final_w_list*x')' ~= y);                   % Compute final Eout error for each run.
hist(dat, 20)                                                   % Plot histogram of Eout with 20 bins.
%grid on
%xlabel('$E_\textrm{out}$', 'interpreter', 'latex')
%ylabel('Number of occurances')
%hist(Ein_list, 20)                                               % Plot histogram of Ein with 20 bins.

% x_range = linspace(-1, .1);                                     % Set domain.
% w2 = hypothesis_w_list(iterations,:);                           % Get last weight vector from pocket algorithm.                                                                 
% x2 = -(w2(2)/w2(3)) * x_range - w2(1)/w2(3);                    % Compute hypothesis line for last weight vector.
% w3 = pla_hypothesis_w_list(iterations,:);                       % Get last weight vector from perceptron learning algorithm.
% x3 = -(w3(2)/w3(3)) * x_range - w3(1)/w3(3);                    % Compute hypothesis line for PLA weight vector.

% figure
% hold on

% Plot weights as function of iteration.
% plot(pla_hypothesis_w_list(:,1))
% plot(pla_hypothesis_w_list(:,2))
% plot(pla_hypothesis_w_list(:,3))
% plot(hypothesis_w_list(:,1))
% plot(hypothesis_w_list(:,2))
% plot(hypothesis_w_list(:,3))

% Plot data points.
% scatter(x(1:num,2), x(1:num,3))                                 % Plot the data points for "1".
% scatter(x(num+1:num+num,2), x(num+1:num+num,3))                 % Plot the data points for "5".
% plot(x_range, x2)                                               % Plot the final hypothesis line for the pocket algorithm.
% plot(x_range, x3)                                               % Plot the final hypothesis line for the PLA.

% x and y axis labels.
% xlabel('$x_1$', 'interpreter', 'latex')
% ylabel('$x_2$', 'interpreter', 'latex', 'rotation', 0)

% x and y axis limits.
% xlim([-1 .1])
% ylim([-1 1])

% b = find(sign(w2*x')' ~= y);                                    % Get the indices of all of the misclassified
%                                                                 % points according to the final hypothesis
%                                                                 % weight vector.
% plot(x(b, 2), x(b, 3), '+')                                     % Plot the misclassifed points.

% Plotting parameters.
% legend('1', '5', 'Hypothesis Line', 'Misclassifed', 'location', 'best')
% xlabel('Iteration', 'interpreter', 'latex')
% ylabel('$w_0$', 'interpreter', 'latex', 'rotation', 0)
% ylabel('$w_1$', 'interpreter', 'latex', 'rotation', 0)
% ylabel('$w_2$', 'interpreter', 'latex', 'rotation', 0)
% legend('PLA $w_0$', 'Pocket $w_0$', 'location', 'best', 'interpreter', 'latex')
% legend('PLA $w_1$', 'Pocket $w_1$', 'location', 'best', 'interpreter', 'latex')
% legend('PLA $w_2$', 'Pocket $w_2$', 'location', 'best', 'interpreter', 'latex')
% grid on
