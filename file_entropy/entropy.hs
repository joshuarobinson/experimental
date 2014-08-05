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

-- entropyHelper
-- Designed to be use to accumulate entropy value per histogram bucket. I.e., specifically for
-- foldl usage.
entropyHelper :: Int -> Double -> Int -> Double
entropyHelper total_count prev count = prev - (p_i * logBase 2.0 p_i)
    where p_i = (fromIntegral count) / (fromIntegral total_count)


-- Calculate the entropy of a distribution of counts.
calcEntropy :: [Int] -> Double
calcEntropy [] = 0.0
calcEntropy xs = foldl (entropyHelper total_count) 0.0 xs
    where total_count = sum xs

-- doEntropy composes the histogram creation with the entropy calculation and formats a string for
-- output.
doEntropy :: String -> BS.ByteString -> String
doEntropy f b = f ++ " " ++ show (calcEntropy $ histogram b )


-- doEntropy within the IO monad.
doEntropyIO :: String -> IO ()
doEntropyIO f = do
    d <- BS.readFile f
    putStrLn (doEntropy f d)


-- Do IO and calculate entropy for each item in the command-line args list.
main = do
        args <- getArgs
        mapM_ doEntropyIO args
