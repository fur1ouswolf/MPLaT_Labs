import Control.Monad (replicateM_)
import Data.List (delete, (\\))
import System.CPUTime
import System.Process (callCommand)

calc :: String -> [Integer]
calc = foldl f [] . words
    where
     f :: [Integer] -> String -> [Integer]
     f (x:y:zs) "+"    = (y + x):zs
     f (x:y:zs) "-"    = (y - x):zs
     f (x:y:zs) "*"    = (y * x):zs
     f (x:y:zs) "/"    = (y `div` x):zs
     f xs       y      = read y : xs

main = do
    print(calc "100 6 *")
    start <- getCPUTime
    replicateM_ 100000 $ do
        return (calc "100000000000000000 6 *")
    end <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10 ^ 8)
    putStrLn $ "Time taken: " ++ show diff ++ " milliseconds"
