leastCommonMultiple :: Integer -> Integer -> Integer
leastCommonMultiple m n = abs(m * n) `div` gcd m n
  where gcd a 0 = a
        gcd a b = gcd b (a `mod` b)

check :: Integer -> Integer -> Integer -> String
check a b c = if leastCommonMultiple a b == c then "Yes" else "No"

main = do
    print ("Test 1: " ++ check 10 3 30)
    print ("Test 2: " ++ check 2 3 6)
    print ("Test 3: " ++ check 10 10 10)
    print ("Test 4: " ++ check 5 2 10)
    print ("Test 5: " ++ check 6 18 18)