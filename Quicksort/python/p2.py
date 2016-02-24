'''WinPython 3.4.4'''

from time import time

# read file into array
start = time()
array = []
with open("QuickSort.txt", "rt") as f:
    for line in f:
        array.append(int(line))
finish = time()
time_elapsed = 1000.0 * (finish - start)
print("Time to read file: %.3f ms" % (time_elapsed,))

class Quicksort(object):
    def __init__(self):
        self.comparisons = 0
        
    def __call__(self, array, left, right, method):
        if right - left < 1:
            return
        else:
            self.comparisons += right - left
            pivot = self._pivot_index(array, left, right, method)
            pivot_value = array[pivot]
            array[pivot], array[left] = array[left], array[pivot]
            pivot = left
            for i in range(left + 1, right + 1):
                if array[i] < pivot_value:
                    array[pivot+1], array[i] = array[i], array[pivot+1]
                    pivot += 1
            array[left], array[pivot] = array[pivot], array[left]
            self.__call__(array, left, pivot - 1, method)
            self.__call__(array, pivot + 1, right, method)
        
    def reset_comparisons(self):
        self.comparisons = 0
        
    def _pivot_index(self, array, left, right, method):
        if method == 2:
            return right
        elif method == 3:
            middle_index = (left + right) // 2
            values = [(array[left], left), (array[middle_index], middle_index), (array[right], right)]
            values.sort()
            return values[1][1]
        else:
            return left
        
quicksort = Quicksort()
                   
# Part I: 59.999 ms
array_copy = list(array)
start = time()
quicksort(array_copy, 0, len(array_copy) - 1, 1)
finish = time()
time_elapsed = 1000.0 * (finish - start)
print("Time for sorting method 1: %.3f" % (time_elapsed,))
print("Number of comparisons: %d" % (quicksort.comparisons,))
quicksort.reset_comparisons()

# Part II: 59.998 ms
array_copy = list(array)
start = time()
quicksort(array_copy, 0, len(array_copy) - 1, 2)
finish = time()
time_elapsed = 1000.0 * (finish - start)
print("Time for sorting method 1: %.3f" % (time_elapsed,))
print("Number of comparisons: %d" % (quicksort.comparisons,))
quicksort.reset_comparisons()

# Part III: 59.998 ms
array_copy = list(array)
start = time()
quicksort(array_copy, 0, len(array_copy) - 1, 3)
finish = time()
time_elapsed = 1000.0 * (finish - start)
print("Time for sorting method 1: %.3f" % (time_elapsed,))
print("Number of comparisons: %d" % (quicksort.comparisons,))
quicksort.reset_comparisons()
        
