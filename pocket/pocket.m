

function [ hypothesis_w_list, pla_hypothesis_w_list, Ein ] = pocket(x, y, initial_weight, iterations)
    N = length(x);                                            % Number of data points.

    w = initial_weight;                                     % Initial weight vector.
    hypothesis_w_list = zeros(iterations, 3);               % List of weights for each iteration.
    
    err = (1/N) * sum(sign(w'*x')'~= y);                    % Compute initial error.

    hypothesis_w_list(1,:) = w';                            % Save initial weight vector to hypothesis w list.
    pla_hypothesis_w_list(1,:) = w';
    for i=1:iterations-1                                    % Iterate over iterations.
        wrong_indices = find(sign(w'*x')'~= y);             % Find all of the indices where the sign of dot(w, x)
                                                            % is different from the corresponding y value.
        index = wrong_indices(randi(length(wrong_indices)));% Randomly pick an index for a misclassified point.

        new_w = w + y(index)*x(index,1:3)';                 % Compute new weight vector.
        pla_hypothesis_w_list(i+1,:) = new_w';
        new_err = (1/N) * sum(sign(new_w'*x')' ~= y);       % Compute new error using the new weight vector.

        if new_err < err                                    % Check if the new error is less than the best error.
            err = new_err;                                  % Set best error to be equal to the new error.
            w = new_w;                                      % Set best weight vector to be equal to the new
                                                            % weight vector.
        end
        hypothesis_w_list(i+1,:) = w';                      % Append the current weight vector to the list of
                                                            % hypothesis weight vectors.
    end
    Ein = (1/N) * sum(sign(w'*x')' ~= y);
end