close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

time = 2000;
i = 1;

E = [];

flushinput(sAVR);
while(i <= time)
    if(fread(sAVR,1,'char') == 'A')
        A = fread(sAVR,5,'int16');
        if(isempty(E))
            E = A;
        else
            E(:,end+1) = A;
        end
        i = i + 1;
    end
    disp(i);
end

t = [1:1:time];

t6 = E; 

plot(t, E);

