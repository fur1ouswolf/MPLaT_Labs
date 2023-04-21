towerofhanoi :: Int -> Int -> Int -> Int -> [(Int, Int)]
towerofhanoi x y z 1 = [(x, y)]
towerofhanoi x y z n = towerofhanoi x z y (n - 1) ++ [(x, y)] ++ towerofhanoi z y x (n - 1)

solve :: Int -> [(Int, Int)]
solve n = towerofhanoi 1 2 3 n

test :: Int -> [(Int, Int)] -> String
test n ans = if solve n == ans then "OK" else "WA"

main = do
    print("Test 1: " ++ test 1 [(1,2)])
    print("Test 2: " ++ test 3 [(1,2),(1,3),(2,3),(1,2),(3,1),(3,2),(1,2)])
    print("Test 3: " ++ test 5 [(1,2),(1,3),(2,3),(1,2),(3,1),(3,2),(1,2),(1,3),(2,3),(2,1),(3,1),(2,3),(1,2),(1,3),(2,3),(1,2),(3,1),(3,2),(1,2),(3,1),(2,3),(2,1),(3,1),(3,2),(1,2),(1,3),(2,3),(1,2),(3,1),(3,2),(1,2)])