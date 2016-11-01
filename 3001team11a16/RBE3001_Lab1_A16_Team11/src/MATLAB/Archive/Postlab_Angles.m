function [theta2, theta1] = Postlab_Angles(time, sAVR)
    flushinput(sAVR);
    
    theta2 = [];
    theta1 = [];
    
    for i = 1:time
        if(fread(sAVR,1,'char') == 'A')
            A = fread(sAVR,2,'uint16');
            if(isempty(theta2))
                theta2 = A(1);
                theta1 = A(2);
            else
                theta2(end+1) = A(1);
                theta1(end+1) = A(2);
            end
        end
        pause(.01);
    end
end