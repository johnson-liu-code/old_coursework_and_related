function [pop] = kung(pop)
    % sort the individuals based on the first objective function
    x = [pop.Cost];
    c = x(1,:);
    [~,r] = sort(c, 'ascend');
    
    % create a temporary set of individuals
    temp_pop = pop(r);
    
    x = 1:length(pop);
    not_indices = [];

    % while the temporary set of individuals is not empty, do
    while ~isempty(temp_pop)
        % get the front
        front_pop = front(temp_pop);
        % iterate over the front and append the individuals' index to a set of indices
        for i=1:length(front_pop)
            not_indices = [not_indices front_pop(i).Index];
        end
            
        % the new temporary population has the front taken out
        temp_pop = pop(setdiff(x, not_indices));
    end
    
    % sort the new population according to the front indices
    pop = pop(not_indices);
end