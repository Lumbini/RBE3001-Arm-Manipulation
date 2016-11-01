clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

X = [];
Y = [];
%fprintf(sAVR, 'A');

% fprintf(sAVR, '%d ', 900);
%pause(3);
% fprintf(sAVR, '%d ', 0);

[up,low] = calcAngle(-100,250);
SendAngles(up, low, sAVR);
pause(2);

for q = 1:14
    [up,low] = calcAngle(-100,250 - 5 * q);
    SendAngles(up, low, sAVR);
    [x,y] = Postlab_Plot(2, sAVR);
    
    X = horzcat(X,x);
    Y = horzcat(Y,y);
end

[up,low] = calcAngle(-100,175);
SendAngles(up, low, sAVR);
pause(2);

for q = 1:24
    [up,low] = calcAngle(-100 - q * 4,175 - q);
    SendAngles(up, low, sAVR);
    [x,y] = Postlab_Plot(2, sAVR);
    
    X = horzcat(X,x);
    Y = horzcat(Y,y);

end

[up,low] = calcAngle(-200,150);
SendAngles(up, low, sAVR);
pause(2);

for q = 1:24
    [up,low] = calcAngle(-200 + q * 4 ,150 + q * 4);
    SendAngles(up, low, sAVR);
    [x,y] = Postlab_Plot(2, sAVR);
    
    X = horzcat(X,x);
    Y = horzcat(Y,y);
end

plot(X,Y);
axis([-300, 0, 100, 300]);

fclose(sAVR);