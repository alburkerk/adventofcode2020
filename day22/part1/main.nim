import sequtils, strutils, deques

let input = readFile("input.txt")

type
    Deck = Deque[int]

var deck1: Deck = initDeque[int]()
var deck2: Deck = initDeque[int]()
var currentDeck = 0

#  parse file
for line in input.splitLines():
    if line.startsWith("Player"):
        currentDeck.inc()
        continue
    if line.len == 0:
        continue

    if currentDeck == 1:
        deck1.addLast(line.parseInt())
    else:
        deck2.addLast(line.parseInt())


while deck1.len() > 0 and deck2.len() > 0:
    let card1 = deck1.popFirst()
    let card2 = deck2.popFirst()
    if card1 > card2:
        deck1.addLast(card1)
        deck1.addLast(card2)
    elif card2 > card1:
        deck2.addLast(card2)
        deck2.addLast(card1)


let deck: Deck = if deck1.len() > 0: deck1 else: deck2

var sum = 0

for pos, value in deck.pairs:
    sum += (deck.len() - pos) * value

echo sum



