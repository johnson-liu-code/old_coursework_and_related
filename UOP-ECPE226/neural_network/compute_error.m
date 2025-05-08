function [error] = compute_error(layers)
    % layers is a multidimensional structure with .w (weights) members

    num_layers = length(layers);                                        % number of layers
    error = .5*(layers(num_layers).x(2) - layers(num_layers).y).^2;     % compute squared error
end