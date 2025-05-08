


empty_ind.Position=[];
empty_ind.Cost=[];
empty_ind.Index = 0;

ii = 6;

% nPop = 10;
nPop = sum(1:ii);

pop=repmat(empty_ind,nPop,1);
for i=1:nPop
    pop(i).Index = i;
end

k = 1;

% ii = 10;
% jj = 10;

for i=1:ii
    for j=1:ii
        if (i+j) <= ii+1
            pop(k).Position = [i;j];
            pop(k).Cost = [i;j];
            k = k+1;
        end
    end
end

% pop.Cost
% front_pop = kung(pop);
% % new_pop = pop;
% not_indices = [];
% for i=1:length(front_pop)
%     not_indices = [not_indices front_pop(i).Index];
% end
% x = 1:length(pop)
% cut_pop = pop(setdiff(x, not_indices))
% front_pop = kung(cut_pop)

not_indices = [];
k = 0;
pop = kung(pop)
% for i=1:length(pop)
%     pop(i).Cost
% end
% temp_pop = pop;
% while ~isempty(temp_pop)
%     front_pop = kung(temp_pop);
%     [temp_pop, not_indices] = kung(temp_pop, not_indices);
%     for i=1:length(front_pop)
%         not_indices = [not_indices front_pop(i).Index];
%     end

%     x = 1:length(pop);
%     temp_pop = pop(setdiff(x, not_indices));
%     figure(1)
%     plot_pos = [temp_pop.Position];
%     hold on
%     xlim([0 ii+1])
%     ylim([0 ii+1])
%     grid on
%     set(gca, 'GridLineStyle', '--')
%     scatter(pos(1,:), pos(2,:), 'rx')
%     pause(1)
% end





% pos = [pop.Position];
% hold on
% xlim([0 ii+1])
% ylim([0 ii+1])
% grid on
% set(gca, 'GridLineStyle', '--')
% scatter(pos(1,:), pos(2,:), 'rx')