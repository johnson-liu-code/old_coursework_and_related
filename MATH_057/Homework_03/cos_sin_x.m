

function tt = cos_sin_x(t, N)
    n = linspace(0, N, N+1);
    
    const_vector = zeros(1, N+1);
    terms = zeros(length(const_vector), length(t));
    
    for i = n
        const_vector(1, i+1) = 1 / factorial(2*i+1);
        terms(i+1,:) = t .^(2*i + 1);
    end

    tt = ( ( (-1).^n ) .* const_vector ) * terms;
end




