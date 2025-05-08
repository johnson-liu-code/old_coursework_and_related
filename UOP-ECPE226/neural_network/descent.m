function [layers, error] = descent(layers, x, y)
    % this function is not used
    
    theta = @(x) 1./(1+exp(-x));
    thetap = @(x) x.*(1-x);

    num_layers = length(layers);

    layers(1).x = x;

    for l=2:num_layers
        layers(l).s = layers(l).w'*layers(l-1).x;                           % compute signal
        layers(l).x = [1; theta(layers(l).s)];                              % compute output
    end

    x = layers(num_layers).x(2:length(layers(num_layers).x),:);
    layers(num_layers).d = thetap(x).*(x-y);                                % compute delta for last layer

    for l=num_layers-1:-1:2
        x = layers(l).x(2:length(layers(l).x),:);                                            % remove bias
        w = layers(l+1).w(2:length(layers(l+1).w),:);                                          % remove bias weight
        layers(l).d = thetap(x).*(w*layers(l+1).d);                         % compute delta for layer
    end

    for l=2:num_layers
        layers(l).grad = layers(l-1).x*layers(l).d';                        % compute gradient for each layer
    end

    error = .5*(layers(3).x(2:length(layers(3).x),:) - y).^2;
end