function [decimal] = binary_to_decimal(binary)
    % function to turn binary representation to decimal representation
    decimal = 128*binary(:,1) + 64*binary(:,2) + 32*binary(:,3) + 16*binary(:,4) + 8*binary(:,5) + 4*binary(:,6) + 2*binary(:,7) + 1*binary(:,8);
end