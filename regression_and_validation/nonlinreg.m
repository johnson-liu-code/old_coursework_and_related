function [N, z, w_reg, add_err] = nonlinreg(x, y, lambda)
[N, d] = size(x);
xx = x';
x1 = xx(1,:);
x2 = xx(2,:);
z = [ones(1, N); x1; x2; x1.^2; x1.*x2; x2.^2; x1.^3; (x1.^2).*x2; x1.*(x2.^2); x2.^3]';
[p, m] = size(z);
t = (z'*z + lambda*eye(m));
w_reg = inv(t) * z' * y;
add_err = (lambda/N) * w_reg'*w_reg;
end