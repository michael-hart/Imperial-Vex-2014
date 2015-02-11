
def fletcher16(data_to_checksum):
    """ Data in is assumed an integer list """
    assert type(data_to_checksum[0]) == int
    sum1, sum2 = 0, 0
    for i in data_to_checksum:
        sum1 = (sum1 + i) % 255
        sum2 = (sum2 + sum1) % 255
    return (sum2 << 8) | sum1
	
def compare_checksum(data_to_checksum, checksum):
    chk = fletcher16(data_to_checksum)
    print "Checking: " + " ".join([hex(x) for x in data_to_checksum])
    return chk == (checksum[0] << 8) + checksum[1]
	
	
if __name__ == "__main__":
    test_arr = [1, 0x22, 0]
    c16 = fletcher16(test_arr)
    # Results generated using C functions
    assert (c16 >> 8) == 0x47
    assert (c16 & 0xFF) == 0x23
    test_arr += [(c16 >> 8) & 0xFF]
    test_arr += [c16 & 0xFF]
    assert compare_checksum(test_arr[:3], test_arr[3:])
    print "Test completed successfully"
