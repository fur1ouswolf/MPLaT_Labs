combinationsWithRepetitions :: Integral a => a -> a -> a
combinationsWithRepetitions n m = product [n+i-1 | i <- [1..m]] `div` product [1..m]

check :: Integer -> Integer -> Integer -> String
check a b c = if combinationsWithRepetitions a b == c then "Yes" else "No"

main = do
    print ("Test 1: " ++ check 10 3 220)
    print ("Test 2: " ++ check 20 5 42504)
    print ("Test 3: " ++ check 1 1 1)