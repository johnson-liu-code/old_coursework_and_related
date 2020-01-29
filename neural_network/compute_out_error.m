function [Eout] = compute_out_error(layers, test_x_data, test_y_data)
    % layers is a multidimensional structure with .w (weights) members
    % test_x_data is 3xN
    % test_y_data is Nx1
    
    N = length(test_x_data);                        % length of test_x_data                   
    num_layers = length(layers);                    % number of layeres
    Eout_total = 0;
    
    for n=1:N                                       % iterate over the data points
        layers(1).x = test_x_data(:,n);             % set the input data
        layers(num_layers).y = test_y_data(n);      % set the expected output
        layers = forward_propagation(layers);       % forward propagation
        error = compute_error(layers);              % compute the error
        Eout_total = Eout_total + error;
    end
    
    Eout = Eout_total/N;                            % average the out-sample error over all of the data points
end