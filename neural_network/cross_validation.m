function [Eout] = cross_validation(layers, descent_type, eta, k, iteration_limit, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % descent_type ist the type of gradient descent (batch or stochastic)
    % eta is a real number value and is used for as the learning rate
    % k is the length of each subgroup
    % iteration limit specifies the maximum number of iterations to run for the cross-validation
    % x_data is 3xN
    % y_data is Nx1
    
    N = length(x_data);         % Length of data set
    K = N/k;                    % Size of each subgroup
                                % k is the number of subgroups
    l = length(layers);         % number of layers
    
    Eout_total_all = 0;
    
    for i=0:k-1                 % iterate over subgroups
        Eout_total = 0;
        
        x_in = [];
        y_in = [];

        for j=0:k-1
            if j~=i             % collect the in-sample for the chosen subgroup
                x_in = [x_in x_data( :, j*K+1 : (j+1)*K) ];
                y_in = [y_in; y_data( j*K+1 : (j+1)*K ) ];
            else                % collect the out-sample for the chosen subgroup
                x_out = [x_data( :, j*K+1 : (j+1)*K) ];
                y_out = [y_data( j*K+1 : (j+1)*K ) ];
            end
        end
         
        for it=1:iteration_limit                    % perform gradient descent
            if descent_type == "batch"
                [layers, Ein] = batch_descent(layers, eta, x_in, y_in);
            elseif descent_type == "stochastic"
                [layers, Ein] = stochastic_descent(layers, eta, x_in, y_in);
            end
        end

        out_length = length(x_out);                 % length of out-sample

        for o=1:out_length                          % iterate over out-sample data points
            layers(1).x = x_out(:,o);               % specify the input for the input layer
            layers = forward_propagation(layers);   % forward propagation
            layers(l).y = y_out(o);                 % set the expected output
        
            Eout = compute_error(layers);           % compute the error given the current weights
        
            Eout_total = Eout_total + Eout;
        end
        Eout_total = Eout_total/out_length;         % average the total out-sample error for one specific subgroup
        
        Eout_total_all = Eout_total_all + Eout_total;
    end
    
    Eout = Eout_total_all/k;                        % average the average out-sample error across all subgroups
    
end