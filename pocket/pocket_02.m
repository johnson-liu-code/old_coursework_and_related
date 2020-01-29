

load('usps_modified.mat');
[x, y] = getfeatures(data);

% scatter(x(:,1), x(:,2))

% rand('seed', 1994)                                              % Set random generator seed.

% w = [0.4329;-0.5313;0.3321];                                    % Set initial weight vector.
w = [-1 + (2)*rand(3, 1)];
iterations = 10;                                                % Number of iterations.
[ hypothesis_w_list, N, x, y ] = pocket(x, y, w, iterations);   % Run pocket algorithm.
err_list = (1/N) * sum(sign(hypothesis_w_list*x')'~= y)'       % Compute error for each of the saved 
                                                                % weight vectors.
% plot(err_list)
x_range = linspace(-1, -.2);                                     % Set domain.
w2 = hypothesis_w_list(iterations,:);                           % Get last weight vector.
x1 = -(w(2)/w(3)) * x_range - w(1)/w(3);                        % Compute hypothesis line for initial
                                                                % weight vector.
x2 = -(w2(2)/w2(3)) * x_range - w2(1)/w2(3);                    % Compute hypothesis line for last
                                                                % weight vector.
% figure
% hold on
scatter(x(1:100,2), x(1:100,3))                                   % Plot the data points for "1".
scatter(x(101:200,2), x(101:200,3))                                 % Plot the data points for "5".
% plot(x_range, x1)
plot(x_range, x2)                                               % Plot the final hypothesis line.

b = find(sign(w2*x')' ~= y);                                    % Get the indices of all of the misclassified
                                                                % points according to the final hypothesis
                                                                % weight vector.
plot(x(b, 2), x(b, 3), '+')                                     % Plot the misclassifed points.

grid on

function [ hypothesis_w_list, N, x, y ] = pocket(x, y, initial_weight, iterations)
    figure
    hold on
    x = [x(find(y==1), :); x(find(y==5), :)];               % Collect x data points for 1 and 5 only.
    x = [x(1:100, :); x(501:600, :)];
    y = [y(find(y==1)); y(find(y==5))];                     % Collect y data points for 1 and 5 only.
    y = [y(1:100); y(501:600)];
    y(find(y==5)) = -1;                                     % Convert y = 5 to y = -1.
    N = size(x);                                            % Number of data points.
    N = N(1);
    w = initial_weight;                                     % Initial weight vector.
    hypothesis_w_list = zeros(iterations, 3);               % List of weights for each iteration.
    x = [ ones(N,1) x ];                                    % Adding x_0 = 1 to the data points.
%     sign(w'*x')' ~= y
%     err = 0
%     for i=1:N
%         err = err + sign(dot(w, x(i,:)));
%     end
%     err = err / N;
%     a = sign(w'*x')'~= y;
%     a(find(a==0)) = -1;
    err = (1/N) * sum(sign(w'*x')'~= y);                    % Compute initial error.
%     err = (1/N) * sum(a);
    hypothesis_w_list(1,:) = w';                            % Save initial weight vector to hypothesis w list.
    for i=1:iterations-1                                    % Iterate over iterations.
%         [sign(w'*x')' y sign(w'*x')'~= y];
        wrong_indices = find(sign(w'*x')'~= y);             % Find all of the indices where the sign of dot(w, x)
                                                            % is different from the corresponding y value.
        index = wrong_indices(randi(length(wrong_indices)));% Randomly pick an index for a misclassified point.
%         plot(x(index, 2), x(index, 3), '+')
        new_w = w + y(index)*x(index,1:3)';                 % Compute new weight vector.
%         a = sign(new_w'*x')' ~= y;
%         a(find(a==0)) = -1;
        new_err = (1/N) * sum(sign(new_w'*x')' ~= y);       % Compute new error using the new weight vector.
%         new_err = sum(a);
%         new_err = 0;
%         for i=1:N
%             new_err = new_err + sign(dot(new_w, x(i,:)));
%         end
%         new_err = new_err / N
        if new_err < err                                    % Check if the new error is less than the best error.
%             display('change');
            err = new_err;                                  % Set best error to be equal to the new error.
            w = new_w;                                      % Set best weight vector to be equal to the new
                                                            % weight vector.
        end
        hypothesis_w_list(i+1,:) = w';                      % Append the current weight vector to the list of
                                                            % hypothesis weight vectors.
    end
end

% function hypothesis_w_list = single_perceptron(num_dots, initial_weight, iterations)
%     w = initial_weight;
%     hypothesis_w_list = zeros(iterations, 3);
%     x = -1 + (2).*rand(num_dots, 2);
%     x = [ones(num_dots,1) x];
%     y = double(x(1:num_dots,2) > x(1:num_dots,3));
%     y(find(y==0)) = -1;
%     for i=1:iterations
%         h = sign(w' * x')';
%         index = find(h~=y);
%         if size(index) > 0
%             index = index(1);
%             w = w + y(index) * x(index, 1:3)';
%         end
%         hypothesis_w_list(i,1:3) = w;
%     end
% end