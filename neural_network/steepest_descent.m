function [layers, Ein] = steepest_descent(layers, epsilon, delta, thresh, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % epsilon is a real number value used in initializing the U configuration for line searching
    % delta is a real number value used for stopping the line search when |eta_1 - eta_3| is smaller than delta
    % thresh is a real number value used for stopping the stochastic descent and line search when |previous_error - error| is smaller than thresh
    % x_data is 3xN
    % y_data is Nx1
    
    init_eta_list = find_best_three_eta(layers, epsilon, x_data, y_data);           % find the initial U configuration for the line search
    eta_list = bisection(layers, init_eta_list, delta, x_data, y_data);             % do first line search

    prev_Ein = 0;                                                                   % set previous_error
    
    end_loop = false;
    
    while end_loop == false                                                         % continue while end conditions not met
        eta_bar = eta_list(2);
        [layers, Ein] = stochastic_descent(layers, eta_bar, x_data, y_data);        % perform stochastic descent
        Ein_diff = abs(prev_Ein - Ein);                                             % compute |previous_error - error|
        
        if Ein_diff < thresh
            end_loop = true;                                                        % if the difference in error is small enough, stop
        end
        
        eta_list = bisection(layers, eta_list, delta, x_data, y_data);              % do line search
    end
end