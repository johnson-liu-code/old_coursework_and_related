function [error] = compute_temp_error(layers)
    % layers is a multidimensional structure with .w (weights) members

    num_layers = length(layers);                                               % number of layers
    
    error = .5*(layers(num_layers).temp_x(2) - layers(num_layers).y).^2;       % compute the squared error
end