

m = 1;
h_bar = 1;
p = 1;

a = 1;
h = 1E-1;

n=1;
% E = (n^2 * p^2 * h_bar^2) / (2 * m * a^2);
V = 0;
% c = -(2 * m * h^2.) / h_bar^2;


E = 6;

C = -(2*m) / (h_bar^2) * (E - V);

length = a / h;

x = zeros(length, 1);

psi = ones(length, 1);


for i = 1:length
    x(i) = i;
    psi(i) = 1;
end

psi(1) = 0;
psi(length) = 0;

change = 1

% hold on
axis square

while change > 1E-8
    for i = 1:1E1
        psi_temp = zeros(length, 1);
        for i = 2:length-1
    %         psi(i) = (c*(E-V)+2.)^-1. * (psi(i+1) + psi(i-1));
            psi_temp(i) = ( ( (1 + 1/12 * h^2 * C) * psi(i+1) + (1 + 1/12 * h^2 * C) * psi(i-1) ) / (2 * (1 - 5/12 * h^2 * C) ) );
%             plot(x, psi, 'b')
%             drawnow
        end
        change = (sum((psi_temp - psi).^2))^.5;
        psi = psi_temp;
    end
    E = E + 1E-1
end

plot(x, psi, 'r')
% psi
