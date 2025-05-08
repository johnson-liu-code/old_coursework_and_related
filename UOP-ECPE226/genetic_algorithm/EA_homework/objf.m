function [value] = objf(x,y)
    % an objective function
    value = exp(-((x-3).^2+(y-3).^2)./5) + exp(-(x.^2+(y+3).^2)./5) + 0.2*(cos(x.*pi./2)+cos(y.*pi./2)) + 0.5;
end
