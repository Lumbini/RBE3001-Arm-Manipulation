function [] = sendAngles(upper, lower, sAVR)

upper = int16(upper);
lower = int16(lower);

%disp(upper);
%disp(lower);

upLink = typecast(upper, 'int8');

%disp(upLink(2));
%disp(upLink(1));

lowLink = typecast(lower, 'int8');

%disp(lowLink(2));
%disp(lowLink(1));


fwrite(sAVR, upLink(2), 'int8');
fwrite(sAVR, upLink(1), 'int8');

fwrite(sAVR, lowLink(2), 'int8');
fwrite(sAVR, lowLink(1), 'int8');

end