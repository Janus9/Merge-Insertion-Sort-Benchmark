Timing benchmark between Insertion Sort and Merge Sort

ARGUMENTS

    ./main.exe [#elements in array] [#times to run test] "--sorted" (OPTIONAL, makes array order sorted)
    
    argv[1] -> [INT] :: Number of elements in the array (n) 
    
    argv[2] -> [INT] :: Number of iteratios to run the test
    
    argv[3] -> ["--sorted"] :: (Optional) Makes array sorted upon generation
    
Example

    ./main.exe 1000 100 "--sorted"
    
    ./main.exe 10000 1000

Table made by ChatGPT 5.0: 
| Algorithm          | Best Case                 | Average Case   | Worst Case                | Space Complexity    | Stable? |
| ------------------ | ------------------------- | -------------- | ------------------------- | ------------------- | ------- |
| **Insertion Sort** | **O(n)** (already sorted) | **O(n²)**      | **O(n²)** (reverse order) | O(1)                | ✅ Yes  |
| **Merge Sort**     | **O(n log n)**            | **O(n log n)** | **O(n log n)**            | O(n) (extra arrays) | ✅ Yes  |

