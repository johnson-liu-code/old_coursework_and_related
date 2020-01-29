function [layers, error] = variable_rate_descent(layers, eta, alpha, beta, thresh, x_data, y_data)
    % layers is a multidimensional structure with .w (weights) members
    % eta is the learning rate (a real number)
    % alpha is the learning rate increase factor (a real number)
    % beta is the learning rate decrease factor (a real number)
    % thresh is a real number value for stopping the variable rate descent when |temp_error - error| is smaller than thresh
    % x_data is 3xN
    % y_data is Nx1
    
    [layers, error] = batch_descent(layers, eta, x_data, y_data);                   % do first batch descent
    [temp_layers, temp_error] = batch_descent(layers, alpha*eta, x_data, y_data);   % do another batch descent with a different eta
                                                                                    % temp_error is the error that comes from batch descent using the proposed eta value

    stop = false;

    while stop==false                                                               % continue while stopping criteria is not met
        if abs(temp_error - error) < thresh                                         % if |temp_error - error| is smaller than thresh, stop
            stop = true;
        end

        if temp_error < error                                                       % if temp_error is less than the error, accept the update
            error = temp_error;
            layers = temp_layers;
            eta = alpha*eta;                                                        % change eta by a factor of alpha
        else
            eta = beta*eta;                                                         % else, reject the update and change eta by a factor of beta
        end
        
        [temp_layers, temp_error] = batch_descent(layers, eta, x_data, y_data);     % do batch descent to get the next proposed update

    end

end
%     num_layers = length(layers);
%     N = length(x_data);
    
% %     Ein_total = 0;

%     for n=1:N
%         x = x_data(:,n);
%         y = y_data(n,1);
%         
%         layers(1).x = x;
%         layers(num_layers).y = y;
%     
%         layers = forward_propagation(layers);
%         layers = backpropagation(layers);
%         
%         error = compute_error(layers);
%         Ein_total = Ein_total + error;
%         
%         layers(1).temp_x = layers(1).x;
%         
%         layers = compute_temp(layers, eta);
%         
%         temp_error = compute_temp_error(layers);
% 
%         if temp_error < error
% %             disp('yes')
%             for l=2:num_layers
%                 layers(l).w = layers(l).w - eta*layers(l).grad;
% %                 layers(l).w
%             end
%             
%             eta = alpha*eta;
%             
%         else
% %             disp('no')
%             eta = beta*eta;
%             
%         end
%     end
%     Ein = Ein_total/N;
% end