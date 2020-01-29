function [dist] = euc_dist(x, v)
    % x and v are 1 by D vectors
    dist = (x-v) * (x-v)';
end