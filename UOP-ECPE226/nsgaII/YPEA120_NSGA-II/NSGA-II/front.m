function [M] = front(pop)
    pSize = length(pop);
    % if the population size is not 1
    if pSize ~= 1
        % separate the top and bottom individuals
        T = front( pop(1:floor(pSize/2)) );
        B = front( pop(floor(pSize/2)+1:pSize) );
        M = T;
        % iterate over the bottom individuals
        for i = 1:length(B)
            flag = 0;
            % check if any of the top individuals dominate the bottom individual
            for j = 1:length(T)
                if Dominates(T(j), B(i))
                    flag = 1;
                    break;
                end
            end
            % if no top individual dominates the bottom individual, append the
            % bottom individual to the set that gets passed back through the recursion
            if flag == 0
                M = [M;B(i)];
            end
        end
    else
        M = pop;
    end
end