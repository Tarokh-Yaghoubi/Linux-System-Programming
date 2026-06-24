#!/bin/bash

OUTPUT_FILE="programmer_status.dat"

yes "tarokh is a moderate programmer" | head -n 100 > "$OUTPUT_FILE"

echo "Successfully wrote the statement 100 times inside the file => $OUTPUT_FILE"


