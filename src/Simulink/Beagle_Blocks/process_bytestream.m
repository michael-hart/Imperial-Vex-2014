
function [output, ready] = process_bytestream(input)
    if(verify_checksum(input)) 
        ready =1;
     
    else 
        ready =0;
    end
       output = input(4:5);
end

function output = verify_checksum(input)
	checksum = typecast([input(4), input(5)], 'uint16');
	fletcher = get_fletcher(input(1:3));
	output = (checksum == fletcher);
end

