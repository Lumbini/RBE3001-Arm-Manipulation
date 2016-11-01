clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);

pause(1);

while(1)
    if(fread(sAVR,1,'char') == 'A')
        A = fread(sAVR,2,'uint16');
        %disp(A);
        realTimePlot(A(1), A(2));
        drawnow;
        %SendAngles(0, 1800, sAVR);
    end
end