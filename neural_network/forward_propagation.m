function [layers] = forward_propagation(layers)
    % layers is a multidimensional structure with .w (weights) members

    theta = @(x) 1./(1+exp(-x));                    % activation function

    num_layers = length(layers);                    % get the number of layers

    for l=2:num_layers                              % iterate through the layers
        layers(l).s = layers(l).w'*layers(l-1).x;   % compute the signal for each layer
        layers(l).x = [1; theta(layers(l).s)];      % compute output of each layer
    end
end