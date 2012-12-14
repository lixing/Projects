// Name: Lixing Lian
// E-mail: lixing@stanford.edu

This scanner is used to transform the source file from a stream of bits and bytes into a series of meaningful tokens, such as identifiers, operators and comments. And it also can report the various lexical errors.

Design decisions:

1. Operators: for single-character operators, it returns the ASCII value. For two-character operators, it returns the corresponding tokens from scanner.h file.

2. Constants: it recognizes int, double, bool and string constant. If the constant is hexadecimal, it will be converted to integer by using "strtol". If the string is not ended, it will report "UntermString"(in error.h file). And the corresponding field in yylval will be set. Finally it returns the corresponding token of constant.

3. Identifiers: the scanner should check if the length of the identifier is longer than "MaxIdentLen"(predefined in main.cc and the value is 31). If it is, it will use "LongIdentifier()" in error.h to report the error and returns the first 31 characters of the indentifier. But if it is not, it will return the token of identifier.

4. Comments: it recognizes two kinds of comments: one is single line comments, the other one is multiple lines comments. If the multiple lines comments have not ended, it will report error "UntermComment".

5. Error report: all the error handlings are mentioned above and be properly report by using the corresponding function in error.h file. "." is used to report the unrecognize character.

6. Counting lines and columns: "line" and "column" are gobal variables to count the line and column numbers. If the scanner can specify if it changes line, the line variable adds one.  These two variables are used in DoBeforeEachAction function. And "first_line", "first_column" and "last_column" of yylloc in scanner.h file record the line and column numbers.
