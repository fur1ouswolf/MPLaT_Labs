import Data.Char (digitToInt)

reverseList :: [a] -> [a]
reverseList [] = []
reverseList (x:xs) = reverseList xs ++ [x]

doubleEveryOther :: [Int] -> [Int]
doubleEveryOther xs = reverseList $ zipWith (*) (reverseList xs) (cycle [1,2])

sumDigits :: Int -> Int
sumDigits n = sum $ map digitToInt $ show n

luhn :: String -> Bool
luhn s = sum (map sumDigits (doubleEveryOther (map digitToInt s))) `mod` 10 == 0

test:: String -> Bool -> String
test cardn ans = if luhn cardn == ans then "OK" else "WA"

main = do
  print("Test 1: " ++ test "4111111111111111" True)
  print("Test 2: " ++ test "4111111111111112" False)