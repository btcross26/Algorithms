### Quicksort problem from algorithms class
### Compile with options --opt:speed -d:release -d:danger for max speed

from strutils import nil
import strformat
from times import nil
from algorithm import sort
from sequtils import toSeq

# proc to read in array from file
proc readArr(intArr: var seq[int]) =
    let f: File = open("QuickSort.txt", fmRead)
    defer: f.close()

    var lineStr: string
    while readLine(f, lineStr):
        intArr.add(strutils.parseInt(lineStr))

# read in the array
echo "Reading integer array data..."
var startTime: float = times.cpuTime()
var intArr: seq[int] = newSeq[int]()
readArr(intArr)
var runTime: float = times.cpuTime() - startTime
echo fmt("Time to read file: {runTime:.3f} seconds")
echo()

# for value in intArr.items():
#     echo value
# echo "length: ", intArr.len


## quick sort solution code (sort done in place)
type
    quickSortIndex = enum
        qsiFirst
        qsiLast
        qsiMof3

proc swap(intArr: var seq[int], a, b: int) =
    var tmp: int = intArr[b]
    intArr[b] = intArr[a]
    intArr[a] = tmp

proc argsort(a: seq[int]): seq[int] =
    result = toSeq(0..a.len - 1)
    sort(result, proc (i, j: int): int = cmp(a[i], a[j]))

proc quickSortPivotIndex(intArr: seq[int], low, high: int,
        pivotType: quickSortIndex): int =
    case pivotType
        of qsiFirst:
            result = low
        of qsiLast:
            result = high
        of qsiMof3:
            let midIndex: int = (low + high) div 2
            var values: seq[int] = @[intArr[low], intArr[midIndex], intArr[high]]
            let index: int = argsort(values)[1]
            result = (
                case index
                of 0: low
                of 1: midIndex
                of 2: high
                else: low # shouldn't get here
            )

proc quickSort*(intArr: var seq[int], lowIndex: int, highIndex: int,
        pivotType: quickSortIndex = qsiFirst): int =
    var comparisons: int = 0
    if highIndex > lowIndex:
        var
            pivotIndex: int = quickSortPivotIndex(intArr, lowIndex, highIndex, pivotType)
            pivotValue: int = intArr[pivotIndex]
        swap(intArr, lowIndex, pivotIndex)
        pivotIndex = lowIndex
        for i in (lowIndex + 1)..highIndex:
            comparisons += 1
            if intArr[i] < pivotValue:
                swap(intArr, pivotIndex + 1, i)
                pivotIndex += 1
        swap(intArr, lowIndex, pivotIndex)
        comparisons += quickSort(intArr, pivotIndex + 1, highIndex, pivotType)
        comparisons += quickSort(intArr, lowIndex, pivotIndex - 1, pivotType)
        return comparisons
    else:
        return 0

# overloaded with just an array and method
proc quickSort*(intArr: var seq[int], pivotType: quickSortIndex): int =
    return quickSort(intArr, 0, intArr.high, pivotType)

# for value in intArr.items():
#     write(stdout, value, " ")
# echo()

# answer 1
echo "Calculating comparisons for question 1..."
startTime = times.cpuTime()
var answer: int = quickSort(intArr, qsiFirst)
runTime = times.cpuTime() - startTime
echo fmt("Number of comparisons: {answer:d}")
echo fmt("Runtime: {runTime:.3f} seconds")
echo()

# echo intArr   # check the ordering

# reset and re-read intArr
`=destroy`(intArr)
wasMoved(intArr)
readArr(intArr)

# answer 2
echo "Calculating comparisons for question 2..."
startTime = times.cpuTime()
answer = quickSort(intArr, qsiLast)
runTime = times.cpuTime() - startTime
echo fmt("Number of comparisons: {answer:d}")
echo fmt("Runtime: {runTime:.3f} seconds")
echo()

# reset and re-read intArr
`=destroy`(intArr)
wasMoved(intArr)
readArr(intArr)

# answer 3
echo "Calculating comparisons for question 3..."
startTime = times.cpuTime()
answer = quickSort(intArr, qsiMof3)
runTime = times.cpuTime() - startTime
echo fmt("Number of comparisons: {answer:d}")
echo fmt("Runtime: {runTime:.3f} seconds")
echo()
