function [child1_binx, child1_biny, child2_binx, child2_biny] = uniform_crossover(parent1_binx, parent1_biny, parent2_binx, parent2_biny, mask)
    % uniform crossover

    % create child 1 binx
    % set child 1 binx to be equal to parent 1 binx
    child1_binx = parent1_binx;
    % replace specific sections of child 1 binx with sections from parent 2 binx according to the mask
    child1_binx(mask > 0.5) = parent2_binx(mask > 0.5);
    
    % create child 2 binx
    % set child 2 binx to be equal to parent 2 binx
    child2_binx = parent2_binx;
    % replace specific sections of child 2 binx with sections from parent 1 binx according to the mask
    child2_binx(mask > 0.5) = parent1_binx(mask > 0.5);

    % creaste child 1 biny
    % set child 1 biny to be equal to parent 1 biny
    child1_biny = parent1_biny;
    % replace specific sections of child 1 biny with sections from parent 2 biny according to the mask
    child1_biny(mask > 0.5) = parent2_biny(mask > 0.5);
    
    % create child 2 biny
    % set child 2 biny to be equal to parent 2 biny
    child2_biny = parent2_biny;
    % replace specific sections of child 2 biny with sections from parent 1 biny according to the mask
    child2_biny(mask > 0.5) = parent1_biny(mask > 0.5);
end