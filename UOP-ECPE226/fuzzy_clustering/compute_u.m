function [U] = compute_u(X, V, m)

    C = length(V);
    N = length(X);
    U = zeros(C, N);

    % loop over the cluster centers
    for i=1:C
        % loop over the data points
        for k=1:N
            
            % check if the data point lies on top of any of the cluster centers
            I = ismember(V, X(k,:), 'rows');
            S = sum(I);
            
            % if it does, compute u as 1/n
            if S > 0
                U(i,k) = 1/S;
            % otherwise, compute u using the formula
            else
                % compute the distance between the data point the cluster center
                dist1 = euc_dist(X(k,:), V(i,:));
                n_sum = 0;

                % compute the distances between the data point and each of the cluster centers
                for j=1:C
    %                 dist = euc_dist(X(k,:), V(j,:));
    %                 dist2 = dist2 + dist;
                    dist2 = euc_dist(X(k,:), V(j,:));
                    n = (dist1/dist2)^(1/(m-1));
                    n_sum = n_sum + n;
                end
    %             U(i,k) = (dist1/dist2)^(1/(m-1));

                U(i,k) = 1/n_sum;
            end
        end
    end
end