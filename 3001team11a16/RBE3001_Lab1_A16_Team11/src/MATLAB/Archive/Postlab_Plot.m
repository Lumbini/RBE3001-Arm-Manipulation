function [X,Y] = Postlab_Plot(time, sAVR)
    flushinput(sAVR);
    
    X = [];
    Y = [];
    
    for i = 1:time
        if(fread(sAVR,1,'char') == 'A')
            A = fread(sAVR,2,'int');
            [x,y] = calcXY(A(1), A(2));
            if(isempty(X))
                X = x;
                Y = y;
            else
                X(end+1) = x;
                Y(end+1) = y;
            end
        end
        pause(.01);
    end
end