function [parent1_binx, parent1_biny, parent2_binx, parent2_biny] = get_parent_bin(candidate, pairs, p)
    % retrieve binx and biny for parents 1 and 2
    parent1_binx = candidate.binx(pairs(p,1),:);
    parent2_binx = candidate.binx(pairs(p,2),:);

    parent1_biny = candidate.biny(pairs(p,1),:);
    parent2_biny = candidate.biny(pairs(p,2),:);
end