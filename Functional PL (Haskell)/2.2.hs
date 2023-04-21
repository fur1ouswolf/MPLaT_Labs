f :: [String] -> String
f list = list[(joseph (length list) 5) - 1]

joseph :: Integer -> Integer -> Integer
joseph n k | n > 1 = ((joseph (n - 1) k + k - 1) `mod` n) + 1
           | otherwise = 1

test :: Integer -> Integer -> String
test n ans = if joseph n 5 == ans then "OK" else "WA"

main = do
  print("Test 1: " ++ test 10 3)
  print("Test 2: " ++ test 1 1)
  print("Test 3: " ++ test 2 2)
  print("Test 4: " ++ test 5 2)
  print("Test 5: " ++ test 7 6)
  print("Test 6: " ++ test 20 7)