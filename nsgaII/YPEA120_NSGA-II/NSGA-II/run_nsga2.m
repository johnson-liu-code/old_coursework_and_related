

tim = [];

for i=1:10
    i
    tic;
    nsga2;
    tim = [tim toc];
end