
% ************************************ %
% ***** User Changable Variables ***** %
pop = 40;                           % population size
gen = 200;                          % number of generations
pcntsel = .5;                       % fraction of candidates selected for next generation
breed_method = 'uniform';           % select crossover method
% breed_method = '1-point';
cross_over_index = 4;               % for 1-point crossover, select location to cross the parents

precision = 8;                      % precision of real number represenation (ex. 8 -> 8-bit represenation)
range = [-5 5; -5 5];               % bounds for input variables

trials = 200;                       % number of trials
% ************************************ %

% **************************************** %
% ***** Method for selecting parents ***** %
% selection_method = 'roulette';    % roulette
% selection_method = 'elitist';       % elitist
% selection_method = 'tournament';  % tournament
selection_method = 'linear_rank'; % linear rank

% decide whether or not to carry parents over to the next generation
parents_carry_over = true;
% parents_carry_over = false;

% **************************************** %

% ************************ %
% ***** Calculations ***** %
mu = round(pcntsel*pop);            % number of parents selected
lambda = pop - mu;                  % number of new candidates in each generation (children)

eta_p = 1.5;                        % eta^+ value for linear rank selection
eta_m = 2 - eta_p;                  % eta^- value for linear rank selection

best_ind = zeros(gen, trials);      % matrix to save the best fitness from each generation for each trial

% generate cumulative summation for linear rank election
if strcmp(selection_method, 'linear_rank')
    ints = 1:pop;
    candidate.p = (eta_p - (eta_p-eta_m)*(ints-1)/(pop-1)) ./ pop;  % linear rank formula
    candidate.ps = cumsum(candidate.p);                             % the formula makes sure that all candidate.p add up to 1
end

%{
% iterate over trials
for t = 1:trials
    candidate.binx = rand(pop,precision)>0.5;   % generate binary representation for x
    candidate.biny = rand(pop,precision)>0.5;   % generate binary representation for y
    
    % iterate over generations
    for g = 1:gen
        % *************************************** %
        % ********* Convert Representation ****** %
        candidate.x = (range(1,1)-range(1,2))*(binary_to_decimal(candidate.binx)/(2^precision-1))+range(1,2);   % convert binary x to decimal x
        candidate.y = (range(2,1)-range(2,2))*(binary_to_decimal(candidate.biny)/(2^precision-1))+range(2,2);   % convert binary y to decimal y

        % *************************************** %

        % *************************************** %
        % ********* Get Fitness ***************** %
        candidate.fit = objf(candidate.x,candidate.y);
        % *************************************** %

        best_ind(g,t) = max(candidate.fit);                 % add best fitness to matrix

        % *************************************** %
        % ********* Selection ******************* %
        if strcmp(selection_method, 'roulette')
            % roulette selection
            [chosen] = roulette_selection(candidate, mu);
            
        elseif strcmp(selection_method, 'elitist')
            % elitist Selection
            [~, chosen] = maxk(candidate.fit, mu);
            
        elseif strcmp(selection_method, 'tournament')
            % tournament selection
            [chosen] = tournament_selection(candidate, pop, mu);
            
        elseif strcmp(selection_method, 'linear_rank')
            % linear rank selection
            [candidate, chosen] = linear_rank_selection(candidate, mu);
        end
        
        % determine pairs of parents
        pairs = [chosen(1:mu/2,1) chosen(mu/2+1:mu,1)];

        % create mask for cross breeding
        if strcmp(breed_method, 'uniform')
            mask = rand(1, precision) > 0.5;
        end
        
        % *************************************** %
        % ********* Create Offspring ************ %
        for p=1:length(pairs)
            % get binx and biny for parents 1 and 2
            [parent1_binx, parent1_biny, parent2_binx, parent2_biny] = get_parent_bin(candidate, pairs, p);
            
            % uniform crossover
            if strcmp(breed_method, 'uniform')
                [child1_binx, child1_biny, child2_binx, child2_biny] = uniform_crossover(parent1_binx, parent1_biny, parent2_binx, parent2_biny, mask);

            % single-point crossover
            elseif strcmp(breed_method, '1-point')
                [child1_binx, child1_biny, child2_binx, child2_biny] = point_crossover(parent1_binx, parent1_biny, parent2_binx, parent2_biny, cross_over_index);
            end
            
            % append child 1 binx to temporary vector
            candidate.temp_binx(mu+p,:) = child1_binx;
            % append child 2 binx to temporary vector
            candidate.temp_binx(mu+p+length(pairs),:) = child2_binx;

            % append child 1 biny to temporary vector
            candidate.temp_biny(mu+p,:) = child1_biny;
            % append child 2 biny to temporary vector
            candidate.temp_biny(mu+p+length(pairs),:) = child2_biny;
        end
        % *************************************** %

        if parents_carry_over == true
            % append parents to temporary vector for binx and biny
            for i=1:mu
                candidate.temp_binx(i,:) = candidate.binx(chosen(i),:);
                candidate.temp_biny(i,:) = candidate.biny(chosen(i),:);
            end
        elseif parents_carry_over == false
            % append randomized candidates to temporary vector for binx and biny
            for i=1:lambda
                candidate.temp_binx(i,:) = rand(1,precision)>0.5;
                candidate.temp_biny(i,:) = rand(1,precision)>0.5;
            end
        end
        
        % *************************************** %
        % ********* Next Generation ************* %

        % save temporary vector to candidate vector for binx and biny
        candidate.binx = candidate.temp_binx;
        candidate.biny = candidate.temp_biny;

        % *************************************** %
    end
end
%}