m = 1;
h_bar = 1;
k = 1;

c = 1;
q = [1 1];
G = 1;
mass = [1 2];

potential = Inf;

a = 1;
h = 1E-3;
interval = a / h;
% a = .05;


%n = 3;
% E_expected = (n^2 * pi^2 * h_bar^2) / (2 * m * a^2);
%E_expected = (h_bar * pi * n)^2 / (2 * m * a^2);

E = 100;
E_init = E;

j = 0;

%hold on
%axis square

color = ['b' 'm'];
col = 1;

% look = 'back';
look = 'forw';

previous = 0;

if look == 'forw'
    change = 1E0;
%     change = 10;
elseif look == 'back'
    change = -1E0;
end

% V = zeros(interval+1, 1);
% V([1 end]) = Inf;
%blocks = [20:24 49:56 70:75]';
%blocks =[49:56];
%blocks = [49:51];
%V(blocks) = 1E2;
%V(51) = Inf;

psi = zeros(interval+1, 2);

for ii = 1:interval+1
    psi(ii, 1) = (ii-1) * h;
end

psi(2, 2) = h;

while abs(change) > 1E-3
    for ii = 3:interval+1
%         if psi(i, 1) == a
%             V = inf;
%         elseif psi(i, 1) == a/2
%             V = inf;
%         else
%             %V = compute_V(psi(i, 1), c, q);
%             V = 0;
%         end

        psi(ii, 2) = finite_difference(psi(ii-2, 2), psi(ii-1, 2), h, m, k, h_bar, E, V(ii));

    end
%     axis([0 1 0 .5])
%     plot(psi(1:interval, 1), psi(1:interval, 2), 'Color', color(col));
%     pause;
%     drawnow
    
    if psi(interval+1, 2) > 0
        E = E + change;
    elseif psi(interval+1, 2) < 0
        E = E - change;
    end
    
    if ( (previous > 0) && (psi(interval+1, 2) < 0 ) ) || ( (previous < 0) && (psi(interval+1, 2) > 0 ) )
        change = change*.1;
    end
    
    previous = psi(interval+1, 2);
    
    if col == 1
        col = 2;
    elseif col == 2
        col = 1;
    end
%}
end

E_init;
E
%E_expected;

x = psi(1:interval, 1);
y = psi(1:interval, 2);

% plot(  psi(1:interval, 1) , psi(1:interval, 2), 'g', 'LineWidth', 2);

% cftool

% fit(x, y, 'sin1')

%ax = gca;
%ax.YAxisLocation = 'origin';


[psi_time_real, psi_time_imag] = time_dependence(E, h_bar, psi(1:end-1, 2));

y_min = min(min(psi_time_real));
y_max = max(max(psi_time_real));

hold on;

for ii = 1:length(psi_time_real)
   plot( psi(1:interval, 1), psi_time_real(ii, :), 'r');
   plot( psi(1:interval, 1), psi_time_imag(ii, :), 'b');
%    plot( psi(1:interval, 1), psi_time_real(ii, :) .* psi_time_imag(ii, :), 'm');

%    plot( psi(1:interval, 1), (psi(1:interval, 2) .* psi(1:interval, 2) ), 'm');
   
   set(gca, 'YLim', [y_min y_max])

   pause(.03);
   drawnow
   cla
end


