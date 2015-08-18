'''Programming Assignment 6 - WinPython 3.4.4'''

from time import time

# Version 1: Vector Based Implementation
def two_sum_vector(filename, lower, upper):
    assert lower < upper, "Invalid range arguments"
    with open(filename, "rt") as f:
        num_list = []
        for value in f:
            num_list.append(int(value))
    num_list.sort()
    
    min_index, max_index = 0, len(num_list) - 1
    existing_sums = set()
    while max_index > min_index:
        while num_list[min_index] + num_list[max_index] > upper and max_index > min_index:
            max_index -= 1
        for i in range(max_index, min_index, -1):
            if num_list[min_index] + num_list[i] < lower:
                break
            elif num_list[min_index] != num_list[i]:
                existing_sums.update([num_list[min_index] + num_list[i]])
        min_index += 1
    return len(existing_sums)

# time = 2.032 seconds    
start = time()
answer = two_sum_vector("2sum.txt", -10000, 10000)
finish = time()
elapsed = 1.0 * (finish - start)
print("Vector Based Implementation:")
print("Computation time: %.3f seconds" % (elapsed,))
print("          Answer: %d" % (answer,))
print()


# Version 2: Hash Table based implementation    
def two_sum_hashtable(filename, lower, upper):
    assert lower < upper, "Invalid range arguments"
    assert type(upper) is int and type(lower) is int
    range = upper - lower
    with open(filename, "rt") as f:
        num_map = dict()
        for value in f:
            value = int(value) - lower
            bucket = int(value / range)
            if bucket not in num_map:
                num_map[bucket] = set([value])
            else:
                num_map[bucket].update([value])
    
    existing_sums = set()
    for key in num_map:
        if key <= 0 and -key in num_map:
            for value1 in num_map[key]:
                for value2 in num_map[-key]:
                    if value1 + value2 <= range and value1 + value2 >= 0:
                        existing_sums.update([value1 + value2])
        if key <= 0 and (-key + 1) in num_map:
            for value1 in num_map[key]:
                for value2 in num_map[-key + 1]:
                    if value1 + value2 <= range and value1 + value2 >= 0:
                        existing_sums.update([value1 + value2])
        if key == 1:
            for value1 in num_map[key]:
                for value2 in num_map[key]:
                    if value1 != value2 and value1 + value2 <= range and value1 + value2 >= 0:
                        existing_sums.update([value1 + value2])
    return len(existing_sums)



# time = 3.5 seconds
start = time()
answer = two_sum_hashtable("2sum.txt", -10000, 10000)
finish = time()
elapsed = 1.0 * (finish - start)
print("Hash Table Based Implementation:")
print("Computation time: %.3f seconds" % (elapsed,))
print("          Answer: %d" % (answer,))
print()