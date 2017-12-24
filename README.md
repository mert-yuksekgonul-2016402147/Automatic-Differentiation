## Automatic Differentiation

Please check out Project4.pdf for description of the project.

## Implementation Details 

I have implemented a computation graph for handling the forward pass and backward pass operations.

After calculating the topological order of the nodes, forward pass operation is used to calculate the output of the graph.

After that, I am using reverse-topological order to calculate partial derivatives by backward pass.

Classes of functions and variables are implemented in an object oriented fashion.

Please contact me for any additional questions.

mertyuksekgonul@gmail.com

## How to compile

In a terminal, call commands:
```
>cmake CMakeLists.txt

>make

OR

>cmake CMakeLists.txt && make

```
Make sure the executable is produced.

Then you can test the project with the command:
```
>./project4 functionDefinitionFile inputValuesFile outputValuesFile derivativeValuesFile
```
