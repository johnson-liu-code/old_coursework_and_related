%% Evolutionary Algorithm Example
% Dr. David Mueller
% 
% Computational Intelligence
%% Problem Statement:
% Use a genetic algorithm to find the global optimum of the following objective 
% function:
% 
% $$f(x,y)=\exp\left( \frac{-\left[ (x-3)^2+(y-3)^2\right]}{5} \right) +\exp\left( 
% \frac{-\left[ x^2+(y+3)^2\right]}{5} \right) + 0.2\left[ \cos\left(\frac{x\pi}{2}\right) 
% + \cos\left(\frac{y\pi}{2}\right)\right] +5$$
% 
% Mathematically we know this function has a maximum height of 1.6903 in 
% the range of -5 to 5 for x and y.

[x,y]=meshgrid(-5:0.05:5);
mesh(x,y,objf(x,y));

%xlim([-5.00 5.00])
%ylim([-5.00 5.00])
%zlim([0.00 2.00])
%view([-112.50 -13.80])
%% Methods:
% * Representation: Binary
% * Selection: Elitist, Rank Selection
% * Mating/Variation: Single Point Binary Crossover, Uniform Crossover
%% Initialize Parameters
% For a genetic algorithm, the important parameters are population size, number 
% of generations to execute, fraction of population seleected for mating, the 
% data representation, and the range of data.

clearvars
% ***** User Changable Variables ***** %
pop = 40;               %population size
gen = 200;              %number of generations
pcntsel = 0.5;          %fraction of candidated selected for next generation
breed_method = 'uniform';       % select crossover method
% breed_method = '1-point';
cross_over_index = 4;           % for 1-point crossover, select location to cross the parents

precision = 8;          %precision of real number represenation (ex. 8 -> 8-bit represenation)
range = [-5 5; -5 5];   %bounds for input variables

% ***** Calculations ***** %
mu = round(pcntsel*pop);    %number of parents selected
lambda = pop - mu;          %number of new candidates in each generation (children)

trials = 200;                       % numnber of trials
best_ind = zeros(gen, trials);      % matrix to collect the best fitness from each generation for every trial
%% 
%% Genetic Algorithm
%%
for t = 1:trials                % iterate over the trials
    
%%           Generate Initial Population
%             Generally, the initial population is generated randomly within 
% specified ranges. 

    candidate.binx = rand(pop,precision)>0.5;   %generate binary representation
    candidate.biny = rand(pop,precision)>0.5;

    for i = 1:gen
        
        % ********* Convert Representation ****** %
        candidate.x = (range(1,1)-range(1,2))*(binary_to_decimal(candidate.binx)/(2^precision-1))+range(1,2);       % convert binary to decimal for x and y
        candidate.y = (range(2,1)-range(2,2))*(binary_to_decimal(candidate.biny)/(2^precision-1))+range(2,2);
        % *************************************** %
        
        % ********* Get Fitness ***************** %
        candidate.fit = objf(candidate.x,candidate.y)       % compute fitness for each individual
        % *************************************** %

        best_ind(i,t) = max(candidate.fit);                 % collect the fitness of the fittest individual

        % ********* Selection ******************* %
        % Linear (Roulette Wheel) Selection
        fitsum = sum(candidate.fit);                        % sum up the fitness of every individual
        candidate.p = candidate.fit./fitsum;                % compute the ratio of the fitness of each individual to the total sum of fitnesses
        candidate.ps = cumsum(candidate.p);                 % generate cummulative sum
        
        % *************************************** %
        
        r = rand(mu,1);                                     % generate random numbers
        [~,chosen] = histc(r, candidate.ps);                % taken from internet. selects parents
        chosen = chosen + 1;                                % take care of the 0 ...
        pairs = [chosen(1:mu/2,1) chosen(mu/2+1:mu,1)];     % pair up the parents

        for i=1:mu                                                      % iterate over the parents
            candidate.temp_binx(i,:) = candidate.binx(chosen(i),:);     % carry the parents over to the next generation
            candidate.temp_biny(i,:) = candidate.biny(chosen(i),:);
        end
        
        mask = rand(1, precision) > 0.5;                    % generate mask

        % *************************************** %

        % ********* Create Offspring ************ %
        for i=1:length(pairs)                                                   % iterate over the pairs
            parent1_binx = candidate.binx(pairs(i,1),:);                        % get binx of parent 1
            parent2_binx = candidate.binx(pairs(i,2),:);                        % get binx of parent 2

            parent1_biny = candidate.biny(pairs(i,1),:);                        % get biny of parent 1
            parent2_biny = candidate.biny(pairs(i,2),:);                        % get biny of parent 2

            if breed_method == 'uniform'
                child1_binx = parent1_binx;                                     % generate binx for child 1
                child1_binx(mask > 0.5) = parent2_binx(mask > 0.5);
                child2_binx = parent2_binx;                                     % generate binx for child 2
                child2_binx(mask > 0.5) = parent1_binx(mask > 0.5);

                child1_biny = parent1_biny;                                     % generate biny for child 1
                child1_biny(mask > 0.5) = parent2_biny(mask > 0.5);
                child2_biny = parent2_biny;                                     % generate biny for child 2
                child2_biny(mask > 0.5) = parent1_biny(mask > 0.5);

                candidate.temp_binx(mu+i,:) = child1_binx;                      % carry child 1 binx over to the next generation
                candidate.temp_binx(mu+i+length(pairs),:) = child2_binx;        % carry child 2 binx over to the next generation
                
                candidate.temp_biny(mu+i,:) = child1_biny;                      % carry child 1 binx over to the next generation
                candidate.temp_biny(mu+i+length(pairs),:) = child2_biny;        % carry child 1 binx over to the next generation

            elseif breed_method == '1-point'
                child1_binx = [parent1_binx(1:cross_over_index) parent2_binx(cross_over_index+1:end)];  % generate binx for child 1
                child2_binx = [parent2_binx(1:cross_over_index) parent1_binx(cross_over_index+1:end)];  % generate binx for child 2
                child1_biny = [parent1_biny(1:cross_over_index) parent2_biny(cross_over_index+1:end)];  % generate biny for child 1
                child2_biny = [parent2_biny(1:cross_over_index) parent1_biny(cross_over_index+1:end)];  % generate biny for child 2
                
                candidate.temp_binx(mu+i,:) = child1_binx;                      % carry child 1 binx over to the next generation
                candidate.temp_binx(mu+i+length(pairs),:) = child2_binx;        % carry child 2 binx over to the next generation
                
                candidate.temp_biny(mu+i,:) = child1_biny;                      % carry child 1 biny over to the next generation
                candidate.temp_biny(mu+i+length(pairs),:) = child2_biny;        % carry child 2 biny over to the next generation
            end
        end
        % *************************************** %

        % ********* Next Generation ************* %
        candidate.binx = candidate.temp_binx;           % make the next generation
        candidate.biny = candidate.temp_biny;


        % *************************************** %
    end
end
%% Results and Conclusions