

% ***** User Changable Variables ***** %
pop = 40;               %population size
gen = 200;              %number of generations
pcntsel = 1;          %fraction of candidates selected for next generation
% breed_method = 'uniform';           % select crossover method
breed_method = '1-point';
cross_over_index = 4;               % for 1-point crossover, select location to cross the parents

precision = 8;          %precision of real number represenation (ex. 8 -> 8-bit represenation)
range = [-5 5; -5 5];   %bounds for input variables

% ***** Calculations ***** %
mu = round(pcntsel*pop);    %number of parents selected
lambda = pop - mu;          %number of new candidates in each generation (children)

trials = 200;
best_ind = zeros(gen, trials);

for t = 1:trials
    candidate.binx = rand(pop,precision)>0.5;   %generate binary representation
    candidate.biny = rand(pop,precision)>0.5;
    
    for i = 1:gen
        % ********* Convert Representation ****** %
        candidate.x = (range(1,1)-range(1,2))*(binary_to_decimal(candidate.binx)/(2^precision-1))+range(1,2);
        candidate.y = (range(2,1)-range(2,2))*(binary_to_decimal(candidate.biny)/(2^precision-1))+range(2,2);

        % *************************************** %

        % ********* Get Fitness ***************** %
        candidate.fit = objf(candidate.x,candidate.y);
        % *************************************** %

        best_ind(i,t) = max(candidate.fit);

        % ********* Selection ******************* %
        % Linear (Roulette Wheel) Selection
        fitsum = sum(candidate.fit);
        candidate.p = candidate.fit./fitsum;
        candidate.ps = cumsum(candidate.p);
        r = rand(mu,1);
        [~,chosen] = histc(r, candidate.ps);
        chosen = chosen + 1;                            % take care of the 0 ...
        pairs = [chosen(1:mu/2,1) chosen(mu/2+1:mu,1)];

        for i=1:mu
            candidate.temp_binx(i,:) = candidate.binx(chosen(i),:);
            candidate.temp_biny(i,:) = candidate.biny(chosen(i),:);
        end
        
        mask = rand(1, precision) > 0.5;

        % *************************************** %

        % ********* Create Offspring ************ %
        for i=1:length(pairs)
            parent1_binx = candidate.binx(pairs(i,1),:);
            parent2_binx = candidate.binx(pairs(i,2),:);

            parent1_biny = candidate.biny(pairs(i,1),:);
            parent2_biny = candidate.biny(pairs(i,2),:);

            if breed_method == 'uniform'
                child1_binx = parent1_binx;
                child1_binx(mask > 0.5) = parent2_binx(mask > 0.5);
                child2_binx = parent2_binx;
                child2_binx(mask > 0.5) = parent1_binx(mask > 0.5);

                child1_biny = parent1_biny;
                child1_biny(mask > 0.5) = parent2_biny(mask > 0.5);
                child2_biny = parent2_biny;
                child2_biny(mask > 0.5) = parent1_biny(mask > 0.5);

                candidate.temp_binx(mu+i,:) = child1_binx;
                candidate.temp_binx(mu+i+length(pairs),:) = child2_binx;
                
                candidate.temp_biny(mu+i,:) = child1_biny;
                candidate.temp_biny(mu+i+length(pairs),:) = child2_biny;

            elseif breed_method == '1-point'
                child1_binx = [parent1_binx(1:cross_over_index) parent2_binx(cross_over_index+1:end)];
                child2_binx = [parent2_binx(1:cross_over_index) parent1_binx(cross_over_index+1:end)];
                child1_biny = [parent1_biny(1:cross_over_index) parent2_biny(cross_over_index+1:end)];
                child2_biny = [parent2_biny(1:cross_over_index) parent1_biny(cross_over_index+1:end)];
                
                candidate.temp_binx(mu+i,:) = child1_binx;
                candidate.temp_binx(mu+i+length(pairs),:) = child2_binx;
                
                candidate.temp_biny(mu+i,:) = child1_biny;
                candidate.temp_biny(mu+i+length(pairs),:) = child2_biny;
            end
        end
        % *************************************** %

        % ********* Next Generation ************* %
        candidate.binx = candidate.temp_binx;
        candidate.biny = candidate.temp_biny;


        % *************************************** %
    end
end