function [epsilon_list, errors] = find_best_three_eta(layers, epsilon, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % epsilon is a realy number value used in finding the first three points for the line search
    % x_data is 3xN
    % y_data is Nx1

    save_layers = layers;

    epsilon_list = zeros(1,3);              % make array to store epsilon values
    epsilon_list(1) = 0;
    epsilon_list(2) = epsilon;
        
    errors = zeros(1,3);                    % make array to store errors associated with the stored epsilon values
    
    [layers, errors(1)] = stochastic_descent(save_layers, epsilon_list(1), x_data, y_data);     % perform stochastic descent for the first epsilon value 
    [layers, errors(2)] = stochastic_descent(save_layers, epsilon_list(2), x_data, y_data);     % perform stochastic descent for the second epsilon value
        
    if errors(2) < errors(1)
        epsilon_list = [0 epsilon 2*epsilon];       % if E(epsilon_2) < E(epsilon_1), initialize epsilon array to [0, epsilon, 2*epsilon]
    else
        epsilon_list = [epsilon 0 -epsilon];        % else, initialize epsilon array to [epsilon 0 -epsilon]
        
    [layers, errors(3)] = stochastic_descent(save_layers, epsilon_list(3), x_data, y_data);     % perform stochastic descent for the third epsilon value
    
    if errors(3) > errors(2)
        found_three = true;                         % if E(epsilon_3) > E(epsilon_2), the first three epsilon values to use in the line search has been found
    end

    found_three = false;
    
    while found_three == false
        [layers, new_error] = stochastic_descent(save_layers, 2*epsilon_list(3), x_data, y_data);   % perform stochastic descent for the next epsilon value

        if new_error > errors(3)
            found_three = true;                     % if E(epsilon_3) > E(epsilon_2), the first three epsilon values to use in the line search has been found
        end
        
        errors = [errors(2) errors(3) new_error];   % update array of errors
        epsilon_list = [epsilon_list(2) epsilon_list(3) 2*epsilon_list(3)];         % update epsilon list
    end
    
    errors;
end