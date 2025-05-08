function [chosen] = roulette_selection(candidate, mu)
    % linear (roulette wheel) selection
    fitsum = sum(candidate.fit);                    % sum up all of the fitnesses from every candidate
    candidate.p = candidate.fit./fitsum;            % compute the 'probability' of picking each candidate
    candidate.ps = cumsum(candidate.p);             % compute the cumulative summation
    r = rand(mu,1);                                 % generate random numbers
    [~,chosen] = histc(r, candidate.ps);            % select from cumulative summation
    chosen = chosen + 1;                            % take care of the 0 ...
end