function y = sine_JL ( theta, n )
% ################################################################
% Function to return the approximate value of sin(theta)
%   using n terms in the Taylor Series expansion for sin.
% 
% Input:
%   1) theta (angle) for the sin function.
%   2) n, the number of terms to use in the Taylor Series expansion.
% 
% Output:
%   1) The partial sum up to n terms.
% 
% Johnson Liu 20210111
% ################################################################

% Create an array of x values to be inputs in the partial
%   sum up to n in the Taylor Series expansion.
j = linspace(0, n-1, n);

% Ignore. --------------------------------------------------------
%%% neg_1 =(-1).^j
%%% pow = 2.*j + 1
%%% x = theta.^(2.*j + 1)
% ----------------------------------------------------------------

% Compute each of the terms in the partial sum of the
%   Taylor Series expansion.
a = ( ( (-1).^j ) .* theta.^(2.*j + 1) ) ./ factorial(2.*j + 1);

% Add up the terms.
y = sum(a, 2);

end