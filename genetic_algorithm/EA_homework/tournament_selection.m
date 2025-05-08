function [chosen] = tournament_selection(candidate, pop, mu)
    % tournament selection
    chosen = zeros(mu,1);
    for m=1:mu
        ind1 = randi(pop,1);                            % randomly select first individual
        ind2 = randi(pop,1);                            % randomly select second individual
        if candidate.fit(ind1) > candidate.fit(ind2)    % compare the fitnesses of the two individuals
            chosen(m,1) = ind1;                         % select individual with higher fitness
        else
            chosen(m,1) = ind2;
        end
    end
end