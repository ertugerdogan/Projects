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


koch :: Int -> Shape
koch n = iterate_koch n [t1]
    where
        iterate_koch 0 shape = shape
        iterate_koch m shape =
            iterate_koch (m - 1) (concatMap generate_triangles shape)
        
        generate_triangles :: Triangle -> [Triangle]
        generate_triangles ((x1, y1, z1), (x2, y2, z2), (x3, y3, z3)) = 
            let p1 = (x1, y1, z1)                                          -- point 1
                p2 = (x2, y2, z2)                                          -- point 2
                p3 = (x3, y3, z3)                                          -- point 3
                -- m1 = ((x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2)         -- midpoint of point 1 and 2
                -- t1o1 = (x1 + x2 - x3, y1 + y2 - y3, z1 + z2 - z3)          -- outer point of point 3
                t1c1 = ((2*x1 + x2) / 3, (2*y1 + y2) / 3, (2*z1 + z2) / 3) -- point between point 1 and 2 (closer to 1)
                t1c2 = ((2*x2 + x1) / 3, (2*y2 + y1) / 3, (2*z2 + z1) / 3) -- point between point 1 and 2 (closer to 2)
                t1c3 = ((2*x1 + 2*x2 - x3) / 3, (2*y1 + 2*y2 - y3) / 3, (2*z1 + 2*z2 - z3) / 3) -- point between (midpoint of point 1 and 2) and  (outer point of point 3)
                
                t2c1 = ((2*x3 + x2) / 3, (2*y3 + y2) / 3, (2*z3 + z2) / 3) -- point between point 2 and 3 (closer to 3)
                t2c2 = ((2*x2 + x3) / 3, (2*y2 + y3) / 3, (2*z2 + z3) / 3) -- point between point 2 and 3 (closer to 2)
                t2c3 = ((2*x3 + 2*x2 - x1) / 3, (2*y3 + 2*y2 - y1) / 3, (2*z3 + 2*z2 - z1) / 3) -- point between (midpoint of point 2 and 3) and  (outer point of point 1)
                
                t3c1 = ((2*x3 + x1) / 3, (2*y3 + y1) / 3, (2*z3 + z1) / 3) -- point between point 1 and 3 (closer to 3)
                t3c2 = ((2*x1 + x3) / 3, (2*y1 + y3) / 3, (2*z1 + z3) / 3) -- point between point 1 and 3 (closer to 1)
                t3c3 = ((2*x3 + 2*x1 - x2) / 3, (2*y3 + 2*y1 - y2) / 3, (2*z3 + 2*z1 - z2) / 3) -- point between (midpoint of point 1 and 3) and  (outer point of point 2)
                
                t4c1 = (x1, y1, z1)                                        -- point 1
                t4c2 = ((2*x1 + x2) / 3, (2*y1 + y2) / 3, (2*z1 + z2) / 3) -- point between point 1 and 2 (closer to 1)
                t4c3 = ((2*x1 + x3) / 3, (2*y1 + y3) / 3, (2*z1 + z3) / 3) -- point between point 1 and 3 (closer to 1)

                t5c1 = (x2, y2, z2)                                          -- point 2
                t5c2 = ((2*x2 + x3) / 3, (2*y2 + y3) / 3, (2*z2 + z3) / 3) -- point between point 2 and 3 (closer to 2)
                t5c3 = ((2*x2 + x1) / 3, (2*y2 + y1) / 3, (2*z2 + z1) / 3) -- point between point 1 and 2 (closer to 2)

                t6c1 = (x3, y3, z3)                                          -- point 3
                t6c2 = ((2*x3 + x2) / 3, (2*y3 + y2) / 3, (2*z3 + z2) / 3) -- point between point 2 and 3 (closer to 3)
                t6c3 = ((2*x3 + x1) / 3, (2*y3 + y1) / 3, (2*z3 + z1) / 3) -- point between point 1 and 3 (closer to 3)
            in
            [(t1c1, t1c2, t1c3)] ++ [(t2c1, t2c2, t2c3)] ++ [(t3c1, t3c2, t3c3)] ++ [(t4c1, t4c2, t4c3)] ++ [(t5c1, t5c2, t5c3)] ++ [(t6c1, t6c2, t6c3)] ++ [(p1, p2, p3)]

-- generateSierpinski :: Int -> Shape
-- generateSierpinski n = iterateSierpinski n [t1]
--   where
--     iterateSierpinski 0 shape = shape
--     iterateSierpinski m shape =
--       iterateSierpinski (m - 1) (concatMap generateTriangles shape)

--     generateTriangles :: Triangle -> [Triangle]
--     generateTriangles ((x1, y1, z1), (x2, y2, z2), (x3, y3, z3)) =
--       let p1 = (x1, y1, z1)                                  -- point 1
--           p2 = (x2, y2, z2)                                  -- point 2
--           p3 = (x3, y3, z3)                                  -- point 3
--           m1 = ((x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2) -- calculate the midpoint of point 1 and 2
--           m2 = ((x3 + x2) / 2, (y3 + y2) / 2, (z3 + z2) / 2) -- calculate the midpoint of point 2 and 3
--           m3 = ((x1 + x3) / 2, (y1 + y3) / 2, (z1 + z3) / 2) -- calculate the midpoint of point 1 and 3
--       in
--       [(p1, m1, m3)] ++ [(m1, p2, m2)] ++ [(m3, m2, p3)]


main :: IO ()
main = writeObjModel (koch 3) "part2.stl"