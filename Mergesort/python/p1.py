'''WinPython 3.4.4'''

import time

class MergeSort(object):
    def __init__(self):
        self.inversions = 0
        
    def __call__(self, array, left_ind = 0, right_ind = -1):
        assert left_ind >= 0 and left_ind < len(array)
        if right_ind == -1:
            right_ind = len(array) - 1
        elif right_ind < left_ind:
            right_ind = left_ind
        return self._sort(array, left_ind, right_ind)
        
    def _sort(self, array, left_ind, right_ind):
        if right_ind - left_ind == 0:
            return [array[left_ind]]
        else:
            index = (left_ind + right_ind) // 2
            return self._merge(self._sort(array, left_ind, index), \
                               self._sort(array, index + 1, right_ind))
        
    def _merge(self, left, right):
        nl, nr, i, j, index = len(left), len(right), 0, 0, 0
        merged = [0] * (nl + nr)
        while i < nl and j < nr:
            if left[i] <= right[j]:
                merged[index] = left[i]
                i += 1
            else:
                merged[index] = right[j]
                self.inversions += (nl - i)
                j += 1
            index += 1
            
        if i == nl:
            merged[index:] = right[j:]
        elif j == nr:
            merged[index:] = left[i:]
            
        return merged
        
    def reset_inversions(self):
        self.inversions = 0

# read file        
filename = "IntegerArray.txt"
start = time.time()
integer_array = []
with open(filename, "rt") as f:
    for line in f:
        integer_array.append(int(line))
finish = time.time()
total_time = finish - start
print("Time to read file: %.3f seconds" % total_time)   # 0.055 seconds

# sort list
start = time.time()
merge_sort = MergeSort()
merge_sort(integer_array)
finish = time.time()
total_time += finish - start
print("Time to sort list: %.3f seconds" % (finish - start,))   # 0.903 seconds
print("Total processing time: %.3f seconds" % total_time)      # 0.957 seconds

# print answer
print()
print("Number of inversions: %d" % merge_sort.inversions)

