function [ t, y, dy ] = problem_3_1_02( A, y0, tfin )
% Inputs: m, g, k are the coefficients in my'' + gy' + ky = 0
%         y0, v0 are the initial displacement and velocity

dt = .001;            % Step size
t = 0:dt:tfin;        % Interval
n = length(t);
y = zeros(2, n);      % Initialize
dy = zeros(2, n);

y(:,1) = y0;
dy(:,1) = A*y(:,1);

for j = 2:length(t)                      % Loop
    y(:,j) = y(:,j-1) + dy(:,j-1)*dt;    % Update y
    dy(:,j) = A*y(:,j) + [1;0];          % Update dy
end

plot(t, y(1,:), t, y(2,:))

xlabel('t (s)')
ylabel('Amount of salt (g)')
legend('container 1', 'container 2', 'Location', 'Best')

grid on

end