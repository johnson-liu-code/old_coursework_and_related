function [x_train, y_train] = collect_train_data(x_data, y_data, n, m)
    % this function is not used

    x_train = zeros((m-n)*10, 3);
    y_train = zeros((m-n)*10 );
    for i=0:9
        x_train(i*(m-n)+1:, 3) = x_data( (n+i*500 :  ), 3 )
    end
end