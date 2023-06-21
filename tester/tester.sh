#!/bin/bash

# Input file containing tests
TESTS_FILE="t.txt"
RES_FILE="res.txt"

# Loop through each test in the input file
while IFS= read -r test; do
  # Execute the test
  bash_result=$(eval "$test")
  echo "$bash_result" >> "$RES_FILE"
done < "$TESTS_FILE"

#!/bin/bash

# Path to your C program executable
# PROGRAM="./app"

# # Input file containing tests
# TESTS_FILE="t.txt"

# # Output file to store the results
# RESULTS_FILE="results.txt"

# # Remove the results file if it already exists
# rm -f "$RESULTS_FILE"

# # Loop through each test in the input file
# while IFS= read -r test; do
#   # Run the C program and pass the test as an argument
#   result=$("$PROGRAM" "$test")
  
#   # Append the result to the output file
#   echo "$result" >> "$RESULTS_FILE"
# done < "$TESTS_FILE"