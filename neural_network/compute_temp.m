function [layers] = compute_temp(layers, factor)
    % layers is a multidimensional structure with .w (weights) members
    % factor is a real value number used as a learning rate
    
    % this function computes temporary weights, signals, and outputs for the layers
    theta = @(x) 1./(1+exp(-x));                                    % activation function

    num_layers = length(layers);                                    % number of layers
    for l=2:num_layers
        v = -layers(l).grad;                                        % "velocity"
        layers(l).temp_w = layers(l).w + factor*v;                  % compute the temporary weights
        layers(l).temp_s = layers(l).temp_w'*layers(l-1).temp_x;    % compute the temporary signals
        layers(l).temp_x = [1; theta(layers(l).temp_s)];            % compute the temporary outputs
    end
end