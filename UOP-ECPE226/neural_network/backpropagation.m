function [layers] = backpropagation(layers)
    % layers is a multidimensional structure with .w (weights) members
    thetap = @(x) x.*(1-x);                 % derivative of the activation function

    num_layers = length(layers);            % number of layers

    x = layers(num_layers).x(2:length(layers(num_layers).x),:);     % collect the x output from the last layer while removing the bias
    layers(num_layers).d = thetap(x).*(x-layers(num_layers).y);     % compute delta for last layer

    for l=num_layers-1:-1:2                                         % iterate over the layers backwards
        x = layers(l).x(2:length(layers(l).x),:);                   % remove bias
        w = layers(l+1).w(2:length(layers(l+1).w),:);               % remove bias weight
        layers(l).d = thetap(x).*(w*layers(l+1).d);                 % compute delta for the layer
    end

    for l=2:num_layers                                              % iterate over the layers
        layers(l).grad = layers(l-1).x*layers(l).d';                % compute the gradient for each layer
    end
end