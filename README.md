# Minishell

## 📌 Project Overview
This project involves building a **mini Bash shell** from scratch in C with my partner [Yun-Chia](https://github.com/Yunchia-Hsu)
The shell mimics the behavior of a traditional Unix shell by parsing user input, executing commands, and managing processes.

The goal was to deepen understanding of:
- Process management in Unix/Linux
- System calls (`fork()`, `exec()`, `wait()`)
- Input parsing and command execution
- Process environment and state management
- Building an interactive CLI

---

## 🚀 Features
- Interactive shell prompt (`lobster-shell 🦞`)
- Execution of standard Unix commands (e.g., `ls`, `pwd`, `cat`)
- Support for **foreground processes**
- Basic **I/O redirection** (`>`, `<`, `>>`, `<<`)
- Handles quotes (`'`, `"`)
- **Piping** (`|`) between commands
- **Environmental Variables**
- **Built-in commands** that are implemented:
  - `cd` – change directory
  - `exit` – quit the shell
  - `pwd` - find place in the shell
  - `export` - set environment variables and list all exported variables
  - `env` - display environmental variable
  - `unset` - remove environmental variable
  - `echo` – prints aruguments (with option `-n`)
- **Signal Handling**
  - `ctrl-C` displays a new prompt on a new line
  - `ctrl-D` exits the shell
  - `ctrl-\` does nothing
- Error handling (invalid commands, missing files, etc.)

---

## ⚙️ Technologies Used
- **Language:** C  
- **System Calls:** `fork`, `execvp`, `wait`, `dup2`  
- **OS:** Linux (tested on Ubuntu 20.04)  

---

## 📂 Project Structure
```
minishell/
├── src/        # Source code
| ├── builtin/  # Built-in files
├── include/    # Header files
├── libft/      # Basic functions we have previously written that we were allowed to use
└── README.md
```
---

## 🛠️ Installation & Usage

```bash
git clone https://github.com/allihive/minishell.git
cd minishell
make
./minishell
```

---

## 🧠 Approach and Logic

**TEAMWORK**
- Divided work between 2 people
  - @Yunchia-Hsu handled parsing with tokens, piping, handling redirections
  - @allihive handled builtins, environmental variables, signals
- debugging, edge cases, memory leaks were discovered and handled by both

**LOGIC**
- Started with Readline to have the history and commandline working
- worked on creating each built-in commands as they were more independent from parsing and tokens
- create simple parsing logic and how tokens should be separated and expanded as we continued to add more features
- create parent and child processes and when to fork
  - Heredoc signals as well as implementation was used in the child process 
- implement signals at parent and child levels
- environmental variables are expanding with `'` and `"`
- CLI handling `'` and `"` with `echo`
- tested and retested different edge cases to make sure implementing one feature did not break or cause a leak in another

- ## Future improvements
- test even more edge cases involving `'` and `"`
- add more edge cases with pipes
- handle more memory leaks including still reachables

