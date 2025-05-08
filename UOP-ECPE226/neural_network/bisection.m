function [eta_list] = bisection(layers, eta_list, delta, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % eta_list is a 1x3 array of real number values
    % x_data is 3xN
    % y_data is Nx1
    
    eta_bar = .5*(eta_list(1) + eta_list(3));               % compute eta_bar

    save_layers = layers;                                   % save a copy of the original layers
    
    errors = zeros(1,3);                                    % create an array to store the errors
    
    while abs( eta_list(1)-eta_list(3) ) > delta            % continue while the difference between eta_1 and eta_3 is greater than delta
        [layers, errors(1)] = stochastic_descent(save_layers, eta_list(1), x_data, y_data);         % stochastic descent for eta_1
        [layers, errors(2)] = stochastic_descent(save_layers, eta_list(2), x_data, y_data);         % stochastic descent for eta_2
        [layers, errors(3)] = stochastic_descent(save_layers, eta_list(3), x_data, y_data);         % stochastic descent for eta_3
        [layers, error_bar] = stochastic_descent(save_layers, eta_bar, x_data, y_data);
        
        if error_bar > errors(2)                            % if E(eta_bar) > E(eta_2), select eta_bar, eta_2, and eta_3 for the next line search
            eta_list = [eta_bar eta_list(2) eta_list(3)];
        else                                                % else, select eta_1, eta_bar, and eta_2 for the next line search
            eta_list = [eta_list(1) eta_bar eta_list(2)];
        end
        
        eta_bar = .5*(eta_list(1) + eta_list(3));           % compute eta_bar
    end
end