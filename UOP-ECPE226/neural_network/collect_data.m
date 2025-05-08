function [x_collect, y_collect] = collect_data(x_data, y_data, n, m)
    % this function is not used
    
    x_collect = zeros( (m-n)*10, 3);
    y_collect = zeros( (m-n)*10);
    
    for i=0:9
        x_collect( (i*(m-n))+1:(i*m)+m, 3 ) = x_data( (i*500)+1 : (i*500)+m, 3 );
        y_collect( (i*(m-n))+1:(i*m)+m, 3 ) = y_data( (i*500)+1 : (i*500)+m, 3 );
    end
end