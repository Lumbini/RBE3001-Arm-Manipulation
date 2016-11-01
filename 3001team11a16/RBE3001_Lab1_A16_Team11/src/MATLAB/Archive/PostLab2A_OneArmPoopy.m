clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

theta2 = [];
current = [];

for c = 1:300
    if(fread(sAVR,1,'char') == 'A')
        A = fread(sAVR,2,'int16');
        if(isempty(theta2))
            theta2 = A(1);
            current = A(2);
        else
            theta2(end+1) = A(1);
            current(end+1) = A(2);
        end
    end
    pause(0.01);
end

siz = size(theta2);
time = (0:1:(siz(2) - 1));

v2 = 0;

for count = 2:siz(2)
    v2(end+1) = (theta2(count) - theta2(count - 1))/ 0.1;
end

v2(1) = 0;

a2 = 0;

for count = 2:siz(2)
    a2(end+1) = (v2(count) - v2(count - 1))/ 0.1;
end

a2(1) = 0;

plot(time,theta2, time, v2, time, current);



fclose(sAVR);