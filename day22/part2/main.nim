import strutils, deques, tables

let input = readFile("input.txt")

type
    Deck = Deque[int]

var startDeck1: Deck = initDeque[int]()
var startDeck2: Deck = initDeque[int]()
var currentDeck = 0

#  returns (winner, sum)
proc playGame(deckOne: Deck, deckTwo: Deck): (int, int) =
    var deck1 = deckOne
    var deck2 = deckTwo

    var playedDeck1 = initTable[string, int]()
    var playedDeck2 = initTable[string, int]()

    var winningDeck = 0

    # Otherwise, at least one player must not have enough cards left in their deck to recurse; the winner of the round is the player with the higher-value card.
    while deck1.len() > 0 and deck2.len() > 0:
        # Before either player deals a card, if there was a previous round in this game that had exactly the same cards in the same order in the same players' decks, the game instantly ends in a win for player 1. Previous rounds from other games are not considered. (This prevents infinite games of Recursive Combat, which everyone agrees is a bad idea.)
        if $deck1 in playedDeck1 and $deck2 in playedDeck2:
            return (1, 0)


        playedDeck1[$deck1] = 1
        playedDeck2[$deck2] = 1


        let card1 = deck1.popFirst()
        let card2 = deck2.popFirst()

        # If both players have at least as many cards remaining in their deck as the value of the card they just drew, the winner of the round is determined by playing a new game of Recursive Combat
        if card1 <= deck1.len() and card2 <= deck2.len():
            var deck1Shrinked = deck1
            var deck2Shrinked = deck2

            while deck1Shrinked.len() > card1:
                discard deck1Shrinked.popLast()
            while deck2Shrinked.len() > card2:
                discard deck2Shrinked.popLast()

            let (winner, _) = playGame(deck1Shrinked, deck2Shrinked)

            if winner == 1:
                deck1.addLast(card1)
                deck1.addLast(card2)
            else:
                deck2.addLast(card2)
                deck2.addLast(card1)
        else:
            # Otherwise, this round's cards must be in a new configuration; the players begin the round by each drawing the top card of their deck as normal.
            if card1 > card2:
                deck1.addLast(card1)
                deck1.addLast(card2)
            elif card2 > card1:
                deck2.addLast(card2)
                deck2.addLast(card1)

    winningDeck = if deck1.len() > 0: 1 else: 2

    var sum = 0
    let deck = if winningDeck == 1: deck1 else: deck2
    for pos, value in deck.pairs:
        sum += (deck.len() - pos) * value

    return (winningDeck, sum)



#  parse file
for line in input.splitLines():
    if line.startsWith("Player"):
        currentDeck.inc()
        continue
    if line.len == 0:
        continue

    if currentDeck == 1:
        startDeck1.addLast(line.parseInt())
    else:
        startDeck2.addLast(line.parseInt())

var sum = 0
var winner = 0
(winner, sum) = playGame(startDeck1, startDeck2)

echo sum



