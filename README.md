# Airgead Banking Investment Calculator

Ryan Hockenhull  
CS 210 Project Two: Airgead Banking

## Summarize the project and what problem it was solving.

Airgead Banking needed a way for users to compare saving a starting amount by itself with adding money each month. My solution was a console program written in C++. After collecting the user's amounts, interest percentage, and time period, it calculates both situations month by month. Each report lists the balance at the end of each year and the interest earned during that year. Seeing the results together makes the effect of continued contributions easier to understand.

## What did you do particularly well?

One part I am happy with is how the program handles entries that are almost valid. For example, entering 5abc does not get accepted as 5 because my input function checks the entire line. I also made sure the second report begins with the original investment instead of continuing from the first report's ending balance. The two reports use one method with different deposit amounts, which keeps their calculations consistent.

## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

I would put a practical limit on the investment period. Currently, the program checks whether the years fit within an integer, but that still allows someone to request far more output than they could reasonably use. A smaller limit would prevent unnecessarily long runs. Another change would be moving validation into the Investment constructor as well. Right now, the class depends on main.cpp to provide acceptable values. Checking them within the class would make it more reliable when reused elsewhere. I would also separate the calculated results from the printing code so I could check the numbers without reading console output.

## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

Keeping track of the monthly balance and the annual interest total took some thought. The balance needs to carry into the next year, while the earned-interest total needs to start over each year. I worked through this in my pseudocode and placed the yearly reset outside the monthly loop. I also followed the project sample's order of applying deposits before calculating interest. For future assignments, I plan to use my pseudocode alongside zyBooks, C++ documentation, and the Visual Studio debugger to work through calculations and follow changing variable values.

## What skills from this project will be particularly transferable to other projects or course work?

I can use the same approach of planning a calculation before deciding where each loop and variable belongs. It will also help to recognize when two features can share a method, as my two reports do. Working with the Investment class gave me practice passing information from the main program into an object. I expect to build on that when future assignments involve several classes working together.

## How did you make this program maintainable, readable, and adaptable?

Someone reviewing the project can find the class declarations in Investment.h, the report logic in Investment.cpp, and the input process in main.cpp. My comments explain decisions such as adding deposits before interest and rounding only the displayed amounts. I also gave the conversion values names, including MONTHS_PER_YEAR, so their purpose is clear. Since both report options call displayReport, changes to the monthly calculation would only need to be made in that method.
