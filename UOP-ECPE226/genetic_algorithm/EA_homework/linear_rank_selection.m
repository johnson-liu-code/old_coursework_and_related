function [candidate, chosen] = linear_rank_selection(candidate, mu)
    % linear rank selection
    r = rand(mu,1);                                     % generate random numbers
    [~,chosen] = histc(r, candidate.ps);                % choose from cumulative summation
    
%     chosen = zeros(mu,1);
%     for i=1:mu
%         prev = 0;
% %         r = rand(1,1)
%         for j=1:length(candidate.ps)
% %             candidate.ps(1,j)
%             if r > flip_candidate.ps(1,j)
% %                 r
% %                 candidate.ps(1,j)
%                 chosen(i,1) = prev;
%                 break
%             end
%             prev = prev+1;    
%         end
%     end
%     
    chosen = chosen + 1;
    [~,idx] = sort(candidate.fit, 'descend');           % sort the candidates from highest fitness to lowest fitness
    candidate.fit = candidate.fit(idx);
    candidate.binx = candidate.binx(idx,:);
    candidate.biny = candidate.biny(idx,:);
end