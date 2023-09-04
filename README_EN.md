# Text Processing Project

## What the Main Project Does:
- Reads text (in my case, for example, it's the text of Eugene Onegin)
- Splits it into lines
- Sorts the lines in alphabetical order
- Sorts lines from the end (resulting in rap), as it turns out that adjacent lines have the same ending

## Project Features

- Use of `string_view` to accelerate the program and enhance the speed of the text-splitting operation. Unlike `std::string`, `string_view` provides an immutable view of a character sequence. This avoids unnecessary copies and memory usage when processing strings, making the code more efficient.
- Unicode support using `std::wstring` and `std::wcout` for correct text processing across different languages and platforms.
- Supports all platforms, uses native `Win API` functions on Windows.
- Custom sorting function with known asymptotics.

# `QuickSortUnitTest`

`QuickSortUnitTest` is a graphical subproject for tuning the coefficients of your quick sort function using the Monte Carlo method and gradient descent. The sorting function is of the form nlogn and is compared to the function kx + b, implemented based on the high-level library [`TESTWIN32_GRAPHICAPP`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP).
It is used for tuning the coefficients of the sorting function and plotting sorting efficiency graphs.

<img src="https://user-images.githubusercontent.com/64206443/235460597-0fbdd4c4-49d0-4fa8-a81e-cc3396697266.png" width="400">

--------------------------
# Instructions for Running `QuickSortUnitTest` on Windows
- Requirements: Windows 7 is required for the program to function fully.
- Download the application from the following link: https://github.com/quqveik1/StringSort/releases/latest
- Run the downloaded .exe file, ignore antivirus warnings stating that the program is dangerous.
In this window, you should click on this button.

<img src="https://user-images.githubusercontent.com/64206443/182945554-ed4d18c6-a25d-4d0d-a331-e268643b3031.png" width="400">

- The program installer will open; follow its instructions.
