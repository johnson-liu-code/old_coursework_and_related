
hbar = 1.055e-34;      % J.s
e = 1.602e-19;         % C
me = 9.109e-31;        % kg
eps0 = 8.854e-12;      % F/m

n = input('principle quantum number, n =  ');
disp('   ');
l = input('orbital quantum number, l =  ');
disp('   ');
m = input('magnetic quantum number, m =  ');
disp('   ');
Z = input('nuclear charge, Z =  ');
disp('   ');

% n = 1;
% l = 0;
% m = 0;
% Z = 1;


num = 1201;
r_min = 1E-15;
r_max = 1E-9;

r = linspace(r_min, r_max, num);
dr = r(2) - r(1);

% Second derivative matrix
SD = -(hbar^2 / (2*me*e)) * second_derivative(num, dr);

% Coulumb potential
Uc = -Z*e ./ (4*pi*eps0*r);

% Angular potential
Ul = ( (hbar^2 * l*(l+1))/(2*me*e) ) ./ r.^2;

% Effective potential
U = Uc + Ul;

U(U < -2000) = -2000;
U(U > 1000) = 1000;

U_matrix = sparse(diag(U(2:num-1))); 

H = SD + U_matrix;
[psi_matrix, E_matrix] = eig(full(H));

E_matrix = sparse(E_matrix);
E_matrix(:,n)
i
loc = find(diff(sign(diag(E_matrix))) > 0);

psi = zeros(num, loc);
prob = zeros(size(psi));

for cn = 1 : loc
    psi(:,cn) = [0; psi_matrix(:,cn); 0];
    area = simpson1d( (psi(:,cn) .* psi(:,cn))', r_min, r_max);
    psi(:,cn) = psi(:, cn)/sqrt(area);
    prob(:,cn) = psi(:,cn) .* psi(:,cn);
end

E_matrix = sparse(E_matrix);

% hold on;
% plot(psi(:,1))

nump = 201;
% pqn = 1;
qn = n - l;

prob_density = psi(:, qn) .* psi(:, qn);

dp = 2*r_max/(nump-1);
xp = -r_max : dp : r_max;

k = 0;

for c1 = 1 : nump
    for c2 = 1 : nump
        rp = sqrt(xp(c1)^2 + xp(c2)^2);

        if rp < r_max
 
            if xp(c1) >= 0 & xp(c2) >= 0
                theta = atan(abs(xp(c2)/(xp(c1)+eps)));
            end;
            if xp(c1) <= 0 & xp(c2) >= 0
                theta = pi - atan(abs(xp(c2)/(xp(c1)+eps)));
            end;
            if xp(c1) <= 0 & xp(c2) <= 0
                theta = pi + atan(abs(xp(c2)/(xp(c1)+eps)));
            end;
            if xp(c1) >= 0 & xp(c2) <= 0
                theta = 2*pi - atan(abs(xp(c2)/(xp(c1)+eps)));
            end;
            
            leg01 = legendre(l, cos(theta));
            leg02 = leg01(m+1, :);
            
            N = round(1 + (num-1)*(rp/r_max))
            probcloud(c1, c2) = prob_density(N)*leg02^2;
        else
            probcloud(c1, c2) = 0;
        end   %if
    end   %for c1
end   %for c2

probcloud = probcloud ./ max(max(probcloud));


figure(84)
set(gcf,'Name','Cloud3','NumberTitle','off')
set(gcf,'Units','normalized','Position',[0.3 0.3 0.6 0.6]);
surf(xp,xp,probcloud);
colorbar off;
colormap jet
shading interp;
% title(s);
xlabel('x  (ao)  ');
ylabel('y   (ao) ');
axis off
view(-86,70)

