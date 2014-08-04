-- Haskell version of file_entropy.
--
-- run via "runhaskell entropy.hs"

import qualified Data.ByteString as BS
import Data.List
import Data.Word
import System.Environment

-- Return a histogram as a list of bucket counts.
-- Note that we are ignoring the bucket values.
histogram :: BS.ByteString -> [Int]
histogram xs = [ BS.length l | l <- BS.group (BS.sort xs) ]

entropyHelper :: Int -> Double -> Int -> Double
entropyHelper total_count prev count = prev - (p_i * logBase 2.0 p_i)
    where p_i = (fromIntegral count) / (fromIntegral total_count)

calcEntropy :: [Int] -> Double
calcEntropy [] = 0.0
calcEntropy xs = foldl (entropyHelper total_count) 0.0 xs
    where total_count = sum xs


main = do
        args <- getArgs
        let f = head args
	d <- BS.readFile f
        let counts = histogram d
        let entropy = calcEntropy counts
        putStrLn (f ++ " " ++ (show entropy))
