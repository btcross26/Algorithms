### Mergesort problem from algorithms class
### Compile with options --opt:speed -d:release -d:danger for max speed

from strutils import nil
import strformat
from times import nil

# proc to read in array from file
proc readArr(intArr: var seq[int]) =
    let f: File = open("IntegerArray.txt", fmRead)
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


# merge sort solution code
type
    mergeSortResult = ref object
        sortedArr: seq[int]
        inversions: int

proc mergeWithInversions(leftRes, rightRes: sink mergeSortResult): mergeSortResult =
    ## Perform merge but also count inversions
    # const/var declarations
    let
        leftArr: seq[int] = leftRes.sortedArr
        rightArr: seq[int] = rightRes.sortedArr
    var
        mergedArr: seq[int] = newSeq[int]()
        inversions: int = leftRes.inversions + rightRes.inversions
        i: int = 0
        j: int = 0

    # perform the merge and count inversions
    while true:
        if leftArr[i] <= rightArr[j]:
            mergedArr.add(leftArr[i])
            i += 1
        else:
            mergedArr.add(rightArr[j])
            inversions += leftArr.len - i
            j += 1

        if i == leftRes.sortedArr.len:
            for k in j..rightArr.high:
                mergedArr.add(rightArr[k])
            break

        if j == rightArr.len:
            for k in i..leftArr.high:
                mergedArr.add(leftArr[k])
            break
    return mergeSortResult(sortedArr: mergedArr, inversions: inversions)


proc mergeSortWithInversions*(intArr: seq[int]): mergeSortResult =
    ## MergeSort recursion - result type is custom to count inversions
    if intArr.len <= 1:
        return mergeSortResult(sortedArr: intArr, inversions: 0)
    else:
        let
            i: int = intArr.len div 2
            left: mergeSortResult = mergeSortWithInversions(intArr[0..<i])
            right: mergeSortResult = mergeSortWithInversions(intArr[
                    i..<intArr.len])
        return mergeWithInversions(left, right)


# Find the answer using the above algorithms
echo "Sorting and calculating inversions..."
startTime = times.cpuTime()
let answer: mergeSortResult = mergeSortWithInversions(intArr)
runTime = times.cpuTime() - startTime
echo fmt("Time to compute inversions: {runTime:.3f} seconds")

# for value in answer.sortedArr.items():
#     write(stdout, value, " ")
# echo()

echo "Number of inversions: ", answer.inversions
