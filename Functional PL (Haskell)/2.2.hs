f :: [String] -> String
f list = list !! ((joseph (length list) 5) - 1)

joseph :: Int -> Int -> Int
joseph n k | n > 1 = ((joseph (n - 1) k + k - 1) `mod` n) + 1
           | otherwise = 1

test :: [String] -> String -> String
test s ans = if f s == ans then "OK" else "WA"

main = do
  print("Test 1: " ++ test ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"] "3")
