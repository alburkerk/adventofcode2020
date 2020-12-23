import lists, strutils

var cups = initSinglyLinkedRing[int]()

let input = "247819356"
var min = 9999999999
var max = 0

var lastAddedCup = cups.head

for i in input:
    lastAddedCup = newSinglyLinkedNode[int](parseInt($i))
    cups.append(lastAddedCup)

    if lastAddedCup.value > max:
        max = lastAddedCup.value
    if lastAddedCup.value < min:
        min = lastAddedCup.value

lastAddedCup.next = cups.head

var currentCup = cups.head

for i in 1 .. 100:

    var removedCups = currentCup.next

    currentCup.next = removedCups.next.next.next
    # echo "with removed 3 cups", cups

    var destination = currentCup.value - 1
    if(destination < min):
        destination = max

    # If this would select one of the cups that was just picked up, the crab will keep subtracting one until it finds a cup that wasn't just picked up.
    while removedCups.value == destination or removedCups.next.value ==
            destination or removedCups.next.next.value == destination:
        dec(destination)

        # If at any point in this process the value goes below the lowest value on any cup's label, it wraps around to the highest value on any cup's label instead.
        if(destination < min):
            destination = max

    var cup = currentCup

    while cup.value != destination:
        cup = cup.next

    removedCups.next.next.next = cup.next

    cup.next = removedCups

    currentCup = currentCup.next

var firstCup = cups.head
while firstCup.value != 1:
    firstCup = firstCup.next

firstCup = firstCup.next

var result = ""

while firstCup.value != 1:
    result = result & $(firstCup.value)
    firstCup = firstCup.next

echo result
