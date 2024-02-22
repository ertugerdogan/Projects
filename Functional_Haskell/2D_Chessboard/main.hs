import Chessboard

main :: IO ()
main = do  
    writeFile "output.txt" $ unlines
        [ "Current level: " ++ show(level)
        ,"count of total attacking positions: " ++ show (makeAttack attackBoard)
        , boardToChar attackBoard
        , "Team with the minimum value: " ++ show (getLowestScoringTeam valueBoard) ++ " " ++ show (boardValue valueBoard)
        , boardToChar valueBoard 
        ]