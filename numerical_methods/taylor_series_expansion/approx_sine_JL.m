function [ y, theta_range ] = approx_sine_JL ( theta_max, n, resolution )
% ################################################################
% Function to compute the approximation of sin for multiple theta
%   values. The range goes from -theta_max to theta_max.
% 
% Input:
%   1) The upper limit on the angle to be used in the sin
%   approximation.
%   2) n, the number of terms to use in the Taylor Series expansion.
%   3) The number of angles to use within the range of angles.
% 
% Output:
%   1) A vector y containing the approximation for sin(theta) for
%   each theta value.
%   2) A vector theta_range containing all of the theta values used.
% 
% Johnson Liu 20210111
% ################################################################


% Generate range of theta values based on theta_max and the
%   resolution.
theta_range = linspace( -theta_max, theta_max, resolution )';

% Run the sin Taylor Series code on the theta range using n number
%   of terms in the partial sum.
y = sine_JL( theta_range, n );

end