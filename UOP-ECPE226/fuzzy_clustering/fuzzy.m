data = load('clusterdata.mat');
data = data.clusterdemo;

% specify the number of clusters
n = 3;

C = n;
% specify parameter values
m = 2;
epsilon = 1e-10;

% initialize V to random numbers between 0 and 1
V = rand(C,3);

% x = [4 1 3];
% v = [1 1 1];
% 
% dist = euc_dist(x, v);

% compute the initial U
U = compute_u(data, V, m);
% save V to be the previous V
V_prev = V;
% compute the new V
V = compute_v(V, U, data, m);

total_dist = 0;
for y=1:length(V)
    dist = euc_dist( V_prev(y,:), V(y,:) );
    total_dist = total_dist + dist;
end

% loop while the distance between the current V and the previous V is
%   greater than the convergence threshold
while total_dist > epsilon
    % compute U
    U = compute_u(data, V, m);
    % save V to be the previous V
    V_prev = V;
    % compute the new V
    V = compute_v(V, U, data, m);
    
    total_dist = 0;
    for y=1:length(V)
        dist = euc_dist( V_prev(y,:), V(y,:) );
        total_dist = total_dist + dist;
    end
end

% sort the data points into the three clusters
[M, I] = max(U);

first_cluster = [];
second_cluster = [];
third_cluster = [];

for i=1:length(I)
    if I(i) == 1
        first_cluster = [first_cluster;data(i,:)];
    elseif I(i) == 2
        second_cluster = [second_cluster;data(i,:)];
    elseif I(i) == 3
        third_cluster = [third_cluster;data(i,:)];
    end
end



scatter3(first_cluster(:,1), first_cluster(:,2), first_cluster(:,3))
hold on
scatter3(second_cluster(:,1), second_cluster(:,2), second_cluster(:,3))
scatter3(third_cluster(:,1), third_cluster(:,2), third_cluster(:,3))




