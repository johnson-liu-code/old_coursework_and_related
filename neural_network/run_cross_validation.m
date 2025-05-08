
clear                                             % clear variables
rand('seed', 1994);                               % seed random number generator

load('usps_modified.mat');                        % load x and y data into variable called data
[x, y] = getfeatures(data);                       % extract symmetry and intensity features (x data becomes 2x5000)
[N, M] = size(x);                                 % get size of x data
x_data = [ones(N,1) x]';                          % add 1's to the x data (for bias)
y(y~=1) = 0;                                      % change all y values that are not equal to 1 to 0
y_data = y;

split = randperm(5000);                           % randomize indices
cv_x_data = x_data(:, split(1:1000));             % collect cross-validation x data
cv_y_data = y_data( split(1:1000) );              % collect cross-validation y data

num_layers = 3;                                   % number of layers
layers(1:num_layers,1) = struct;                  % create the layer structures
layers(2).w = (rand(3,5)-.5)*2;                   % randomize the weights for layers 2 and 3 with random values between -1 and 1
layers(3).w = (rand(6,1)-.5)*2;                   % first index in rand must be the second index in the previous rand plus one (for the bias)

iteration_limit = 10;                             % number of iterations
k = 10;                                           % number of subgroups

Eout_over_eta = [];

eta_list = logspace(-3,1.7,40);                   % set eta values

descent_type = "stochastic";

for eta=eta_list
    Eout = cross_validation(layers, descent_type, eta, k, iteration_limit, cv_x_data, cv_y_data);   % perform cross-validation
    Eout_over_eta = [Eout_over_eta Eout];                                                           % collect error as a function of eta
end
