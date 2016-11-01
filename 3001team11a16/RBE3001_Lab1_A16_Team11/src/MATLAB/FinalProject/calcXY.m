function [ endX, endY ] = calcXY( upTheta, lowTheta )
% calcXY calculates the x and y positions of the end Effector 
% given the angles of the links

upLength = 159.67;  %length including gripper 
                    %without gripper = 118

lowLength = 152.401;

%Transform to correct coordinate system
upTheta = upTheta / 10 - 90;
lowTheta = lowTheta / 10;

% Convert input angle to degree
upThetaRad = deg2rad(upTheta);
lowThetaRad = deg2rad(lowTheta);

% Using forward kinematics of two links. 
endX = lowLength * cos(lowThetaRad) + upLength * cos(upThetaRad + lowThetaRad);
endY = lowLength * sin(lowThetaRad) + upLength * sin(upThetaRad + lowThetaRad);

end

