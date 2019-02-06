This is my submission for Assignment 1. I went with option A, to create a templated vector class.
I used the non-templated double vector class that was provided as a start point.
To start with, I went and changed all of the functions and data members that were already in the class
to use templates rather than doubles. There were a few bugs which ocurred as a result of not having appropriately
changed the code in certain places to using templates, so I had to fix those. Once that was done, I went on
to define the various operators for the class. I started with the arithmetic operators. I encountered some problems with these,
mostly having to do with working with templates. For example, my dot product function was not producing the correct outputs
because I was trying to initialize a new variable of type T with the code "T result;" when what I needed was "T result = T();".
Once these were working, I defined the logical operators. I started with the less-than operator, and defined all of the remaining
operators in terms of that one. These operators did not give me too much trouble. Then I went on to writing a few different
versions of operator<<; one for ints, one for doubles, and one for strings. Once those were working, I dealt with the
requirements we were given for multiplication of vectors with strings. My solution was to write an operator* for strings, then
rewrite parts of my operator* to give the correct output in the case of strings. In order to do this, I changed from using *=
to * so that the operator* I had defined for strings would be used when dealing with strings.
