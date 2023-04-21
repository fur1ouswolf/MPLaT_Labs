data MathTree =
	  None
	| Node (MathTree) [String] (MathTree)
	| Leaf [String]

union :: [String] -> [String]
union [] = []
union [x] = [x]
union (h:t) = if (head t == "*" || head t == "/") then union ([head(tail t) ++ " " ++ head t ++ " " ++ h] ++ (drop 2 t)) else ([h] ++ union t)

treeBuilder :: [String] -> MathTree
treeBuilder [] = None
treeBuilder [x] = Leaf [x]
treeBuilder (x:y:tail) = Node (treeBuilder (if (length tail) == 1 then words (head tail) else tail)) [y] (treeBuilder (words x))


makeRPN :: MathTree -> String
makeRPN None = ""
makeRPN (Leaf x) = head x
makeRPN (Node l x r) = makeRPN l ++ " " ++ makeRPN r ++ " " ++ head x

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
	let tree = union (words "22 * 3 - 23 * 2 - 1")
	let mt = treeBuilder(reverse tree)
	let rpn = makeRPN mt
	print(calc rpn)
