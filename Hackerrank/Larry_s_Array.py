import sys

def rotateArray(startIndex,endIndex,array,iter_dir = "left"):

     midIndex = startIndex + 1
     temp = array[startIndex]
     array[startIndex] = array[endIndex]
     array[endIndex] = array[midIndex]
     array[midIndex]= temp
     return array
     pass
# in these 0 is taken as 10
# 8 6 2 0 7 5 4 1 3 9
# 8 1 6 2 0 7 5 4 3 9
#workout starts
# 8 6 2 0 7 5 1 4 3 9
# 1 8 6 2 0 7 5 4 3 9
# 1 2 8 6 0 7 5 4 3 9
# 1 2 3 8 6 0 7 5 4 9
# 1 2 3 8 4 6 0 7 5 9 check curr num and previous num. if they are in vicinity, ie. the distance between them is less than 3 they are gone

#BRANCH OUT#
# 1 2 3 8 4 6 0 7 5 9 <- same as above (for integrity)
# 1 2 3 6 8 4 0 7 5 9
# 1 2 3 4 6 8 0 7 5 9 if the curr and previous numbers are a item apart, select the 3 indices immediately after the previous number then iterate twice. issue seems to be solved at the moment
# resume normal branch from here

#NORMAL BRANCH#
#move 5
# 1 2 3 4 6 8 0 7 5 9
# 1 2 3 4 6 8 5 0 7 9
# 1 2 3 4 5 6 8 0 7 9
# 1 2 3 4 5 6 7 8 10 9

###
#targetIndex -> this is the location of the previous small number
#this function just modifies the array by moving the required digit to the final place after n rotations
#this is a better optimised solution to rotateArray method being called in a for loop
#its time consistancy is constant

#TODO: fix the moveDigit function, to align the first element
def prepareArray(currentIndex):
    finalPosition =
    array.insert()
    array.pop(currentIndex)
    pass
def moveDigit(targetIndex,currentIndex,array):

    diff = currentIndex - targetIndex - 1
    addAtIndx = diff%3
    array.insert(targetIndex + addAtIndx,array[currentIndex])
    array.pop(currentIndex)
    return array
    pass


def canBeSorted(array,size):


    sortedArray = sorted(array)
    smlValIndx = array.index(sortedArray[0])
    index = 0
    moveDigit()

    pass


t = input()
for a0 in xrange(t):
    N = input()
    t0 = int(raw_input().strip().split())
    print canBeSorted(t0,N)
    pass
