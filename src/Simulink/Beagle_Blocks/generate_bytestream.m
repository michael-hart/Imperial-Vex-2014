function b = generate_bytestream(q, serial_open)
persistent ID; 
if isempty(ID)
	ID = uint8(0);
end
if size(q) ~= 2 
    disp('you dun goofed')
elseif serial_open==0
    disp('serial comms are down')
else
    b = uint8([q(1),q(2),ID])
    [u,v] = get_fletcher(b);
    b = [b,u,v];
    ID = ID +1
end
end
