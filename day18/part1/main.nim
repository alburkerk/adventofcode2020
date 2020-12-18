import deques, strutils, std/enumerate

proc isNumber(s: string): bool =
  try:
    discard s.parseInt()
    result = true
  except ValueError:
    result = false

proc isNumber(c: char): bool =
  return isNumber($c)

proc expression2rpn(expression: string): string =
  var newExpression: string = ""
  var operatorsStack = initDeque[char]()

  for e in expression:
    if e.isNumber():
      newExpression.add(e & " ")
    else:
      if e == '+':
        while len(operatorsStack) > 0 and operatorsStack.peekLast() != '(':
          newExpression.add(operatorsStack.popLast() & " ")
        operatorsStack.addLast(e)
      if e == '*':
        while len(operatorsStack) > 0 and operatorsStack.peekLast() != '(':
          newExpression.add(operatorsStack.popLast() & " ")
        operatorsStack.addLast(e)
      if e == '(':
        operatorsStack.addLast(e)
      if e == ')':
        var tmp = operatorsStack.popLast()
        # find matching parentheses
        while tmp != '(':
          newExpression &= tmp & " "
          tmp = operatorsStack.popLast()

  while len(operatorsStack) > 0:
    newExpression.add(operatorsStack.popLast() & " ")

  return newExpression

proc eval(expression: string): int =
  var stack = initDeque[int]()

  for e in expression.split(' '):
    if e.isNumber():
      stack.addLast(e.parseInt())
    elif e == "*" or e == "+":
      let a = stack.popLast()
      let b = stack.popLast()
      var res = 0
      if e == "+":
        res = a + b
      else:
        res = a * b
      stack.addLast(res)

  return stack.popLast()

var sum = 0
let input = readFile("input.txt")
for i in input.splitLines():
  if len(i) == 0:
    continue
  sum += eval(expression2rpn(i))

echo sum
