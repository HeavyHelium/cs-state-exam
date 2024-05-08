import Data.List

main :: IO ()
main = do
  print "This is a test"
  print $ fibonacci 1
  print $ fibonacci 2
  print $ fibonacci 3
  print $ fibonacci 4
  print $ fibonacci 5
  print $ fibonacci 6
  print $ fibonacci 7
  print $ fibonacci 8
  print $ fibonacci 9
  print $ fibonacci 10
  print $ my_power 2 10
  print $ 2 ** 10
  print $ euclid_gcd 25 75
  print $ euclid_gcd 255 75
  print $ euclid_gcd 3 4
  print $ euclid_gcd 4 3
  print $ my_length [1, 2, 3, 4]
  print $ length [1, 2, 3]
  print $ range_ctor 1 5
  print $ range_ctor 5 1
  print $ elem 5 [1, 8, 3]
  print $ elem 5 [1, 8, 5, 3]
  print $ contains 5 [1, 8, 3]
  print $ contains 5 [1, 8, 5, 3]
  print $ remove_all 5 [4, 7, 3, 3]
  print $ remove_all 5 []
  print $ remove_all 5 [1, 5, 6, 3, 5, 9, 115]
  print $ square_them_all [1, 2, 3, 4]
  print $ remove_them_primes [1, 5, 6, 3, 5, 9, 115]
  print $ remove_them_primes_pt2 [1, 5, 6, 3, 5, 9, 115]
  print $ ((\x y -> x * y) 5) 6
  print $ div 10 5
  print $ 10 / 5
  print $ [4] ++ [1, 2, 3]
  print $ my_reverse [1, 2, 3]
  print $ my_reverse_linear_wrapper [4, 5, 6, 7]
  print $ sum ([1, 2, 3, 4])
  print $ my_sum ([1, 2, 3, 4])
  print $ take 1 [1, 2, 3, 4]
  print $ my_take 1 [1, 2, 3, 4]
  print $ drop 3 [1, 2, 3, 4, 5, 6, 7]
  print $ my_sort [5, 4, 8, 2, 9, 2, 1, 3, 33, 0, -6]
  print $ nub [1, 1, 2, 3, 1, 5, 5, 1, 2, 5]
  print $ my_nub [1, 1, 2, 3, 1, 5, 5, 1, 2, 5]
  print $ my_group "Mississippi"
  print $ (\x -> 5 * x) 5
  print $ (\x y z -> x + y + z) 4 5 6
  print $ my_zip [1, 2, 3, 4] [5, 6, 7, 8, 9, 10]

fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci (n - 1) + fibonacci (n - 2)

my_power :: Int -> Int -> Int
my_power _ 0 = 1
my_power x k = x * my_power x (k - 1)

euclid_gcd :: Int -> Int -> Int
euclid_gcd a b
  | a == 0 || b == 0 = a + b
  | b > a = euclid_gcd a (b `mod` a)
  | otherwise = euclid_gcd b (a `mod` b)

my_length :: [Int] -> Int
my_length [] = 0
my_length (_ : t) = 1 + my_length t

range_ctor :: Int -> Int -> [Int]
range_ctor x y = helper (min x y) (max x y)
  where
    helper :: Int -> Int -> [Int]
    helper x y
      | x == y = [x]
      | otherwise = (x : (helper (x + 1) y))

contains :: Int -> [Int] -> Bool
contains _ [] = False
contains x (h : t)
  | h == x = True
  | otherwise = contains x t

remove_all :: Int -> [Int] -> [Int]
remove_all _ [] = []
remove_all y (x : xs)
  | x == y = remove_all y xs
  | otherwise = x : (remove_all y xs)

square_them_all :: [Int] -> [Int]
square_them_all lst = map (\x -> x * x) lst

remove_them_primes :: [Int] -> [Int]
remove_them_primes lst = filter (\x -> not ((all (/= 0) (map (\y -> (x `mod` y)) [2 .. (x - 1)])))) lst

remove_them_primes_pt2 :: [Int] -> [Int]
remove_them_primes_pt2 lst = [x | x <- lst, not (all (/= 0) (map (\y -> (x `mod` y)) [2 .. (x - 1)]))]

-- my_flatten :: [a] -> [b]
-- my_flatten x

my_reverse :: [Int] -> [Int]
my_reverse [] = []
my_reverse (x : xs) = my_reverse xs ++ [x]

-- my_reverse_linear lst stack res
my_reverse_linear :: [Int] -> [Int] -> [Int]
my_reverse_linear [] stack = stack
my_reverse_linear (x : xs) stack = my_reverse_linear xs [x] ++ stack

my_reverse_linear_wrapper :: [Int] -> [Int]
my_reverse_linear_wrapper lst = my_reverse_linear lst []

my_sum :: [Int] -> Int
my_sum [] = 0
my_sum (x : xs) = (x + my_sum (xs))

my_take :: Int -> [Int] -> [Int]
my_take 0 _ = []
my_take num (x : xs) = x : my_take (num - 1) xs

-- drop -- drop first k elements in list

my_sort :: [Int] -> [Int]
my_sort [] = []
my_sort (x : xs) = (my_sort [y | y <- xs, y <= x]) ++ [x] ++ my_sort ([z | z <- xs, z > x])

my_nub :: [Int] -> [Int]
my_nub [] = []
my_nub lst = h : (helper t h)
  where
    (h : t) = my_sort lst
    helper :: [Int] -> Int -> [Int]
    helper [] prev = []
    helper (x : xs) prev
      | x == prev = helper xs prev
      | otherwise = x : (helper xs x)

my_group :: (Eq a) => [a] -> [[a]]
my_group [] = []
my_group (x : xs) = helper xs x [x]
  where
    helper :: (Eq a) => [a] -> a -> [a] -> [[a]]
    helper [] prev acc = [acc]
    helper (h : t) prev acc
      | h /= prev = [acc] ++ helper t h [h]
      | otherwise = helper t h (h : acc)

-- take all elements like prev from the rest

{-
Type defs
-}

type Point2D = (Int, Int)

{-

A function that needs to accept numbers in general, i.e. no
matter if they are sau Int or Double

helper :: (Num a, Num b) => a -> b

Тоест един вид аргуементите трябва да имат свойството, че са Num и
един вид го наследяват
-}

my_zip :: [a] -> [a] -> [(a, a)]
my_zip [] _ = []
my_zip _ [] = []
my_zip (x : xs) (y : ys) = (x, y) : (my_zip xs ys)

my_map :: (a -> b) -> [a] -> [b]
my_map _ [] = []
my_map f (x : xs) = (f x) : (my_map f xs)

my_filter :: (a -> Bool) -> [a] -> [a]
my_filter _ [] = []
my_filter p (x : xs)
  | (p x) = x : (my_filter p xs)
  | otherwise = my_filter p xs

my_foldr1 :: (a -> a -> a) -> [a] -> a
my_foldr1 f [x] = x
my_foldr1 f (x : xs) = f x (my_foldr1 f xs)

my_foldr :: (a -> a -> a) -> a -> [a] -> a
my_foldr f init [] = init
my_foldr f init (x : xs) = f x (my_foldr f init xs)