

load('usps_modified.mat');
[x, y] = getfeatures(data);                     % Get symmetry and intensity features.
y(y~=1) = -1;                                   % Change non-1 labels to -1's.
z = nonlineartransform(x);                      % Apply non-linear transformation.

avg_in_err_list = [];                           % List for storing average Ein for each lambda value.
avg_out_err_list = [];                          % List for storing average Eout for each lambda value.

avg_w_list = [];                                % List for storing average weight vector for each lambda value.

% lambda_values = linspace(.001, 1, 100);       % Lambda values.
lambda_values = [.001 .01 .1 .25 .5 .75 1];
% lambda_values = [1];

for lambda=lambda_values                        % Iterage over lambda values.
    in_err_list = [];                           % List to store Ein.
    out_err_list = [];                          % List to store Eout.
    w_list = [];                                % List to store weight vectors.
    
    for i=0:9                                   % Pick out sub-sets of the data to use as the out-sample.
        z_in = [];
        z_out = [];
        y_in = [];
        y_out = [];

        for j=0:9
            if j~=i
                for k=0:9
                    z_in = [z_in; z( (k*500) + j*50+1:(k*500) + (j+1)*50, :)];      % Pick out specific data.
                    y_in = [y_in; y( (k*500) + j*50+1:(k*500) + (j+1)*50, :)];
                end
            else
                for k=0:9
                    z_out = [z_out; z( (k*500) + j*50+1:(k*500) + (j+1)*50, :)];
                    y_out = [y_out; y( (k*500) + j*50+1:(k*500) + (j+1)*50, :)];
                end
            end
        end
        
        w = linreg(z_in, y_in, lambda);                         % Compute w_reg.
        w_list = [w_list; w'];                                  % Append w_reg to w list.
        
        [N,d1] = size(z_in);                                    % Get size of in-sample data.
        z_in = [ones(1,N); z_in'];                              % Append ones to the in-sample data.
        in_error = (1/N) * sum(sign(w'*z_in)' ~= y_in);         % Compute the in-error.

        [M,d2] = size(z_out);                                   % Get size of out-sample data.
        z_out = [ones(1,M); z_out'];                            % Append ones to the out-sample data.
        out_error = (1/M) * sum(sign(w'*z_out)' ~= y_out);      % Compute the out-error.
        
        in_err_list = [in_err_list; in_error];                  % Append the in-error to list.
        out_err_list = [out_err_list; out_error];               % Append the out-error to list.
    end
    
    avg_in_err = sum(in_err_list)/10;                           % Compute average in-error for all of the sub-groupings.
    avg_out_err = sum(out_err_list)/10;                         % Compute average out-error for all of the sub-groupings.
    
    avg_w = mean(w_list,1);                                     % Compute the average weight vector for all of the sub-groupings.
    avg_w_list = [avg_w_list; avg_w];                           % Append the average weight to list.
    
    avg_in_err_list = [avg_in_err_list; avg_in_err];            % Append the average in-error to list.
    avg_out_err_list = [avg_out_err_list; avg_out_err];         % Append the average out-error to list.
end

% num_in_sample_one = 400;
% num_in_sample_not_one = 800;
% x_sample = [x(1:num_in_sample_one, :); x(501:501+num_in_sample_not_one-1, :)];
% y_sample = [y(1:num_in_sample_one); y(501:501+num_in_sample_not_one-1)];
% y_sample(find(y_sample~=1)) = -1;
% 
% [M_all, d] = size(x)
% [M_sample, d] = size(x_sample)
% 
% xx = x';
% x1 = xx(1,:);
% x2 = xx(2,:);
% 
% xx_sample = x_sample';
% x1_sample = xx_sample(1,:);
% x2_sample = xx_sample(2,:);
% 
% z_all = [ones(1, M_all); x1; x2; x1.^2; x1.*x2; x2.^2; x1.^3; (x1.^2).*x2; x1.*(x2.^2); x2.^3]';
% z_sample = [ones(1, M_sample); x1_sample; x2_sample; x1_sample.^2; x1_sample.*x2_sample; x2_sample.^2; x1_sample.^3; (x1_sample.^2).*x2_sample; x1_sample.*(x2_sample.^2); x2_sample.^3]';
% 
% % lambda_values = [0.001 0.01 0.1 0.25 0.5 0.75 1];
% lambda_values = linspace(.001, 5, 10000);
% aug_and_out_error = [];
% 
% for lambda=lambda_values
%     [N, z_sample, w, add_error] = nonlinreg(x_sample, y_sample, lambda);
%     in_sample_error = (1/N) * sum(sign(w'*z_sample')' ~= y_sample);
% 
%     [M, d] = size(x);
%     y(find(y_sample~=1)) = -1;
% 
%     aug_error = in_sample_error + add_error;
%     out_sample_error = (1/M) * sum(sign(w'*z_all')' ~= y);
%     
%     aug_and_out_error= [aug_and_out_error; aug_error out_sample_error];
% end