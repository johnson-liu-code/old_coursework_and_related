
rand('seed', 1994);

file_name = '/home/jliu/Desktop/files/class/ECPE_226_computational_intelligence/usps_data/usps_modified.mat';
load(file_name);
[x, y] = getfeatures(data);

% learning_rate = 1;
% learning_rate_list = [.1 1 10 50]; % 1,2,3,4
% learning_rate = .1;
% learning_rate = 1;
% learning_rate = 10;
% learning_rate = 50;
% convg_type = 1;
% 1: stop when the gradient is small enough
% 2: stop when the gradient has not changed significantly in the past n iterations
% 3: stop when the error is small enough
% 4: stop when the error has not changed significantly in the past n iterations
% convg_type_list = [1 2 3];
convg_type_list = [1];
% thresh_list = linspace(1e-2,1e-1, 100);
% thresh_list = logspace(-3,-1);
thresh_list = [.1];
init_w = [-1 + (2)*rand(3, 1)];


% hold on
% grid on

% for convg_type=convg_type_list
    in_err_list = [];
%     out_err_list = [];

%     for thresh=thresh_list
        [w_over_time1, gradient_over_time1, in_err_over_time1, out_err_over_time1] = logistic_regression(x, y, init_w, .1, 1, 1e-2, 'batch');
        in_err_size = size(in_err_over_time1);
        final_in_err = in_err_over_time1(1,in_err_size(2));
        in_err_list = [in_err_list final_in_err];
%         out_err_size = size(out_err_over_time1);
%         final_out_err = out_err_over_time1(1,out_err_size(2));
%         out_err_list = [out_err_list final_out_err];
%     end
%     plot(thresh_list, in_err_list)
%     plot(thresh_list, out_err_list)
% end
w_list_size = size(w_over_time1);
w = w_over_time1(:,w_list_size(2)-2);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time2, gradient_over_time2, in_err_over_time2, out_err_over_time2] = logistic_regression(x, y, init_w, 1, 1);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time3, gradient_over_time3, in_err_over_time3, out_err_over_time3] = logistic_regression(x, y, init_w, 10, 1);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time4, gradient_over_time4, in_err_over_time4, out_err_over_time4] = logistic_regression(x, y, init_w, 50, 1);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time5, gradient_over_time5, in_err_over_time5, out_err_over_time5] = logistic_regression(x, y, init_w, learning_rate, convg_type);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time6, gradient_over_time6, in_err_over_time6, out_err_over_time6] = logistic_regression(x, y, init_w, learning_rate, convg_type);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time7, gradient_over_time7, in_err_over_time7, out_err_over_time7] = logistic_regression(x, y, init_w, learning_rate, convg_type);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time8, gradient_over_time8, in_err_over_time8, out_err_over_time8] = logistic_regression(x, y, init_w, learning_rate, convg_type);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time9, gradient_over_time9, in_err_over_time9, out_err_over_time9] = logistic_regression(x, y, init_w, learning_rate, convg_type);
% init_w = [-1 + (2)*rand(3, 1)];
% [w_over_time10, gradient_over_time10, in_err_over_time10, out_err_over_time10] = logistic_regression(x, y, init_w, learning_rate, convg_type);






x_space = linspace(-1, .4);
x2 = -w(2)/w(3) * x_space - w(1)/w(3);

hold on
grid on
scatter(x(1:500,1), x(1:500,2))
scatter(x(501:5000,1), x(501:5000,2))
plot(x_space, x2, 'color', 'black')
xlabel('$x_1$', 'interpreter', 'latex')
ylabel('$x_2$', 'interpreter', 'latex')
legend('Digit 1 Samples', 'Digits 2-0 Samples', 'Final Hypothesis Line', 'location', 'best')
