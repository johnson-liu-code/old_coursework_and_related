function [layers, Ein] = stochastic_descent(layers, eta, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % eta is the learning rate (a real number)
    % x_data is 3xN
    % y_data is Nx1
    
    N = length(x_data);                                         % get the length of x_data
    Ein_total = 0;
    num_layers = length(layers);                                % get the number of layers
    
    for n=1:N                                                   % iterate through the x_data
        x = x_data(:,n);                                        % select one data point
        y = y_data(n);
    
        layers(1).x = x;                                        % through the data point into the input layer
        layers(num_layers).y = y;                               % set the expected y output in the output layer to be equal to y
    
        layers = forward_propagation(layers);                   % forward propagation
        layers = backpropagation(layers);                       % backpropagation
    
        for l=2:num_layers                                      % iterate through the layers
            layers(l).w = layers(l).w - eta*layers(l).grad;     % update the weights
 
        Ein = compute_error(layers);                            % compute the in-sample error given the current weights
        Ein_total = Ein_total + Ein;
        end
    end
    Ein = Ein_total/N;                                          % average the in-sample errors
end