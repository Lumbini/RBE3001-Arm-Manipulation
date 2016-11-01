
upLength = 140.467; %mm
lowLength = 152.401; %mm

theta1 = linspace(0,1800,1801);
for theta2 = 1:1800
[x,y] = calcXY(theta2, theta1);
hold on;
scatter(x,y);
axis([-300,300,-300,300]);
disp(theta2);
end

