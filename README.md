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