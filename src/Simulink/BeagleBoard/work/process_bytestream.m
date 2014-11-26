
function [output, ready] = process_bytestream(input)
    if(verify_checksum(input)) 
        ready =1;
     
    else 
        ready =0;
    end
       output = input(4:5);
end

function output = verify_checksum(input)

sum1=0;
sum2=0;
for i = 1:3
 sum1 = mod((sum1 + input(i)), 255);
 input(i);
 sum2 = mod((sum2 + sum1), 255);
end

fletcher = typecast([sum1,sum2],'uint16');
checksum = typecast([input(4), input(5)], 'uint16');
output = (checksum == fletcher);
%output = [checksum, fletcher];
end

