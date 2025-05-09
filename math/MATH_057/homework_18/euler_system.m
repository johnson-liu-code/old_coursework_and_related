function [ t, y, dy ] = euler_system( A, y0, tfin )

dt = .001;            % Step size
t = 0:dt:tfin;        % Interval
n = length(t);
y = zeros(2, n);      % Initialize
dy = zeros(2, n);

y(:,1) = y0;
dy(:,1) = A*y(:,1);

for j = 2:length(t)                      % Loop
    y(:,j) = y(:,j-1) + dy(:,j-1)*dt;    % Update y
    dy(:,j) = A*y(:,j);                  % Update dy
end

plot(t, y(1,:), t, y(2,:))

xlabel('t (days)')
ylabel('Number of fish')
legend('Adult fish', 'Juvenile fish', 'Location', 'Best')

grid on

end