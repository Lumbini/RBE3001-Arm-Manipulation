%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% RBE 3001 - A16
% Team 11
% Author: Lumbini Parnas, Evan Bosia
%
% Description: This is the final script to perform all MATLAB instructions
% which include kinematic calculations and real time plotting of the arm.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% clear all objects
clear all; close all; delete(instrfindall);
%sets up serial port object
sAVR = serial('COM3','BaudRate',115200);
%opens com port
fopen(sAVR);
%waits a second
pause(1);

state = 'Real Time Plot.';

% State: DETECT_BLOCK
% AVR sends the x and y position of the block
% MATLAB Calculates the inverse kinematics and return the angles for the
% joints
% Format: Bitwise
% Receives: x and y in mm - 2 ints and 1 char in the beginning to check
% data accuracy
% Returns: theta1 and theta2

% State: ALL states
% Real time plotting of the arm
% Receieves the joint angles from the AVR
% Plots it using the realTimePlot function, displays the plot.

while(1)
    character = fread(sAVR, 1, 'char');
    %Calculate Kinematics loop
    if(character == 'A')
        A = fread(sAVR, 2, 'int16');
        %disp(A);
        [up, low] = calcAngle(A(1), A(2));
        disp(A);
    %Real time Plotting loop
    elseif(character == 'P')
        P = fread(sAVR,2,'int16');
        %disp(P);
        
        realTimePlot(P(1), P(2), state);
        drawnow;
        %sendAngles(0, 1800, sAVR);
    %Sends Angles when the trigger is received from AVR
    elseif(character == 'G')
        sendAngles(up, low, sAVR);
        
    %Sets title of the Graph
    elseif(character == 'I')
        state = 'Initializing';
        
    elseif(character == 'C')
        state = 'Caliberating Sensors';
    
    elseif(character == 'B')
        state = 'Ready to Sort!';
    
    elseif(character == 'D')
        state = 'Looking for Block';
    
    elseif(character == 'T')
        state = 'Waiting to Pick up';
    
    elseif(character == 'M')
        state = 'Moving to Pick up';
        
    elseif(character == 'Q')
        state = 'Picking Up stuff!';
        
    elseif(character == 'W')
        state = 'Finding Weight';
        
    elseif(character == 'H')
        state = 'Sorting Heavy';
        
    elseif(character == 'L')
        state = 'Sorting Light';
    end
end
