import lists, strutils, tables

const oneMillion = 1000000
const tenMillions = 10 * oneMillion

var cups = newSeq[SinglyLinkedNode[int]](oneMillion + 1)

let input = "247819356"
var min = 1
var max = oneMillion

for i in 0 .. len(input) - 1:
    cups[parseInt($input[i])] = newSinglyLinkedNode[int](parseInt($input[i]))
    if i != 0:
        cups[parseInt($input[i-1])].next = cups[parseInt($input[i])]

cups[10] = newSinglyLinkedNode[int](10)
for i in 10 .. oneMillion - 1:
    cups[i + 1] = newSinglyLinkedNode[int](i + 1)
    cups[i].next = cups[i + 1]

cups[10].next = cups[11]

cups[parseInt($input[len(input) - 1])].next = cups[10]
cups[oneMillion] = newSinglyLinkedNode[int](oneMillion)
cups[oneMillion].next = cups[parseInt($input[0])]
cups[oneMillion - 1].next = cups[oneMillion]

var currentCup = parseInt($input[0])

for i in 1 .. tenMillions:
    var removedCups = cups[currentCup].next

    cups[currentCup].next = removedCups.next.next.next

    var destination = cups[currentCup].value - 1

    if(destination < min):
        destination = max

    while removedCups.value == destination or removedCups.next.value ==
            destination or removedCups.next.next.value == destination:
        dec(destination)

        if(destination < min):
            destination = max

    removedCups.next.next.next = cups[destination].next

    cups[destination].next = removedCups

    currentCup = cups[currentCup].next.value

let a = cups[1].next.value
let b = cups[1].next.next.value

echo a * b
