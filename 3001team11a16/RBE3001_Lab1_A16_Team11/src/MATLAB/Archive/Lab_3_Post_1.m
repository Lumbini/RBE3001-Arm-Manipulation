
cpt_mv3 = mv3(2) - mv3(1);
cpt_v3 = v3(2) - v3(1);
cpt_v7 = v7(2) - v7(1);


for i = 3:1000
    cpt_mv3(end+1) = mv3(i) - mv3(i - 1);
    cpt_v3(end+1) = v3(i) - v3(i - 1); 
    cpt_v7(end+1) = v7(i) - v7(i - 1);
end

figure;
histogram(cpt_mv3);

figure;
histogram(cpt_v3);

figure;
histogram(cpt_v7);