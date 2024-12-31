
# Sir# Programming Language

Welcome to Sir#, a custom programming language! This project was developed by **Ramy Rashad**, **Ahmed El Gendy**, and **Zyad Hany**. Sir# offers an easy-to-use syntax inspired by Python, focusing on handling basic operations, variables, conditions, and loops, with added support for large integer calculations.

## Features

- **Variable Declaration & Assignment:** Syntax similar to Python. Declare and assign variables easily.
  
  Example:
  ```
  x = 10
  y = "Hello, World"
  ```

- **Conditional Statements:** We support `if` and `else` conditions, each block ending with the `end` keyword.
  
  Example:
  ```
  if x > 5
      print x
  else
      print "x is less than or equal to 5"
  end
  ```

- **Loops:** We currently support `while` loops with a similar structure to Python but with the `end` keyword to close the loop.
  
  Example:
  ```
  x = 0
  while x < 5
      print x
      x = x + 1
  end
  ```

- **Print Function:** Use the `print` keyword to output variables, strings, or operations.
  
  Example:
  ```
  print "The result is"
  ```

- **Big Integer Support:** Sir# supports operations on very large numbers without size restriction, treating numbers as strings internally.

## Syntax

- **Variables:** Declared and assigned using `=`, similar to Python.
  
  Example:
  ```
  variable_name = value
  ```

- **If Statements:** Use `if` and `else` for conditional logic. Blocks must end with `end`.
  
  Example:
  ```
  if condition
      # code block
  else
      # code block
  end
  ```

- **While Loops:** Use `while` for loops. Use `end` to close the loop.
  
  Example:
  ```
  while condition
      # code block
  end
  ```

- **Printing:** Use `print` to output variables, strings, or operations.
  
  Example:
  ```
  print "Hello, World"
  ```

## Handling Big Integers

Sir# can handle large integer values by treating numbers as strings internally and applying operations without size constraints.

## Basic Editor

We have developed a basic editor for Sir#. Simply run the provided Python file, write your code, and execute it in the editor.

## Getting Started

1. Clone the repository.
2. Install dependencies (if required).
3. Run the editor to start writing and running Sir# code.

## Contributors

- **Ramy Rashad**
- **Ahmed El Gendy**
- **Zyad Hany**

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
