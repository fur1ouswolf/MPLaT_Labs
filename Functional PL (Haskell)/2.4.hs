import Data.List (tails)

type Queen = (Int, Int)

canAttack :: Queen -> Queen -> Bool
canAttack (x1, y1) (x2, y2) = x1 == x2 || y1 == y2 || abs (x1 - x2) == abs (y1 - y2)

hasAttack :: [Queen] -> Bool
hasAttack queens = any (uncurry canAttack) [(q1, q2) | (q1:qs) <- tails queens, q2 <- qs]

test :: [Queen] -> Bool -> String
test queens ans = if hasAttack queens == ans then "OK" else "WA"

main = do
  print("Test 1: " ++ test [(1, 1), (3, 2), (5, 3), (7, 4), (2, 5), (4, 6), (6, 7), (8, 8)] True)
  print("Test 2: " ++ test [(1, 1), (3, 2), (5, 3), (7, 4), (2, 5), (4, 6), (6, 7), (8, 8), (4, 4)] True)
  print("Test 3: "++ test [(1, 1), (3, 2), (5, 3), (7, 4), (2, 5), (4, 6), (6, 7)] False)
  print("Test 4: " ++ test [] False)