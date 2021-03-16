
function result = double_factorial(n)
    if (n == 1 || n==0)
        result = 1;
    else
        if (mod(n,2) == 0)
            result = prod(2:2:n);
        else
            result = prod(1:2:n);
        end
    end
end