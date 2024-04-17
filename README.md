# SysProgLabs
## Lab 1 "POSIX-compliant file system"

### Task: Create analogue of `find` func in POSIX-like systems

## Usage:

Possible flags:
* `-f` - show files
* `-d` - show directories
* `-l` - show links
* `-s` - sort according to `LC_COLLATE`
 
Parameters `l`, `d`, and `f` are automatically set if none of them was provided.

## Lab 2 "Сoncept of processes"
### Task: Create two programs: `parent` manages execution of multiple `child` instances.

- `CHILD_PATH` env var created before running `parent`, containing `child`'s directory.
- `parent` process:
 - Retrieves and prints sorted env vars.
 - Keyboard input loop:
   - `+`: Creates child via `fork`/`execve`, runs `child`. Name: `child_XX` (00-99).
   - `*`: Same, but gets `child` path from `main` args.
   - `&`: Same, but gets `child` path from `environ`.
   - Launches child with reduced env vars from file.
 - `q`: Exits.
- `child` process:
 - Prints name, PID, PPID.
 - Opens env var file, prints values.
 - Exits.

## Usage

1. Compile `parent` and `child`.
2. Set `CHILD_PATH`.
3. Run `parent` with env var file path.
4. Follow instructions for `child` management.


## Lab 3 "Process Interaction and Synchronization: Process Synchronization with Signals and Timer Signal Handling"

### Task: Manage child processes and control the output to stdout from them using the SIGUSR1 and SIGUSR2 signals.

## Parent Process Actions

- `+` - the parent process (P) spawns a child process (C_k) and reports it.
- `-` -  removes the last spawned C_k, reports it, and reports the number of remaining child processes.
- `l` -  lists all parent and child processes.
- `k` -  removes all C_k processes and reports it.
- `s` -  prohibits all C_k processes from outputting statistics (see below).
- `g` -  allows all C_k processes to output statistics.
- `snum` - prohibits the C_num process from outputting statistics.
- `gnum` allows the C_num process to output statistics.
- `pnum` prohibits all C_k processes from outputting and requests C_num to output its statistics.
After a specified time (e.g., 5 seconds), if the 'g' character is not entered, P allows all C_k processes to output statistics again.
- `q` removes all C_k processes, reports it, and terminates.

## Child Process Actions:

The child process sets an alarm (nanosleep(2)) in an outer loop and enters an infinite loop, where it fills a structure containing a pair of int variables with the values {0, 0} and {1, 1} in alternating mode. Upon receiving a signal from the alarm, it checks the contents of the structure, collects statistics, and repeats the outer loop body. After a specified number of outer loop iterations (e.g., 101), the child process, if allowed, outputs its PPID, PID, and four numbers – the count of different pairs registered at the time of receiving the alarm signal. The output is performed character-by-character (fputc(3)). C_k requests access to stdout from P and performs the output after confirmation. Upon completion of the output, C_k notifies P. The waiting time interval and the number of outer loop iterations should be chosen to ensure significant statistics.