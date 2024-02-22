type Point = (Float,Float, Float)
type Triangle = (Point, Point, Point)
type Shape = [Triangle]

t1 :: Triangle
t1 = ((0,0,10),(0,-5,0),(0,5,0))

createTriangleDef :: Triangle -> String
createTriangleDef ((x1,y1,z1),(x2,y2,z2),(x3,y3,z3)) = "  facet\n" ++
                                                       "    outer loop\n" ++
                                                       "      vertex " ++ (show x1) ++ " " ++ (show y1) ++ " " ++ (show z1) ++ "\n" ++
                                                       "      vertex " ++ (show x2) ++ " " ++ (show y2) ++ " " ++ (show z2) ++ "\n" ++
                                                       "      vertex " ++ (show x3) ++ " " ++ (show y3) ++ " " ++ (show z3) ++ "\n" ++
                                                       "    endloop\n" ++
                                                       "  endfacet\n"                            


createObjectModelString :: Shape -> String 
createObjectModelString n = "solid Object01\n" ++ concat [createTriangleDef y | y<-n] ++ "endsolid Object01"

writeObjModel :: Shape -> String -> IO ()
writeObjModel x filename = do writeFile filename (createObjectModelString x)

createcube :: (Point, Float) -> Shape
createcube ((x, y, z), l) = 
    let 
        t1c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t1c2 = (x + (l / 2), y - (l / 2), z - (l / 2))
        t1c3 = (x + (l / 2), y + (l / 2), z - (l / 2))

        t2c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t2c2 = (x - (l / 2), y + (l / 2), z - (l / 2))
        t2c3 = (x + (l / 2), y + (l / 2), z - (l / 2))

        t3c1 = (x - (l / 2), y - (l / 2), z + (l / 2))
        t3c2 = (x + (l / 2), y - (l / 2), z + (l / 2))
        t3c3 = (x + (l / 2), y + (l / 2), z + (l / 2))

        t4c1 = (x - (l / 2), y - (l / 2), z + (l / 2))
        t4c2 = (x - (l / 2), y + (l / 2), z + (l / 2))
        t4c3 = (x + (l / 2), y + (l / 2), z + (l / 2))

        t5c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t5c2 = (x - (l / 2), y + (l / 2), z - (l / 2))
        t5c3 = (x - (l / 2), y + (l / 2), z + (l / 2))

        t6c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t6c2 = (x - (l / 2), y - (l / 2), z + (l / 2))
        t6c3 = (x - (l / 2), y + (l / 2), z + (l / 2))

        t7c1 = (x + (l / 2), y - (l / 2), z - (l / 2))
        t7c2 = (x + (l / 2), y + (l / 2), z - (l / 2))
        t7c3 = (x + (l / 2), y + (l / 2), z + (l / 2))

        t8c1 = (x + (l / 2), y - (l / 2), z - (l / 2))
        t8c2 = (x + (l / 2), y - (l / 2), z + (l / 2))
        t8c3 = (x + (l / 2), y + (l / 2), z + (l / 2))

        t9c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t9c2 = (x - (l / 2), y - (l / 2), z + (l / 2))
        t9c3 = (x + (l / 2), y - (l / 2), z + (l / 2))

        t10c1 = (x - (l / 2), y - (l / 2), z - (l / 2))
        t10c2 = (x + (l / 2), y - (l / 2), z - (l / 2))
        t10c3 = (x + (l / 2), y - (l / 2), z + (l / 2))

        t11c1 = (x - (l / 2), y + (l / 2), z - (l / 2))
        t11c2 = (x - (l / 2), y + (l / 2), z + (l / 2))
        t11c3 = (x + (l / 2), y + (l / 2), z + (l / 2))

        t12c1 = (x - (l / 2), y + (l / 2), z - (l / 2))
        t12c2 = (x + (l / 2), y + (l / 2), z - (l / 2))
        t12c3 = (x + (l / 2), y + (l / 2), z + (l / 2))
    in
    [(t1c1, t1c2, t1c3)] ++ [(t2c1, t2c2, t2c3)] ++ [(t3c1, t3c2, t3c3)] ++ [(t4c1, t4c2, t4c3)] ++ 
    [(t5c1, t5c2, t5c3)] ++ [(t6c1, t6c2, t6c3)] ++ [(t7c1, t7c2, t7c3)] ++ [(t8c1, t8c2, t8c3)] ++
    [(t9c1, t9c2, t9c3)] ++ [(t10c1, t10c2, t10c3)] ++ [(t11c1, t11c2, t11c3)] ++ [(t12c1, t12c2, t12c3)]

cubeFractal :: Int -> Shape
cubeFractal n = concatMap createcube (iteratecube n [((0,0,0),1)])
    where
        iteratecube 0 coords = coords
        iteratecube m coords = 
            iteratecube (m - 1) (concatMap generateCoords coords)
        generateCoords :: (Point, Float) -> [(Point, Float)]
        generateCoords ((x, y, z), l) = 
            let d = 3 * l / 4
                c1 = ((x, y, z + d), l / 2)
                c2 = ((x, y, z - d), l / 2)
                c3 = ((x, y + d, z), l / 2)
                c4 = ((x, y - d, z), l / 2)
                c5 = ((x + d, y, z), l / 2)
                c6 = ((x - d, y, z), l / 2)
                oc = ((x, y, z), l)
            in
            [oc] ++ [c1] ++ [c2] ++ [c3] ++ [c4] ++ [c5] ++ [c6]


main :: IO ()
main = writeObjModel (cubeFractal 3) "part4.stl"