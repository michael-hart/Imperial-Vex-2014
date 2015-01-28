from _int import *
def compute(data_to_checksum, size, modulo, limit = None):
    sum, sum_of_sum = 1, 0
    length = len(data_to_checksum)
    if limit is not None and length > limit:
        data_to_checksum = data_to_checksum[:limit]
    for char in data_to_checksum:
        sum += ord(char)
	sum_of_sum += sum
	sum %= modulo
	sum_of_sum += sum
	sum_of_sum %= modulo
    return (sum_of_sum << (size / 2 )) + sum

def fletcher16(data_to_checksum):
    return compute(data_to_checksum, 8, limit=21)

if __name__ == "__main__":
    import test.fletcher_test
