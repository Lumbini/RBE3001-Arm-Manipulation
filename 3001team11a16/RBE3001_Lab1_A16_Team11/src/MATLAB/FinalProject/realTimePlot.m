function [] = realTimePlot(upAngle, lowAngle, state)

% Position of 5 points on the arm in 2 vectors, x and y
% x = [base-10, base, joint 1, joint 2, Tip]
% y = [base-10, base, joint 1, joint 2, Tip]
% z = 0 assuming all joints are in one page

%Convert angles from 10ths to ones
upAngle1D = upAngle/10;
lowAngle1D = lowAngle/10;

upLength = 150; %mm
lowLength = 152; %mm

% Equations were derived using the DH Parameers
lowBase = [-140, -140];
base = [0, -140];
joint1 = [0, 0];

joint2 = [lowLength*cosd(lowAngle1D) , lowLength*sind(lowAngle1D)];
endEffX = (lowLength*cosd(lowAngle1D)) + (upLength*cosd(upAngle1D + lowAngle1D));
endEffY = (lowLength*sind(lowAngle1D)) + (upLength*sind(upAngle1D + lowAngle1D));
endEff = [endEffX, endEffY];

x1 = [lowBase(1) base(1) joint1(1) joint2(1) endEff(1)];
y1 = [lowBase(2) base(2) joint1(2) joint2(2) endEff(2)];

plot(x1,y1,'-gs',...
    'LineWidth',2,...
    'MarkerSize',5,...
    'MarkerEdgeColor','r',...
    'MarkerFaceColor',[0.5,0.5,0.5])
axis([-400,400,-140,400])

txtX = 0;
txtY = 350;
stateStatus = state;

figTitle = text(txtX, txtY, stateStatus);
figTitle.FontSize = 20;
figTitle.Color = 'blue';
figTitle.HorizontalAlignment = 'center';
figTitle.FontName = 'Calibri';
figTitle.FontWeight = 'normal';
figTitle.FontSmoothing = 'on';
end


