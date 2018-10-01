# Expert_System

An expert system has for a goal to emulate the descision making abilites of a human expert. In this project, we aimed to build
our own expert system that deducts queries given a set of rules and facts.

Using backwards chaining we find solutions by breaking down the rules for our goals into pieces and looking for the answer to thoses pieces,
then we bring it back together. This results in a comprehensive and efficent aproach to find all the desired values.

This was project was done with Conan Wu (conanwu777)

enjoy => ^-^

## Comiling and Running

Run `make` to compile. An executable will be created.

Run with:
```
./expert [file]
```

to see usage you can also run `./expert`

Feel free to make your own logical expressions cases based on the ones provided.

## Features

* Handles AND(+), OR(|), NOT(!) and XOR(^) operators in both assertion and conclusion

* Handles nested parenthesized expressions

* Handles biconditional rules IFF (<=>)

* Stores knowledge in a global graph of fact nodes linked by rules to minimize repeated computation

* Interactive fact validation to fiddle with the input while running (can update both facts and quires in runtime)

* Complete deduction reasoning outputted in one-liner formal logic notation directly from base facts

* 4 levels of truth in terms of confidence in deduction

  - surely TRUE (rely only on known fact without any further assumption)
  
  - TRUE assuming some unspecified (and un-deductible) variables being defaulted to false
  
  - FALSE assuming some unspecified (and un-deductible) variables being defaulted to false
  
  - surely FALSE (rely only on known fact without any further assumption)

## Screenshots

![alt text](/1.jpg)
