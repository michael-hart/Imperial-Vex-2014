function [c1,c2] = get_fletcher(b)
if size(b) ~= 3
    disp('you dun goofed');
else
    c1 = uint16(0);
    c2 = uint16(0);

    for i = 1:3 
        c1 = mod(c1+uint16(b(i)),255);
        c2 = mod(c1+c2,255)
    end
end
end
        