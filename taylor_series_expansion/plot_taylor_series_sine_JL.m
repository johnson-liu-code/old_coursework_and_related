% ################################################################
% Code to run the approx_sine_JL function while iterating over
%   theta_max and the number of terms used in the Taylor Series
%   partial sum.
% 
% Johnson Liu 20210111
% ################################################################

% The maximum theta value to use when computing the approximation
%   to the sin function.
% theta_max = pi;
theta_max = 2*pi;

% The list of n number of terms to use in the partial sum.
% i = linspace( 1, 5, 5 );
% i = linspace( 4, 8, 2 );
i = [6, 7, 8, 9, 10];

% The number of theta values to use in the computation of the
%   approximation to the sin function.
resolution = 40;

% Start a figure and set its title.
figure
hold on
str = ['$\theta_{\textrm{max}}$ = ', sprintf('%f', theta_max), sprintf('\nResolution = %d', resolution) ];
title( str, 'interpreter', 'latex', 'fontsize', 18 )

% Iterate over the n number of terms to use.
for n = i
    % Compute the approximation to the sin function using the given
    %   theta_max value, n number of terms, and resolution.
    [ y, theta ] = approx_sine_JL( theta_max, n, resolution );
    % Plot the result.
    plot( theta, y, '+', 'markersize', 8, 'linewidth', 1, 'displayname', sprintf('n = %d', n) )
end

% Plot MATLAB's expected sin function.
x = linspace(-theta_max, theta_max, 100);
sine = sin( x );
plot( x, sine, 'displayname', 'Expected sine function' )

% Give the figure labels.
xlabel('$\theta$', 'interpreter', 'latex', 'fontsize', 14)
ylabel('$y$', 'interpreter', 'latex', 'rotation', 0, 'fontsize', 14)
grid
xlim( [-theta_max theta_max] )
legend('location', 'southwest')