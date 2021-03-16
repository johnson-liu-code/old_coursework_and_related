function [ t, y, dy, ddy ] = socche( m, g, k, y0, v0, tfin )
% Inputs: m, g, k are the coefficients in my'' + gy' + ky = 0
%         y0, v0 are the initial displacement and velocity

dt = .001;            % Step size
t = 0:dt:tfin;        % Interval
y = zeros(size(t));   % Initialize
dy = zeros(size(t));
ddy = zeros(size(t));

y(1) = y0;
dy(1) = v0;
ddy(1) = -(g/m)*dy(1) - (k/m)*y(1);
% ddy(1) = -(1/m)*y(1);

for j = 2:length(t)                     % Loop
    y(j) = y(j-1) + dy(j-1)*dt;         % Update y
    dy(j) = dy(j-1) + ddy(j-1)*dt;      % Update dy
    ddy(j) = -(g/m)*dy(j) - (k/m)*y(j); % Update ddy
%     ddy(j) = -(1/m)*y(j);
end

% plot(t, y, t, dy, t, ddy)
% 
% xlabel('t')
% 
% legend('y', 'dy', 'ddy')
% 
% grid on

end