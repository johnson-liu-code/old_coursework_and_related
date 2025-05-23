%
% Copyright (c) 2015, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YPEA120
% Project Title: Non-dominated Sorting Genetic Algorithm II (NSGA-II)
% Publisher: Yarpiz (www.yarpiz.com)
% 
% Developer: S. Mostapha Kalami Heris (Member of Yarpiz Team)
% 
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

% clc;
% clear;
% close all;
%% Problem Definition

CostFunction=@(x) MOP4(x);      % Cost Function

nVar=3;             % Number of Decision Variables

VarSize=[1 nVar];   % Size of Decision Variables Matrix

VarMin=-5;          % Lower Bound of Variables
VarMax= 5;          % Upper Bound of Variables

% Number of Objective Functions
x = (VarMax - VarMin).*rand(VarSize(2),1) - VarMax;
% nObj=numel(CostFunction(unifrnd(VarMin,VarMax,VarSize)));
nObj=numel(CostFunction(x));

%% NSGA-II Parameters

MaxIt=100;      % Maximum Number of Iterations

nPop=40;        % Population Size

pCrossover=0.7;                         % Crossover Percentage
nCrossover=2*round(pCrossover*nPop/2);  % Number of Parnets (Offsprings)

pMutation=0.4;                          % Mutation Percentage
nMutation=round(pMutation*nPop);        % Number of Mutants

mu=0.02;                    % Mutation Rate

sigma=0.1*(VarMax-VarMin);  % Mutation Step Size


%% Initialization

empty_individual.Position=[];
empty_individual.Cost=[];
empty_individual.Index = [];
empty_individual.Rank=[];
empty_individual.DominationSet=[];
empty_individual.DominatedCount=[];
empty_individual.CrowdingDistance=[];

pop=repmat(empty_individual,nPop,1);

for i=1:nPop
%     i
    x = (VarMax - VarMin).*rand(VarSize(2),1) - VarMax;
%     pop(i).Position=unifrnd(VarMin,VarMax,VarSize);
    pop(i).Position=x;
    pop(i).Cost=CostFunction(pop(i).Position);
    pop(i).Index = i;
end

% Non-Dominated Sorting
% [pop, F]=NonDominatedSorting(pop);

% Kung Sorting
pop = kung(pop);

% % Calculate Crowding Distance
% pop=CalcCrowdingDistance(pop,F);

% Sort Population
% [pop, F]=SortPopulation(pop);


%% NSGA-II Main Loop


for it=1:MaxIt
    it;
    % Crossover
    popc=repmat(empty_individual,nCrossover/2,2);
    for k=1:nCrossover/2
        
        i1=randi([1 nPop]);
        p1=pop(i1);
        
        i2=randi([1 nPop]);
        p2=pop(i2);
        
        [popc(k,1).Position, popc(k,2).Position]=Crossover(p1.Position,p2.Position);
        
        popc(k,1).Cost=CostFunction(popc(k,1).Position);
        popc(k,2).Cost=CostFunction(popc(k,2).Position);
        
    end
    popc=popc(:);
    
    % Mutation
    popm=repmat(empty_individual,nMutation,1);
    for k=1:nMutation
        
        i=randi([1 nPop]);
        p=pop(i);
        
        popm(k).Position=Mutate(p.Position,mu,sigma);
        
        popm(k).Cost=CostFunction(popm(k).Position);
        
    end
    
    % Merge
    pop=[pop
         popc
         popm]; %#ok
     
     % indexing for Kung
     for j=1:length(pop)
         pop(j).Index = j;
     end
     
    % Non-Dominated Sorting
%     [pop, F]=NonDominatedSorting(pop);

    % Kung Sorting
    it;
    pop = kung(pop);
    it;
    % Calculate Crowding Distance
%     pop=CalcCrowdingDistance(pop,F);

    % Sort Population
%     pop=SortPopulation(pop);
    
    % Truncate
    pop=pop(1:nPop);
    
    % Non-Dominated Sorting
%     [pop, F]=NonDominatedSorting(pop);

    % Calculate Crowding Distance
%     pop=CalcCrowdingDistance(pop,F);

    % Sort Population
%     [pop, F]=SortPopulation(pop);
    
    % Store F1
%     F1=pop(F{1});

    % Show Iteration Information
%     disp(['Iteration ' num2str(it) ': Number of F1 Members = ' num2str(numel(F1))]);
    disp(['Iteration ' num2str(it)]);
    % Plot F1 Costs
%     hold on
%     xlim([-22 -5])
%     ylim([-13 10])
%     figure(1);
%     PlotCosts(F1);
%     PlotCosts(plot_pop);

    PlotCosts(pop);
%     pause(0.01);
    
end
% hold on
% xlim([-22 -5])
% ylim([-13 10])
% PlotCosts(pop)
