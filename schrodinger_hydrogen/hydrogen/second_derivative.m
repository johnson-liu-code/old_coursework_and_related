

function SD_matrix = second_derivative(num, dr)

% off = ones(num-3, 1);
% SD_matrix = ( -2*eye(num-2) + diag(off, 1) + diag(off, -1) )/ dr^2;
SD_matrix = sparse(toeplitz([-2 1 zeros(1, num-4)]) / dr^2 );

end
