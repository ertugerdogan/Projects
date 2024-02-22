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


generateSierpinski :: Int -> Shape
generateSierpinski n = iterateSierpinski n [t1]
  where
    iterateSierpinski 0 shape = shape
    iterateSierpinski m shape =
      iterateSierpinski (m - 1) (concatMap generateTriangles shape)

    generateTriangles :: Triangle -> [Triangle]
    generateTriangles ((x1, y1, z1), (x2, y2, z2), (x3, y3, z3)) =
      let m1 = ((x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2) -- calculate the midpoint (x1, y1, z1) (x2, y2, z2)
          m2 = ((x3 + x2) / 2, (y3 + y2) / 2, (z3 + z2) / 2) -- calculate the midpoint (x2, y2, z2) (x3, y3, z3)
          m3 = ((x1 + x3) / 2, (y1 + y3) / 2, (z1 + z3) / 2) -- calculate the midpoint (x1, y1, z1) (x3, y3, z3)
          f1 = (x1, y1, z1)
          f2 = (x2, y2, z2)
          f3 = (x3, y3, z3)
      in
      [(f1, m1, m3)] ++ [(m1, f2, m2)] ++ [(m3, m2, f3)]



main :: IO ()
main = writeObjModel (generateSierpinski 3) "part1.stl"