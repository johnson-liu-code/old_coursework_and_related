clear; close all;

m = 1;
h_bar = 1;
k = 1;

c = 1;
% q = [1 1];
G = 1;
mass = [1 2];

potential = Inf;

a = 1;
h = 1E-3;
interval = a / h;

j = 0;
color = ['b' 'm'];
col = 1;
direction = 0;

lookForward = true;

switch(lookForward)
    case true; dE = 1E0;
    case false; dE = -1E0;
end



% V = zeros(interval+1, 1);
% V([1 end]) = Inf;
% blocks = [20:24 49:56 70:75]';
%blocks =[49:56];
%blocks = [49:51];
% V(blocks) = 1E4;
%V(51) = Inf;

psi = zeros(interval+1, 2);
psi(:,1) = (0:interval)' * h;

source = a/2;

% V = 1 ./ abs((psi(:,1) - source));

r = abs(psi(:,1) - source);

E = 10;
E_init = E;

q = [1 1];

V = (q(1) * q(2)) .* (r .* log(r) - r);
V(isnan(V)) = 0;


hold on
grid on
grid minor
% axis([0 1 min(psi(:,2))-0.01 max(psi(:,2))+0.01])

% plot(psi(:,1), V);

color_num = 1;
color = ['b' 'm'];

while abs(dE) > 1E-5
    psi(:,2) = 0;
    psi(2, 2) = h;
    
    for ii = 3:interval+1        
        psi(ii, 2) = finite_difference(psi(ii-2, 2), psi(ii-1, 2), h, m, k, h_bar, E, V(ii));
    end
        
    if direction == 0
        if(psi(end, 2) < 0 );
            direction = -1;
        else;
            direction = 1;
        end
        E = E + dE;
        continue
    end

    if (psi(end, 2) > 0 && direction < 0) || (psi(end, 2) < 0 && direction > 0)
        dE = -dE * 1E-1;
        direction = -direction;
    end
    
    if color_num == 1
        color_num = 2;
    elseif color_num == 2
        color_num = 1;
    end
    
%    plot(psi(:, 1),psi(:,2), color(color_num),'LineWidth',2);
%    drawnow;
%    pause(.25);

    E = E + dE;
end

E_init;
E
%E_expected;

x = psi(1:interval, 1);
y = psi(1:interval, 2);

% plot(psi(:, 1), psi(:,2),'m','LineWidth',2);
% plot(psi(:, 1), psi(:,2).^2,'g','LineWidth',2);
% cftool

% fit(x, y, 'sin1')

[psi_time_real, psi_time_imag] = time_dependence(E, h_bar, psi(1:end-1, 2));

y_min = min(min(psi_time_real));
y_max = max(max(psi_time_real));

hold on
% grid on
% grid minor


for ii = 1:length(psi_time_real)
   plot( psi(1:interval, 1), psi_time_real(ii, :), 'r');
   plot( psi(1:interval, 1), psi_time_imag(ii, :), 'b');
%    plot( psi(1:interval, 1), psi_time_real(ii, :) .* psi_time_imag(ii, :), 'm');

%    plot( psi(1:interval, 1), .80523 * (psi(1:interval, 2) .* psi(1:interval, 2) ), 'm');
   
   set(gca, 'YLim', [y_min y_max])

   pause(.04);
   drawnow
   cla
end
