calc :: String -> [Integer]
calc = foldl f [] . words
    where
     f :: [Integer] -> String -> [Integer]
     f (x:y:zs) "+"    = (y + x):zs
     f (x:y:zs) "-"    = (y - x):zs
     f (x:y:zs) "*"    = (y * x):zs
     f (x:y:zs) "/"    = (y `div` x):zs
     f xs       y      = read y : xs