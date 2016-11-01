



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
[x1,y1] = Postlab_Angles(200, sAVR);

[up,low] = calcAngle(-200,150);
SendAngles(up, low, sAVR);
[x2,y2] = Postlab_Angles(200, sAVR);

[up,low] = calcAngle(-100,250);
SendAngles(up, low, sAVR);
[x3,y3] = Postlab_Angles(200, sAVR);

theta2 = horzcat(x1, x2, x3);
theta1 = horzcat(y1, y2, y3);
siz = size(theta2);
time = (0:1:(siz(2) - 1));

v1 = 0;
v2 = 0;

for count = 2:siz(2)
    v1(end+1) = (theta1(count) - theta1(count - 1))/ 0.1;
    v2(end+1) = (theta2(count) - theta2(count - 1))/ 0.1;
end

a1 = 0;
a2 = 0;

for count = 2:siz(2)
    a1(end+1) = (v1(count) - v1(count - 1))/ 0.1;
    a2(end+1) = (v2(count) - v2(count - 1))/ 0.1;
end
plot(time,theta1,time,theta2, time, v1, time, v2);



fclose(sAVR);