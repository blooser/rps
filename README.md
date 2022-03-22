# Overview
We have a prepared a very simplified, text-based Rock, Paper, Scissors game which emulates an opponent by picking a random move on a separate thread.
The source code compiles into two binaries (separated as projects in a VS solution):
* `Backend` contains all logic for the game and is built into a static library.
* `RockPaperScissors` acts as the interface for the user and consists only of the `main` function. It is built into the final executable, linked against the `Backend` library.

# Your task
Unfortunately, the game has been created with a single opponent in mind. Your task is to:
1. extend the game functionality to include a variable number of opponents,
1. introduce any fixes to parts of code you find could be improved, anything goes. :)

Each opponent will take some time to think on their own thread.
Then, the moves will be compared after everyone (including the player) picked one.
Currently, the scoring is 2 points for a win, 1 for a tie, 0 points for a loss.
This can be summed up against every opponent for each player.

# Notes
* The standard is C++17.
* The build system doesn't need to be changed unless new directories/files are added, or you see potential improvements.
* For simplicity, the fact that user input can mix with program output can be ignored.
* **Any change matters and can be discussed, big or small.**
* When reviewing your work, we will pay attention to game logic, code cleanliness and adherence to language standards and best practices.

# Building
1. Create a virtual environment and activate it (Windows Git BASH example):\
  ```$ python -m venv venv && . ./venv/Scrpts/activate```

1. Install the Conan build tool:\
  ```$ pip install conan```

1. Make sure Conan has center.conan.io as a remote for packages:\
  ```$ conan remote add conancenter https://center.conan.io```

1. Install the project and dependencies (in case of issues, explicitly specify the remote):\
  ```$ conan install . [--remote conancenter]```

1. Build the project:\
  ```$ conan build .```

The command `conan build` will configure and build the project.
Configuration without building can be called with `conan build . -c` instead, which will create CMake files and a VS solution on Windows.
Later, compilation can be done though either `conan build .` at any moment or inside Visual Studio itself.
After compiling, the executable will be placed in the `bin` directory.
