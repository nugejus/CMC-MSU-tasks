import Prelude

famList::Integer->[(String,Integer)]->[String]
famList val list=map(\(l,n)->l)(filter (\(_,n)->n>=val)list)



foo::[(Integer,Integer)]->[Integer]
foo list=(map (\(s,t)->div s t) list)
lessVelocity :: [(Integer,Integer)]->Bool
lessVelocity list =foldr (&&) True (zipWith (\a b -> a >= b) (foo list) (tail (foo list)))

check::[Integer]->Bool
check list=foldr (&&) True (map(\x->x>3)list)
getGrantList::[(String,[Integer])]->[String]
getGrantList list = map(\(x,y)->x)(filter(\(_,n)->(check n))list)


main :: IO ()
main =  do
print(lessVelocity [(44,11),(25,10),(5,2)])
print(famList 3 [("Fild",2),("Li",5),("Brown",3),("Smith",0)])
print(getGrantList [("Green",[5,3,4]),("Fild",[5,5]),("Li",[4,5,4,5])])
