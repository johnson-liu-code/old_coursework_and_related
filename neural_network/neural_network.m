
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

train_x_data = x_data( :, split(1001:4000) );     % collect training x data
train_y_data = y_data( split(1001:4000) );        % collect training y data

test_x_data = x_data( :, split(4001:5000) );      % collect test x data
test_y_data = y_data( split(4001:5000) );         % collect test y data

% type_of_descent = "batch";                      % select descent method
% type_of_descent = "stochastic";
% type_of_descent = "variable";
type_of_descent = "steepest";

num_layers = 3;                                   % number of layers
layers(1:num_layers,1) = struct;                  % create the layer structures

iteration_limit = 100;                            % number of iterations
alpha = 1.1;                                      % learning rate increase factor
beta = .5;                                        % learning rate decrease factor
epsilon = .1;                                     % epsilon value used for initializing U configuration for the line search in steepest descent
delta = .1;                                       % stopping criterion for |eta_1 - eta_3| in line search in steepest descent
thresh = 1e-2;                                    % stopping criterion for |previous_error - error| in variable and steepest descent

% eta = 10^0;                                     % learning rate
% eta = .5913;
eta = 10^1.1;

trials = 1;                                       % number of trials

% final_Ein_list = [];
% final_Eout_list = [];

for t=1:trials
    Ein_over_time = [];                           % start array to save in-sample error as a function of iteration
    Eout_over_time = [];                          % start array to save out-sample error as a function of iteration
    
    layers(2).w = (rand(3,5)-.5)*2;               % randomize the weights for layers 2 and 3 with random values between -1 and 1
    layers(3).w = (rand(6,1)-.5)*2;               % first index in rand must be the second index in the previous rand plus one (for the bias)

%     run_loop = true;                              % continue running until run_loop is set equal to false

%     while run_loop
        for i=1:iteration_limit                          % run through iterations
            if type_of_descent == "batch"                % run batch descent
                [layers, Ein] = batch_descent(layers, eta, train_x_data, train_y_data);
                Ein_over_time = [Ein_over_time Ein];

                Eout = compute_out_error(layers, test_x_data, test_y_data);
                Eout_over_time = [Eout_over_time Eout];

            elseif type_of_descent == "stochastic"       % run stochastic descent
                [layers, Ein] = stochastic_descent(layers, eta, train_x_data, train_y_data);
                Ein_over_time = [Ein_over_time Ein];
                
                Eout = compute_out_error(layers, test_x_data, test_y_data);
                Eout_over_time = [Eout_over_time Eout];

            elseif type_of_descent == "variable"         % run variable rate descent
                [layers, Ein] = variable_rate_descent(layers, eta, alpha, beta, thresh, train_x_data, train_y_data);
                Ein_over_time = [Ein_over_time Ein];

                Eout = compute_out_error(layers, test_x_data, test_y_data);
                Eout_over_time = [Eout_over_time Eout];
                
            elseif type_of_descent == "steepest"         % run steepest descent
                [layers, Ein] = steepest_descent(layers, epsilon, delta, thresh, train_x_data, train_y_data);
                Ein_over_time = [Ein_over_time Ein];
                
                Eout = compute_out_error(layers, test_x_data, test_y_data);
                Eout_over_time = [Eout_over_time Eout];
            end
        end
%         run_loop = false;
%     end
%     final_Ein_list = [final_Ein_list Ein_over_time(iteration_limit)];
%     final_Eout_list = [final_Eout_list Eout_over_time(iteration_limit)];
end

% while run_loop
%     for i=1:iteration_limit
%         if type_of_descent == "batch"   
%             total_grad_layer_2 = 0;
%             total_grad_layer_3 = 0;
%         end
% 
%         total_error = 0;
% 
%         for n=1:N
%             x = x_data(:,n);
%             y = y_data(n,1);
% 
%             [layers, error] = descent(layers, x, y);
%             
%             total_error = total_error + error;
% 
%             if type_of_descent == "stochastic"
%                 for l=2:num_layers
%                     layers(l).w = layers(l).w - eta*layers(l).grad;                     % update the weights
%                 end
% 
%             elseif type_of_descent == "batch"
%                 total_grad_layer_2 = total_grad_layer_2 + layers(2).grad;
%                 total_grad_layer_3 = total_grad_layer_3 + layers(3).grad;
%                 
%             elseif type_of_descent == "variable"
%                 v_2 = -layers(2).grad;
%                 v_3 = -layers(3).grad;
%                 
%                 [layers, temp_error] = descent(layers, x, y);
%             end
%         end
%         if type_of_descent == "batch"
%             grad_layer_2 = total_grad_layer_2/N;
%             grad_layer_3 = total_grad_layer_3/N;
% 
%             layers(2).w = layers(2).w - eta*grad_layer_2;
%             layers(3).w = layers(3).w - eta*grad_layer_3;
%         end
% 
%         Ein = total_error/N;
% 
%         Ein_over_time = [Ein_over_time Ein];
%         
%         if Ein < 1e-4
%             disp('small error');
%             run_loop = false;
%             break
%         end
%         
%         if abs(Ein - prev_Ein) < 1e-4
%             disp('small change in Ein');
%             run_loop = false;
%             break
%         end
%         
%         prev_Ein = Ein;
%     end
%     run_loop = false;
% end