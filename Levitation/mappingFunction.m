%% Create lookup table

for i = 2:length(lookuptable);
   for k = 1:length(rawdata);
       if(lookuptable(i,2) < rawdata(k, 2))
           slope = (rawdata(k,2) - rawdata(k-1, 2)) / (rawdata(k,1) - rawdata(k-1, 1));
           delta = lookuptable(i,2) - rawdata(k,2);
           estimate(i,1) = round(rawdata(k,1) + delta/slope);
           break;
       end
   end
end