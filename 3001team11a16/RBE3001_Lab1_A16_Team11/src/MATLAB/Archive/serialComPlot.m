%Started by Jeffrey Tolbert improved by Sam Khalandovsky 
%Finished by Joseph St. Germain
%Edited by Lumbini Parnas and Evan Bosia for team 11
% clear all objects
clear all; close all;delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);
%Sets number of Samples
samples = 10000;
%max val of samples
maxVal = 50000;
%number of bytes per variable
dataSize = 2;
%Number of diffrent variables
varPerSample = 2; 
%Send start character
%fprintf(sAVR,'A');
%create array of data with initial values = 0
data = zeros(varPerSample,samples);
%variable for tracking number of samples
i = 1;
%retains the current plot and adds data when plot now is called
hold on;
%Number of variable to read in
for j=1:dataSize
    %handles stores an association to a function
    handles(j) = plot(1:samples,zeros(1,samples)); 
end
%set colors of lines in plot
colors = ['r','g','b','k','m'];

%runs until all samples are complete
while(i<=samples)
    %read 5 2-byte values from serial and save to newdata 
    %bytes recieved
  newData = fread(sAVR,varPerSample,'uint16');
  %save 1x4 array new data into the next row of data array
  %newData;
  data(:,i) = newData;
  %for 5 variables
  
  %CHANGED to varPerSample to avoid errors
  for j=1:varPerSample
      %handles stores an association to a function
      set(handles(j),'YData',data(j,:));
  end
  %increment i  
  i = i+1;
  %set plot axises
  axis([1 samples 0 maxVal])
  %Draw new data
  drawnow
end
%close serial port
fclose(sAVR);
%delet serial object
delete(sAVR);
%clear all;