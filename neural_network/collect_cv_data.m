function [x_cv, y_cv] = collect_cv_data(x_data, y_data, n)
    % this function is not used

    x_cv = zeros(m*10, 3);
    y_cv = zeros(m*10);
    
    for i=0:9
        x_cv( (i*m)+1 : (i*m)+m, 3 ) = x_data( (i*500)+1 : (i*500)+m, 3 );
        y_cv( (i*m)+1 : (i*m)+m, 3 ) = y_data( (i*500)+1 : (i*500)+m, 3 );
    end
end