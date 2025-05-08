%% Evolutionary Algorithm Example
% Dr. David Mueller
% 
% Computational Intelligence
%% Problem Statement:
% Use a genetic algorithm to find the global optimum of the following objective 
% function:
% 
% $$f(x,y)=\exp\left( \frac{-\left[ (x-3)^2+(y-3)^2\right]}{5} \right) +\exp\left( 
% \frac{-\left[ x^2+(y+3)^2\right]}{5} \right) + 0.2\left[ \cos\left(\frac{x\pi}{2}\right) 
% + \cos\left(\frac{y\pi}{2}\right)\right] +5$$

objf = @(x,y) exp(-((x-3).^2+(y-3).^2)./5) + 0.8.*exp(-(x.^2+(y+3).^2)./5) + 0.2*(cos(x.*pi./2)+cos(y.*pi./2)) + 0.5;
%% 
% Mathematically we know this function has a maximum height of 1.6903 in 
% the range of -5 to 5 for x and y.

[x,y]=meshgrid(-5:0.05:5);
mesh(x,y,objf(x,y));

xlim([-5.00 5.00])
ylim([-5.00 5.00])
zlim([0.00 2.00])
xlabel('$x$', 'interpreter', 'latex')
ylabel('$y$', 'interpreter', 'latex')
zlabel('$f(x,y)$', 'interpreter', 'latex')

view([-112.50 -13.80])
%{
%% Methods:
% * Representation: Binary
% * Selection: Elitist, Rank Selection
% * Mating/Variation: Single Point Binary Crossover, Uniform Crossover
%% Initialize Parameters
% For a genetic algorithm, the important parameters are population size, number 
% of generations to execute, fraction of population seleected for mating, the 
% data representation, and the range of data.

clearvars
% ***** User Changable Variables ***** %
pop = 40;               %population size
gen = 1;              %number of generations
pcntsel = 0.5;          %fraction of candidated selected for next generation

precision = 8;          %precision of real number represenation (ex. 8 -> 8-bit represenation)
range = [-5 5; -5 5];   %bounds for input variables

% ***** Calculations ***** %
mu = round(pcntsel*pop);    %number of parents selected
lambda = pop - mu;          %number of new candidates in each generation (children)
%% Generate Initial Population
% Generally, the initial population is generated randomly within specified ranges. 

candidate.binx = rand(pop,precision)>0.5;   %generate binary representation
candidate.biny = rand(pop,precision)>0.5;
%% Genetic Algorithm
%%
for i = 1:gen
    
    % ********* Convert Representation ****** %
    % candidate.x = (range(1,1)-range(1,2))*(bi2de(candidate.binx)/(2^precision-1))+range(1,2);
    % candidate.y = (range(2,1)-range(2,2))*(bi2de(candidate.biny)/(2^precision-1))+range(2,2);
    candidate.x = (range(1,1)-range(1,2))*(binary_to_decimal(candidate.binx)/(2^precision-1))+range(1,2);
    candidate.y = (range(2,1)-range(2,2))*(binary_to_decimal(candidate.biny)/(2^precision-1))+range(2,2);
    % *************************************** %
    
    % ********* Get Fitness ***************** %
    candidate.fit = objf(candidate.x,candidate.y)
    % *************************************** %
    
    % ********* Selection ******************* %
    % Linear (Roulette Wheel) Selection
    fitsum = sum(candidate.fit);
    candidate.p = candidate.fit./fitsum;
    candidate.ps = cumsum(candidate.p);
    
    % *************************************** %
    
    % ********* Create Offspring ************ %
    
    % *************************************** %
    
    % ********* Next Generation ************* %
    
    % *************************************** %
end
%}
%% Results and Conclusions