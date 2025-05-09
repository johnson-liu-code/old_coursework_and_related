

function t = exponential_taylor(n, N)
    x = linspace(0, 2, N);

    double_fact_vector = zeros(1, n+1);
    terms = zeros(length(double_fact_vector), length(x));

    n_vector = linspace(0, n, n+1);

    for i = n_vector
        double_fact_vector(1, i+1) = double_factorial(2*i);
        terms(i+1,:) = x .^(2*i);
    end

    t = ( ( (-1).^n_vector ) ./ double_fact_vector ) * terms;