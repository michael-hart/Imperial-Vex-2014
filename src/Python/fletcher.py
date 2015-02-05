
def fletcher16(data_to_checksum):
    """ Data in is assumed to be string characters, rather than numbers """
    assert type(data_to_checksum[0]) == str
    sum1, sum2 = 0, 0
    for i in data_to_checksum:
        sum1 = (sum1 + ord(i)) % 255
        sum2 = (sum2 + sum1) % 255
    return (sum2 << 8) | sum1
	
def compare_checksum(data_to_checksum, checksum):
    chk = fletcher16(data_to_checksum)
    return chk == (ord(checksum[0]) << 8) + ord(checksum[1])
	
	
if __name__ == "__main__":
    test_arr = map(chr, [1, 0x22, 0])
    c16 = fletcher16(test_arr)
    # Results generated using C functions
    assert (c16 >> 8) == 0x47
    assert (c16 & 0xFF) == 0x23
    test_arr += chr((c16 >> 8) & 0xFF)
    test_arr += chr(c16 & 0xFF)
    assert compare_checksum(test_arr[:3], test_arr[3:])
    print "Test completed successfully"