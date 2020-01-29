function [z] = nonlineartransform(x)
    z = [x(:,1) x(:,2) x(:,1).^2 x(:,1).*x(:,2) x(:,2).^2 x(:,1).^3 x(:,1).^2.*x(:,2) x(:,1).*x(:,2).^2 x(:,2).^3];
end