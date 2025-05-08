

function [w_over_time, gradient_over_time, in_err_over_time, out_err_over_time] = logistic_regression(x, y, init_w, learning_rate, convg_type, thresh, type)
    x_train = [x(1:400,:)];                   % digit 1 data
    x_train = [x_train;x(501:900,:)];         % digit 2 data
    x_train = [x_train;x(1001:1400,:)];       % digit 3 data
    x_train = [x_train;x(1501:1900,:)];       % digit 4 data
    x_train = [x_train;x(2001:2400,:)];       % digit 5 data
    x_train = [x_train;x(2501:2900,:)];       % digit 6 data
    x_train = [x_train;x(3001:3400,:)];       % digit 7 data
    x_train = [x_train;x(3501:3900,:)];       % digit 8 data
    x_train = [x_train;x(4001:4400,:)];       % digit 9 data
    x_train = [x_train;x(4501:4900,:)];       % digit 0 data
    s = size(x_train);
    x_train = [ones(s(1),1) x_train];
    x_train = x_train';

    y_train = [ones(400,1)];
    y_train = [y_train;zeros(3600,1)];
    y_train(find(y_train == 0)) = -1;
    
    y = [ones(500,1)];
    y = [y;zeros(4500,1)];
    y(find(y == 0)) = -1;
    
    N = size(y_train);
    M = size(y);

    x = [ones(M(1),1) x]';
    
    w_over_time = [];
    w = init_w;
    w_over_time = [w];
    
    stop = false;
 
%     gradient_thresh = 1e-2;
%     error_thresh = 1e-2;

 gradient_thresh = thresh;
 error_thresh = thresh;
    gradient_over_time = [];
    in_err_over_time = [];
    out_err_over_time = [];
    
    while stop==false
        if strcmp(type, 'batch')
            g = -(-1/N(1)) .* sum( (y_train'.*x_train) ./ (1+exp( y_train'.*( w'*x_train ) ) ), 2);
            w = w + learning_rate*g;
        elseif strcmp(type, 'stochastic')
            i = randi([1 N(1)], 1);
%             y_train(i) * w'*x_train(:,i)
            g = y_train(i)*x_train(:,i) / (1+exp(y_train(i) .* w'*x_train(:,i) ));
            w = w + learning_rate*g;
        end
        in_err = (1/N(1)) * sum(sign(w'*x_train)' ~= y_train);
        out_err = (1/M(1)) * sum(sign(w'*x)' ~= y);

        w_over_time = [w_over_time w];
        gradient_over_time = [gradient_over_time g];
        in_err_over_time = [in_err_over_time in_err];
        out_err_over_time = [out_err_over_time out_err];

        s = size(gradient_over_time);
        
        if convg_type == 1
            if abs(g) <= gradient_thresh
                stop = true;
            end
        elseif convg_type == 2
            if s(2) > 100
                if  abs( g - gradient_over_time(:,s(2) - 100) ) <= gradient_thresh
                    stop = true;
                end
            end
        elseif convg_type == 3
            if in_err <= error_thresh
                stop = true;
            end
        elseif convg_type == 4
            if s(2) > 100
                if abs( in_err - in_err_over_time(s(2) - 100) ) <= error_thresh
                    stop = true;
                end
            end
        end
    end