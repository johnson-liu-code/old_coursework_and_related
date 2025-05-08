
rand('seed', 1994);


w = [-1 + (2).*rand(3, 1)];
% initial_weight = [0;1;1];
% initial_weight = [-.1678;.2567;.5505];

% hypothesis_w_list = single_perceptron(200, initial_weight, 1000);

% w = [-.1678;13.982;-13.5078];
% num_dots = 10:10:3000;
% repeat = 1000;
% percent_correct = percent_correct_perceptron(num_dots, w, repeat);
% plot(num_dots, percent_correct)
% grid on
% set(gca, 'GridLineStyle', '--')
% xlabel('Number of Data Points', 'interpreter', 'latex')
% ylabel('Percent Correctly Classified', 'interpreter', 'latex')
% pbaspect([1 1 1])

% hypothesis_w_list = alternative_perceptron(100, initial_weight, .0001, 1000)
% plot(hypothesis_w_list)
% grid on
% set(gca, 'GridLineStyle', '--')
% xlabel('Iteration', 'interpreter', 'latex')
% ylabel('Weights', 'interpreter', 'latex')
% legend('$w_0$', '$w_1$', '$w_2$', 'interpreter', 'latex', 'location', 'best')
% pbaspect([1 1 1])

% w = [-0.1041;9.0380;-8.7078];
% w = [0.0080;1.1372;-1.0712];
% w = [0.4329;-0.5313;0.3321];
percent_correct = validate_alternative_perceptron(100, w);

function hypothesis_w_list = single_perceptron(num_dots, initial_weight, iterations)
    w = initial_weight;
    hypothesis_w_list = zeros(iterations, 3);
    x = -1 + (2).*rand(num_dots, 2);
    x = [ones(num_dots,1) x];
    y = double(x(1:num_dots,2) > x(1:num_dots,3));
    y(find(y==0)) = -1;
    for i=1:iterations
        h = sign(w' * x')';
        index = find(h~=y);
        if size(index) > 0
            index = index(1);
            w = w + y(index) * x(index, 1:3)';
        end
        hypothesis_w_list(i,1:3) = w;
    end
end

function percent_correct = percent_correct_perceptron(num_dots, weight, repeat)
%     num_dots = 10:10:2000;
%     w = [-.1678;13.982;-13.5078];
    w = weight;
    s = size(num_dots);
    mean_errors = zeros(s(2),1);
    for num=1:s(2)
        error_list = zeros(repeat,1);
        for i=1:repeat
            x = -1 + (2).*rand(num_dots(num), 2);
            x = [ones(num_dots(num),1) x];
            y = double(x(1:num_dots(num),2) > x(1:num_dots(num),3));
            y(find(y==0)) = -1;
            h = sign(w' * x')';
            index = find(h~=y);
            ss = size(index);
            error_list(i,1) = ss(1);
        end
        mean_errors(num,1) = mean(error_list) / num_dots(num);
    end
    percent_correct = 1 - mean_errors;
end

function hypothesis_w_list = alternative_perceptron(num_dots, initial_weight, eta, iterations)
    w = initial_weight
    x = -1 + (2).*rand(num_dots, 2);y = [y(find(y==1)); y(find(y==5))];                     % Collect y data points for 1 and 5 only.
y = [y(1:num); y(501:501+num-1)];
y(find(y==5)) = -1;                                     % Convert y = 5 to y = -1.

    x = [ones(num_dots,1) x];
    y = double(x(1:num_dots,2) > x(1:num_dots,3));
    y(find(y==0)) = -1;
    hypothesis_w_list = zeros(iterations, 3);
    for i=1:iterations
        r = randi([1 num_dots], 1, 1);
        pair = x(r,:);
        s = w'*pair';
%         y(r) * s;
%         y(r) - s
        if y(r) * s <= 1
            w = w + eta*(y(r) - s)*pair';
        end
        hypothesis_w_list(i,:) = w;
    end
end

function percent_correct = validate_alternative_perceptron(num_dots, weight)
    w = weight;
    x = -1 + (2).*rand(num_dots, 2);
    x = [ones(num_dots,1) x];
    y = double(x(1:num_dots,2) > x(1:num_dots,3));
    y(find(y==0)) = -1;
    h = sign(w' * x')';
    s = size(find(h~=y));
    ss = s(1);
    percent_correct = 1 - ss/num_dots;
    
    pos = [];
    neg = [];
    
    sz = 30;
    cp = 'red';
    cn = 'blue';
    
    for i=1:size(y,1)
        if y(i) == 1
            pos = [pos; x(i,2:3)];
        else
            neg = [neg; x(i,2:3)];
        end
    end
    
    p = size(pos);
    p = p(1);
    n = size(neg);
    n = n(1);
    
    x_range = linspace(-1,1);
    x22 = -(w(2)/w(3)) * x_range - w(1)/w(3);

    hold on
    
    plot([-1 1], [0 0], 'color', 'black')
    plot([0 0], [-1 1], 'color', 'black')
    scatter(pos(1:p,1), pos(1:p,2), sz, cp, 'filled')
    scatter(neg(1:n,1), neg(1:n,2), sz, cn, 'filled')

    plot(x_range, x_range, 'LineWidth', 3, 'color', 'magenta')
    plot(x_range, x_range, 'color', 'magenta')
    
    plot(x_range, x22, 'LineWidth', 3)
    
    xlim([-1 1])
    ylim([-1 1])
    set(gca, 'XTick', -1:.2:1)
    set(gca, 'YTick', -1:.2:1)
    grid on
    set(gca, 'GridLineStyle', '--')
    pbaspect([1 1 1])
end


