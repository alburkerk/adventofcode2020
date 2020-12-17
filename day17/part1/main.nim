import
  sets, strutils, std/enumerate, strformat

type
  Vec = tuple[x, y, z: int]
  Mat = tuple[a, b, c: Vec]
  # active cubes map
  Map = HashSet[Vec]

proc parse(text: string): Map =
  for y, line in enumerate(text.splitLines):
    for x, c in line:
      if c == '#':
        result.incl((x, y, 0))

# returns coordinates of the bounding box of the pocket
proc pocketCoordinates(map: Map): (int, int, int, int, int, int) =
  var xmin, xmax, ymin, ymax, zmin, zmax: int

  (xmin, ymin, zmin) = (int.high, int.high, int.high)
  (xmax, ymax, zmax) = (-int.high, -int.high, -int.high)

  for c in map:
    if c.x < xmin:
      xmin = c.x
    if c.x > xmax:
      xmax = c.x
    if c.y < ymin:
      ymin = c.y
    if c.y > ymax:
      ymax = c.y
    if c.z < zmin:
      zmin = c.z
    if c.z > zmax:
      zmax = c.z

  return (xmin, xmax, ymin, ymax, zmin, zmax)

iterator neighbors(v: Vec): Vec =
  for x in -1 .. 1:
    for y in -1 .. 1:
      for z in -1 .. 1:
        if (x, y, z) == (0, 0, 0):
          continue
        yield (v.x + x, v.y + y, v.z + z)


proc loop(map: var Map) =
  var newMap = map
  let (xmin, xmax, ymin, ymax, zmin, zmax) = pocketCoordinates(map)
  var sum: int
  var v: Vec

  for x in (xmin - 1) .. (xmax + 1):
    for y in (ymin - 1) .. (ymax + 1):
      for z in (zmin - 1) .. (zmax + 1):
        sum = 0
        v = (x, y, z)
        for n in neighbors(v):
          if n in map:
            inc(sum)

        if v in map and sum in [2, 3]:
          newMap.incl(v)
        else:
          newMap.excl(v)
        if v notin map and sum == 3:
          newMap.incl(v)

  map = newMap

let input = readFile("input.txt")
var map = parse(input)
echo pocketCoordinates(map)

for i in 1..6:
  loop(map)

echo "solution : ", map.len
