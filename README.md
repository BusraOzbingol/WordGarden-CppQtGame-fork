# OOP Group13

 # 🌸 WordGarden
 WordGarden is a vocabulary-based word guessing game developed in C++ using the Qt framework. The game combines learning and entertainment by encouraging players to improve their vocabulary through an interactive and visually engaging experience. It is designed for students, language learners, and word game enthusiasts.

## Group Members
- ASYA GÖSTERİR
- BERRAK KIRIK
- ELİF YILDIRIM
- EZGİ RANA YAVUZ
- HATİCE BÜŞRA ÖZBİNGÖL


## Project Description
This project was created in C++. This project is a word game featuring a graphical interface developed using the C++ programming language and the Qt framework. The primary goal of the project is to enhance users' vocabulary and provide an enjoyable learning experience. The target audience includes students, language learners, and word game enthusiasts.

The project aims to comprehensively implement Object-Oriented Programming (OOP) principles. Core classes will include Game (game management), Player (player information), and WordManager (word processing). Through composition, the Game class will contain Player and WordManager objects. Using inheritance, derived subclasses will be created from a base class for different game modes. The polymorphism feature will enable different behaviors through the same interface across various game modes, while exception handling will manage situations such as invalid word entries and file reading errors.

The graphical user interface will consist of buttons, a scoreboard, and colorful word tiles, offering a user-friendly and intuitive experience. The technical infrastructure will include word database management, and file I/O operations. Thanks to the project's extensible design, features such as new game modes and multi-language support can be added in the future.

---

## 🛠️ Technologies Used

* **C++**
* **Qt Framework (Qt Widgets)**
* **Object-Oriented Programming (OOP)**
* **File I/O**

---

## 🧱 Architecture Overview

The project follows a **Manager–Repository–Model** architecture.

### UML Diagram

<p align="center">
  <img src="Uml.png" alt="UML Diagram" width="800">
</p>


### 🔹 Core Model Classes

* **Word**
  Represents a word, its category, guessed letters, and guess state.

* **Player**
  Stores player information such as name, level and score.

* **Score**
  Manages scoring logic (+5 for correct guesses, −2 for incorrect guesses).

* **GameState**
  Represents the current game session, including:

  * Remaining guesses
  * Current word
  * Win/lose conditions

---

### 🔹 Manager Classes

* **WordManager**
  Handles word selection, guessing logic, and score updates.

* **GameStateManager**
  Controls game flow:

  * Starting new games
  * Processing guesses
  * Saving and loading game states

* **PlayerManager**
  Creates and retrieves player profiles.

* **HighScoreManager**
  Sorts and returns top-scoring players.

---

### 🔹 Repository Layer

* **IWordRepository**
  Interface for word data sources (polymorphism).

* **WordRepositoryFile**
  Loads and saves words from a file.

* **WordRepositoryMemory**
  Stores words temporarily in memory.

* **PlayerRepository**
  Manages all registered players.

* **GameStateRepository**
  Stores saved game sessions.

This design allows easy replacement or extension of data sources.

---

## 🖥️ User Interface

The graphical interface is implemented using **Qt Widgets** and includes:

* Login screen (new or existing player)
* Category selection
* Alphabet buttons for guessing letters
* Masked word display
* Scoreboard
* High score table

### 🌼 MainFlower Component

`MainFlower` is a custom Qt widget that visually represents player progress.
As the player makes incorrect guesses, the flower gradually loses its leaves, providing intuitive visual feedback.

---

## 🎮 Game Rules

* The player selects a **category**
* A random word is chosen from that category
* The player has **6 guessing attempts**
* Each correct letter:

  * +5 points
* Each incorrect letter:

  * −2 points
* The game ends when:

  * The word is fully guessed (win)
  * Attempts run out (lose)

---

## 💾 Save & Load System

* If the player exits before the game ends:

  * The current game state is saved
* When the application starts:

  * The last saved game is automatically loaded

---

## 🧠 Object-Oriented Programming Principles

WordGarden demonstrates strong use of OOP:

* **Composition**
  Managers contain and coordinate multiple objects.

* **Polymorphism**
  Achieved through repository interfaces (`IWordRepository`).

* **Modularity**
  Each class has a single responsibility.

* **Interface**
  The game uses well-defined interfaces such as `IWordRepository`, allowing different word sources (file-based or memory-based) to be swapped without changing game logic. This separation ensures modularity and flexibility.

* **Encapsulation**
  Each class hides its internal data and exposes only necessary methods. For example, `Word` keeps track of guessed letters privately, and `GameState` manages remaining guesses. Inheritance is intentionally minimized to avoid unnecessary complexity and maintain clear responsibilities.

* **High Cohesion**
  Classes have a single, focused responsibility.

  * `WordManager` handles word selection and guessing logic.
  * `GameStateManager` controls game flow.
  * `Player` and `Score` only manage player data and scoring.
    This makes each class easier to understand, test, and extend.

* **Consistency**
  Coding conventions, naming rules, and function structures are applied uniformly across all modules, ensuring readability and maintainability.

* **Clarity**
  Methods and class names clearly describe their purpose. For example, `makeGuess()` clearly updates the word state and score, while `getMaskedWord()` returns the word display with hidden letters, making the code largely self-explanatory.

* **Completeness**
  Each module fully meets its intended functionality:

  * Word management, guessing, and scoring are fully implemented.
  * Game state saving and loading works reliably.
  * The UI displays all necessary information (word, category, guesses, score) without missing features.
    Nothing is implemented unnecessarily, keeping the project clean and focused.


---

## 💻 Build & Run

To compile and run **WordGarden** using **Qt Creator**:

1. Open `WordGarden.pro` in Qt Creator.
2. Select a suitable kit (compiler + Qt version).
3. Click **Build** (Ctrl + B) to compile.
4. Click **Run** (Ctrl + R) to start the game.

> Make sure Qt and a compatible C++ compiler are installed on your system.

---
