function [layers, Ein] = batch_descent(layers, eta, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % eta is a real number value and is used as the learning rate
    % x_data is 3xN
    % y_data is Nx1
    
    num_layers = length(layers);                        % number of layers
    N = length(x_data);                                 % length of x_data
    
    Ein_total = 0;
    
    total_change_gradient(1:num_layers,1) = struct;     % create structure to save the total change in gradient
    
    for l=2:num_layers                                  % iterate over the layers
        total_change_gradient(l).change_gradient = zeros(size(layers(l).w));    % create array to save the change in gradient
    end
    
    for n=1:N                                           % iterate over the data points
        x = x_data(:,n);                                % select a data point
        y = y_data(n,1);                                
        
        layers(1).x = x;                                % set the x value of the data point as the input in the input layer
        layers(num_layers).y = y;                       % set the y value of the data point as the expected output of the output layer
    
        layers = forward_propagation(layers);           % forward propagation
        layers = backpropagation(layers);               % backpropagation
        
        for l=2:num_layers                              % iterate over the layers
            total_change_gradient(l).change_gradient = total_change_gradient(l).change_gradient + layers(l).grad;   % add to the total change in gradient
        end
        
        Ein = compute_error(layers);                    % compute the error
        Ein_total = Ein_total + Ein;
    end
    
    for l=2:num_layers                                  % iterate over the layers
        layers(l).w = layers(l).w - (1/N)*eta*total_change_gradient(l).change_gradient;     % update the weights
    end
    
    Ein = Ein_total/N;                                  % compute the average error over all of the data points
end