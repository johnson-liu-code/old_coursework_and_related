
xmin = -2;
xmax = 2;
ngrid = 1000;
delta = (xmax-xmin)/ngrid;
x = xmin:delta:xmax;
A = ones(ngrid+1, 1)*x;
B = x'*ones(1, ngrid+1);
M = A+1i*B;

C = zeros(ngrid, ngrid);

iter = 100;

for i=1:ngrid
    for j=1:ngrid
%         disp(M(i, j));
        z = M(i, j);
        for n=1:iter
%             z = z - (z^3 + 7)/(3*z^2);
            z = z - (z^3 - 1)/(3*z^2);
%             z = z - (z^5 - z^3 + 1)/(5*z - 3*z^2);
%             z = z - (z^7 - 1)/(7*z^6);
%             z = z - (z^9 - z^7 + z^5 - z^3 + z - 1)/(9*z^8 - 7*z^6 + 5*z^4 - 3*z^2 + 1);
        end
        C(i, j) = z;
    end
end

% xrange = 0:50:100;
% xlabel = {'-2', '0', '2'};
xticklabels = -2:2:2;
xticks = linspace(1, size(C, 2), numel(xticklabels));

imagesc(angle(C));
set(gca, 'YDir', 'normal')
set(gca, 'Xtick', xticks, 'XTickLabel', xticklabels)
set(gca, 'Ytick', xticks, 'YTickLabel', xticklabels)
pbaspect([1 1 1])
% colormap cool