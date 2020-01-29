function [child1_binx, child1_biny, child2_binx, child2_biny] = point_crossover(parent1_binx, parent1_biny, parent2_binx, parent2_biny, cross_over_index)
    % single-point crossover
    child1_binx = [parent1_binx(1:cross_over_index) parent2_binx(cross_over_index+1:end)];
    child2_binx = [parent2_binx(1:cross_over_index) parent1_binx(cross_over_index+1:end)];
    child1_biny = [parent1_biny(1:cross_over_index) parent2_biny(cross_over_index+1:end)];
    child2_biny = [parent2_biny(1:cross_over_index) parent1_biny(cross_over_index+1:end)];
end