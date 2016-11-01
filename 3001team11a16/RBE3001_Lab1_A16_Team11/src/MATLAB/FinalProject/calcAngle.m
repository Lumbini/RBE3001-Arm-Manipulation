function [upperTheta, lowerTheta] = calcAngle(X, Y)
% calcAngle outputs the angles of lower link and Upper link
% given required the x and y positions of the end effector
% The outputs are in 10ths of degrees

u = 159.16; %mm
l = 152.4; %mm

cosine_theta = (X^2 + Y^2 - l^2 - u^2)/(2 * l * u);
sine_theta = sqrt(1 - cosine_theta^2);

upperTheta = atan2(sine_theta, cosine_theta);

%upperTheta = [upperTheta, -upperTheta];

k1 = l + u * cos(upperTheta);
k2 = u * sin(upperTheta);

r = sqrt(k1^2 + k2^2);

y = atan2(k2, k1);


lowerTheta = atan2(Y,X) - atan2(k2,k1);

disp(lowerTheta);

if(lowerTheta < 0)
    lowerTheta = lowerTheta + 2 * abs(y);
    upperTheta = -upperTheta;
end

upperTheta =  upperTheta * 180 * 10 / pi;
lowerTheta = lowerTheta * 180 * 10 / pi;

end

