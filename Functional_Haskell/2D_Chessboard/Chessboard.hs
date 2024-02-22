module Chessboard
  ( Piece(..)
  , Team(..)
  , Position
  , Chessboard
  , initialChessboard
  , moveRook
  , moveBishop
  , moveKnight
  , moveQueen
  , isSameTeam
  , isDifferentTeam
  , attack
  , attackCount
  , makeAttack
  , pieceValue
  , getTeamTotalPoints
  , getLowestScoringTeam
  , boardValue
  , deletePiece
  , horizontalCrossover
  , verticalCrossover
  , calculateBranch
  , findBestBoardAttackCount
  , findBestPiceValue
  , boardToChar
  , listToChar
  , attackBoard
  , valueBoard
  , processBoards
  , recurseBoard
  , level
  ) where

import Data.List (minimumBy, intersperse, maximumBy)
import Data.Function (on)

data Piece = Bishop | Knight | Rook | Queen | Pawn   
    deriving (Eq, Show)
    
data Team = Red | Green | Blue | Pink | White   
    deriving (Eq, Show)

type Position = ((Piece, Team), (Integer, Integer))
type Chessboard = [Position]

level :: Integer ------ This variable will be changed to change the level
level = 1

 -- Team Green       
k_g_1 :: Position
k_g_1 =  ((Rook, Green), (6,6))

k_g_2 :: Position
k_g_2 = ((Rook, Green), (5,2))

 -- Team Blue
b_q_1 :: Position
b_q_1 = ((Queen, Blue), (3,4))

b_k_1 :: Position
b_k_1 = ((Knight, Blue), (7,3))

 -- Team Red
q_r_1 :: Position
q_r_1 = ((Queen, Red), (3,2))

 -- Team White
b_w_1 :: Position
b_w_1 = ((Bishop, White), (5,1))

b_w_2 :: Position
b_w_2 = ((Bishop, White), (6,2))

b_w_3 :: Position
b_w_3 = ((Bishop, White), (5,8))

k_w_1 :: Position
k_w_1 = ((Knight, White), (4,6))

 -- Team Pink       
k_p_1 :: Position
k_p_1 = ((Knight, Pink), (6,8))

k_p_2 :: Position
k_p_2 = ((Knight, Pink), (7,7))

q_p_1 :: Position
q_p_1 = ((Queen, Pink), (3,7))

--Initial Chessboard
initialChessboard :: Chessboard
initialChessboard = [k_g_1, k_g_2, b_q_1, b_k_1, b_w_1, b_w_2, b_w_3, q_r_1, k_w_1, k_p_1, k_p_2, q_p_1]

----------------------------------------------------------------------
------------------------------ ROOK ----------------------------------
----------------------------------------------------------------------

--ROOK has 4 different moves
moveRook :: Integer -> Integer -> Team -> Chessboard -> [(Integer, Integer)]
moveRook x y t board = moveLeft (x - 1) y t 8 board ++ moveRight (x + 1) y t 8 board ++ moveUp x (y + 1) t 8 board ++ moveDown x (y - 1) t 8 board

moveLeft :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveLeft x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveLeft (x - 1) y team (count - 1) board

moveRight :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveRight x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveRight (x + 1) y team (count - 1) board

moveUp :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveUp x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveUp x (y + 1) team (count - 1) board

moveDown :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveDown x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveDown x (y - 1) team (count - 1) board

----------------------------------------------------------------------
---------------------------- BISHOP ----------------------------------
----------------------------------------------------------------------

--Bishop has 4 different moves
moveBishop :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveBishop x y t count board =  moveLeftUp (x - 1) (y + 1) t count board ++ 
                                moveRightUp (x + 1) (y + 1) t count board ++ 
                                moveRightDown (x + 1) (y - 1) t count board ++ 
                                moveLeftDown (x - 1) (y - 1) t count board

moveLeftUp :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveLeftUp x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveLeftUp (x - 1) (y + 1) team (count - 1) board

moveRightUp :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveRightUp x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveRightUp (x + 1) (y + 1) team (count - 1) board

moveLeftDown :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveLeftDown x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveLeftDown (x - 1) (y - 1) team (count - 1) board

moveRightDown :: Integer -> Integer -> Team -> Integer -> Chessboard -> [(Integer, Integer)]
moveRightDown x y team count board
    | count == 0 = []
    | isSameTeam x y team board = []
    | isDifferentTeam x y team board = [(x, y)]
    | otherwise = moveRightDown (x + 1) (y - 1) team (count - 1) board

----------------------------------------------------------------------
---------------------------- KNIGHT ----------------------------------
----------------------------------------------------------------------

--Knight has 8 different moves
moveKnight :: Integer -> Integer -> Team -> Chessboard -> [(Integer, Integer)]
moveKnight x y team = concatMap (\((_, t), (px, py)) -> ([(px, py) | isThreatened px py t]))
    where
        isThreatened px py otherTeam = any (\(dx, dy) -> px == x + dx && py == y + dy) knightMoves && otherTeam /= team
        knightMoves = [(2, 1), (-2, 1), (2, -1), (-2, -1), (1, 2), (-1, 2), (1, -2), (-1, -2)]

----------------------------------------------------------------------
----------------------------- QUENN ----------------------------------
----------------------------------------------------------------------

--Queen has 8 different moves and Queen works like rook+bishop
moveQueen ::Integer -> Integer -> Team -> Chessboard -> [(Integer,Integer)]
moveQueen x y t board = moveBishop x y t 8 board ++ moveRook x y t board

----------------------------------------------------------------------
----------------------------- PAWN -----------------------------------
----------------------------------------------------------------------

--Pawn has 4 different moves ( In our problem, pawn is assumed to treat all pieces at its four corners.) basically bishop with range one
movePawn ::Integer -> Integer -> Team -> Chessboard -> [(Integer,Integer)]
movePawn x y t = moveBishop x y t 1

----------------------------------------------------------------------
--check same team
isSameTeam :: Integer -> Integer -> Team -> Chessboard -> Bool
isSameTeam x y team = any (\((_, t), (px, py)) -> px == x && py == y && t == team)

--check different team
isDifferentTeam :: Integer -> Integer -> Team -> Chessboard -> Bool
isDifferentTeam x y team = any (\((_, t), (px, py)) -> px == x && py == y && t /= team)

--general attack function for all types of pieces
attack :: Position -> Chessboard -> [(Integer,Integer)]
attack ((Knight, t), (x, y)) = moveKnight x y t
attack ((Rook, t), (x, y)) = moveRook x y t
attack ((Bishop, t), (x,y)) = moveBishop x y t 8
attack ((Queen, t), (x,y)) = moveQueen x y t
attack ((Pawn, t), (x,y)) = moveBishop x y t 1

--attack count function
attackCount:: [(Integer, Integer)] -> Integer
attackCount pairs = toInteger $ length pairs

--count of all possible attacks in the board
makeAttack :: Chessboard -> Integer
makeAttack board = attackCount (concatMap (`attack` board) board)

-------------------------------------------------------------------------------
--values of every pieces in the board
pieceValue :: Piece -> Float
pieceValue Pawn   = 1
pieceValue Bishop = 3.25
pieceValue Knight = 3.25
pieceValue Rook   = 5
pieceValue Queen  = 10


-- Function to calculate the total points of a specific team
getTeamTotalPoints :: Chessboard -> Team -> Float
getTeamTotalPoints chessboard team = sum [pieceValue piece | ((piece, team'), _) <- chessboard, team' == team]


getLowestScoringTeam :: Chessboard -> Team
getLowestScoringTeam chessboard = minimumBy (compare `on` getTeamTotalPoints chessboard) validTeams
  where
    validTeams = filter (\team -> getTeamTotalPoints chessboard team /= 0) [Red, Green, Blue, Pink, White]


--Function to get the total points of the lowest scoring team
boardValue :: Chessboard -> Float
boardValue chessboard = getTeamTotalPoints chessboard $ getLowestScoringTeam chessboard


-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

-- the new chessboard will be returned without selected position 
deletePiece :: Position -> Chessboard -> Chessboard
deletePiece (_, pos) = filter (\(_, p) -> p /= pos)

horizontalCrossover :: Integer -> Chessboard -> Chessboard
horizontalCrossover num_ = map (\((piece, team), (x, y)) -> ((piece, team), (x, newY num_ y)))
  where
    newY number_val old_val
      | number_val >= old_val =  8 + old_val - number_val -- If the number is less than where we cut it, it goes up and then decreases as much as it is cut.
      | otherwise = old_val - number_val -- If the number is greater than where it is cut off, it only decreases by the place where it is cut off.


verticalCrossover :: Integer -> Chessboard -> Chessboard
verticalCrossover num_ = map (\((piece, team), (x, y)) -> ((piece, team), (newX num_ x, y)))
  where
    newX number_val old_val
      | number_val >= old_val = 8 + old_val - number_val -- If the number is less than where we cut, it moves further to the right
      | otherwise = old_val - number_val -- If the number is greater than where it is cut, it moves to the left only as much as where it is cut.

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
---It calculates the all branches in one level (26)------
calculateBranch :: Chessboard -> [Chessboard]
calculateBranch board = 
    let
        nums = [1,2,3,4,5,6,7] --- number of all possible horizontal and vertical branches
        vertical = map (`verticalCrossover` board) nums
        horizontal = map (`horizontalCrossover` board) nums
        delete = map (`deletePiece` board) board   -- branches for delete
    in
        vertical ++ horizontal ++ delete --- it will return list of chessboard so i add them together

findBestBoardAttackCount :: [Chessboard] -> Chessboard 
findBestBoardAttackCount = minimumBy (compare `on` makeAttack) ----Objective 1

findBestPiceValue :: [Chessboard] -> Chessboard
findBestPiceValue = maximumBy (compare `on` boardValue) ----- Ojective 2

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--print
boardToChar :: Chessboard -> String
boardToChar board = unlines [show piece ++ " " ++ show team ++ " " ++ show x ++ " " ++ show y | ((piece, team), (x, y)) <- board]

listToChar :: (Integer, Integer) -> String
listToChar (x,y) = show x ++ ", " ++ show y

--calculate best board attack count  
attackBoard :: Chessboard
attackBoard = findBestBoardAttackCount (recurseBoard (level) [initialChessboard])

--calculate the value of the team with the minimum value 
valueBoard :: Chessboard
valueBoard = findBestPiceValue (recurseBoard (level) [initialChessboard])

processBoards :: [Chessboard] -> String
processBoards boards = unwords
  ([show (makeAttack board)
      ++
        show (getLowestScoringTeam board)
          ++ show (boardValue board) ++ boardToChar board |
      board <- boards])

--A function designed for the level logic to work recursively.
recurseBoard :: Integer -> [Chessboard] -> [Chessboard]
recurseBoard 0 boards = boards
recurseBoard n boards = recurseBoard (n - 1) (concatMap calculateBranch boards)