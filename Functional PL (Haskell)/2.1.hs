type Person = String
type Relationship = (Person, Person)

getRelationships :: [Relationship] -> Person -> [Person]
getRelationships relationships person =
    let children = [child | (parent, child) <- relationships, parent == person]
    in children ++ concatMap (getRelationships relationships) children

test :: [Relationship] -> Person -> [Person] -> String
test relationships person ans = if getRelationships relationships person == ans then "OK" else "WA"

main = do
    -- let relationships = [("1", "2"), ("1", "3"), ("3", "4"), ("2", "5"), ("6", "7")]
    -- let ans = getRelationships relationships "1"
    -- print(ans)
    print(test [("1", "2"), ("1", "3"), ("3", "4"), ("2", "5"), ("6", "7")] "1" ["2","3","5","4"])
