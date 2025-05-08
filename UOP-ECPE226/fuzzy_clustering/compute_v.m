function [V] = compute_v(V, U, X, m)
    s = size(V);
    C = s(1);
    D = s(2);
    N = length(X);
    
    V = zeros(C,D);
    
    % loop over the cluster centers
    for i=1:C
        denom_sum = 0;
        numer_sum = zeros(1,D);
        
        % loop over the data points
        for k=1:N
            % compute denominator and numerator
            n = U(i,k)^m;
            denom_sum = denom_sum + n;
            
            g = U(i,k)^m * X(k,:);
            numer_sum = numer_sum + g;
        end
        
%         numer_sum
%         denom_sum
        % compute v
        V(i,:) = numer_sum/denom_sum;
        
    end
end