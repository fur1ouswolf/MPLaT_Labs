import Data.List (sort, group)

countNonWorkingDays :: [(Int, Int)] -> Int -> Int
countNonWorkingDays daysOff month = length $ filter (\(_, m) -> m == month) daysOff

findMonthWithMostDaysOff :: [(Int, Int)] -> Int
findMonthWithMostDaysOff daysOff = head $ maximumBy (\x y -> compare (length x) (length y)) groupedDaysOff
  where
    sortedDaysOff = sort daysOff
    groupedDaysOff = group $ map snd sortedDaysOff

daysOff = [(1, 1), (7, 1), (14, 2), (21, 2), (28, 2), (1, 3), (8, 3), (15, 3), (22, 3), (29, 3)]
monthWithMostDaysOff = findMonthWithMostDaysOff daysOff
numDaysOffInMonth = countNonWorkingDays daysOff monthWithMostDaysOff