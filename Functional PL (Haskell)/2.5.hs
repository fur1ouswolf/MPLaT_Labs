isSelfDual :: [Int] -> Bool
isSelfDual function = function == map comp (reverse function)
  where comp 0 = 1
        comp 1 = 0

test :: [Int] -> Bool -> String
test f ans = if isSelfDual f == ans then "OK" else "WA"

main = do
  print("Test 1: " ++ test [0, 1, 1, 0, 1, 0, 0, 1] True)
  print("Test 2: " ++ test [1, 0, 0, 1] False)