function RGB = get_shotsnap(OBJ)
RGB = getsnapshot(OBJ);
while((RGB(1,1) <= 130) && (RGB(1,1) >= 120))
 RGB = getsnapshot(OBJ);
end
end