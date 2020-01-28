

m = 1;
h_bar = 1;

c = 1;
q = [1E2 1];
G = 1;
mass = [1 2];


h = 1E-3;
half_length = 1E1;
full_length = 2 * half_length;
% a = .05;
a = full_length * h;



% n=2;
% E = (n^2 * pi^2 * h_bar^2) / (2 * m * a^2);

E = 73001;
E_init = E;

overlap = 1;

threshold = 1E-5;

hold on
axis square

while abs(overlap) > threshold
    psi = zeros(half_length, 4);
    
    for i = 1:half_length
        psi(i, 1) = (i-1) * h;
        psi(i, 3) = (full_length - (i+1) ) * h;
    end

    psi(1, 2) = 0;
    psi(2, 2) = h;
    
    psi(1, 4) = 0;
    psi(2, 4) = -h;
    
%     psi
    
    for i = 3:half_length
%         V = [compute_V(i*h, c, q, G, mass) compute_V( (i-1)*h , c, q, G, mass) compute_V( (i-2)*h , c, q, G, mass)];
        V = [0 0 0];
        k = compute_k(E, V, m, h_bar);
        psi(i, 2) = numerov( psi(i-2, 2), psi(i-1, 2), h, k(1), k(2), k(3) );
        psi(i, 4) = numerov( psi(i-2, 4), psi(i-1, 4), h, k(1), k(2), k(3) );

    end
    
    plot(psi(:, 1), psi(:, 2), 'b+'); %pause;
    plot(psi(:, 3), psi(:, 4), 'r+'); %pause;
    drawnow
    
    overlap = psi(half_length, 2) - psi(half_length, 4)
    
    E = E + 5E2;
end

E_init
E

psi_complete = [psi(:, 1:2) ; flipud(psi(:, 3:4))];

% plot(psi_complete(:, 1), psi_complete(:, 2), 'm+', 'MarkerSize', 10, 'LineWidth', 2)
plot(psi_complete(:, 1), psi_complete(:, 2), 'm', 'LineWidth', 2)
