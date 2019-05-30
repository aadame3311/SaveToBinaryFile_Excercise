# SaveToBinaryFile_Excercise
From Advanced C++ course, I learned how to use binary files, structs, some pre-processor directives and lists to create a program that writes and reads objects to and from a binary file.

## Goal
My goal for this project was to learn how to properly utilize binary files to efficiently store data in a local system. I did this by implementing some of the things I learned from the first tutorials from UDemy Advanced C++ Tutorial. My goal was also to learn about how to use structs and pre-processor directives to remove byte padding in the following manner:
```cpp 
#pragma pack(push, 1) 
struct Car {
  char model[50];
  int year;
  int price;
}
#pragma pop
```

## What I Learned
I learned alot throughout this simple programming exercise. One thing I learned was how C++ allows you to use pre-processor directive 
```cpp
#define A 1
```
to make things simpler when it comes to replacing some function calls with a more readable and simpler name. I learned a bit about #pragma pre-processor directives and how they can help us make sure that the data we're storing is accurate and we can eliminate unecessary padding for our binary files. 

I also learned alot about binary files, I found it fun to play around with them and see what kind of data you could store. Before this tutorial, I had seen binary files before in my C# Unity projects and how to save data, but I think this helped me out more in understanding how they work and how to easily read from them. 

## Challenges
Some challenges I faced throughout this program were mainly how I wanted to structure my code. At first I thought it would be a good idea to modularize my open function calls. I realized, however, that I could not return a pointer to the fstream object I initiated in that function, as functions in C++ automatically delete any pointers after the function is done. A better solution could have been to pass the fstream object as reference, however, I opted out for simply opening each file in each respective function to avoid such problems.

