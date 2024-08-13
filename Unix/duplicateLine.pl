# 6. Write a script using sed command to print duplicated lines in input.

#!/bin/bash

# Save input to temp file
input_file=$(mktemp)
cat > "$input_file"

# Print duplicated lines
sort "$input_file" | sed '$!N; s/^\(.*\)\n\1$/\1/; t; D'

# Remove temporary file
rm "$input_file"


## Execution =============
# ❯ ./file.sh <<EOF
# > apple
# > grape
# > banana
# > apple
# > orange
# > grape
# > EOF
