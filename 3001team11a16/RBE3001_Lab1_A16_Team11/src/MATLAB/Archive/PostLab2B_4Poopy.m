



clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

[up,low] = calcAngle(-100,250);
SendAngles(up, low, sAVR);
pause(3);

[up,low] = calcAngle(-100,175);
SendAngles(up, low, sAVR);
[x1,y1] = Postlab_Plot(200, sAVR);

[up,low] = calcAngle(-200,150);
SendAngles(up, low, sAVR);
[x2,y2] = Postlab_Plot(200, sAVR);

[up,low] = calcAngle(-100,250);
SendAngles(up, low, sAVR);
[x3,y3] = Postlab_Plot(200, sAVR);

x = horzcat(x1, x2, x3);
y = horzcat(y1, y2, y3);
plot(x,y);
axis([-300, 0, 100, 300]);

fclose(sAVR);