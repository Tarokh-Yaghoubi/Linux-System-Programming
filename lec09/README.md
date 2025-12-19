
## What we learn here

### Opening and Closing Files
`fopen`, `fclose`

### Reading/Writing one character at a time
`fgetc`, `fputc`

### Reading/Writing line by line
`fgets`, `fputs`

### Reading/Writing using formatted I/O
`fscanf`, `fprintf`

### File position functions
`fseek`, `ftell`, `fgetpos`, `fsetpos`, `rewind`

<hr />

## CONTROL-SEQUENCE INTRODUCER

### what we can do using `\033[` in `printf()`
`\033[m`, `reset to default settings`
<br>
`\033[1m`, `Bold Characters`
<br>
`\033[2m`, `Underline Characters`
<br>
`\033[7m`, `Reverse Video`
<br>
`\033[30-39m`, `Foreground Colors`
<br>
`\033[40-49m`, `Background Colors`
<br>
`\033[0K`, `Erase from cursor to end of line`
<br>
`\033[1K`, `Erase from start of line to the cursor`
<br>
`\033[2K`, `Erase Current Line`
