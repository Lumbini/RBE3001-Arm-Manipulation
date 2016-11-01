%Started by Jeffrey Tolbert improved by Sam Khalandovsky 
%Finished by Joseph St. Germain
%Edited by Lumbini Parnas and Evan Bosia for team 11
% clear all objects
clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

%sample amount
samples = 10000;

%Send start character
fprintf(sAVR,'A');
data = zeros(4, samples);
i = 1;

while(i <= samples)
    A = fscanf(sAVR, '%d,%d,%d,%d');
    data(1:end,i) = A;
    i = i+1;
end


 plot([1:samples], data(1,1:end));
 hold on;
 plot([1:samples], data(2,1:end));
 hold on;
 plot([1:samples], data(3,1:end));
 hold on;
 plot([1:samples], data(4,1:end));

fclose(sAVR);
%delet serial object
delete(sAVR);
%clear all;