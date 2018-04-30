# Corewar

**([Video example](https://youtu.be/Ty2P6FtErXk))**

What is Corewar?
* Corewar is a very peculiar game. It’s about bringing “players” together around a “virtual machine”, which will load some “champions” who will fight against one an- other with the support of “processes”, with the objective being for these champions to stay “alive”.
* The processes are executed sequentially within the same virtual machine and mem- ory space. They can therefore, among other things, write and rewrite on top of each others so to corrupt one another, force the others to execute instructions that can damage them, try to rewrite on the go the coding equivalent of a Côtes du Rhône 1982 (that is one delicious French wine!), etc...
* The game ends when all the processes are dead.  The winner is the last player reported to be “alive”.

## Getting Started

### Usage

Compiling asm files
```
Usage : ./asm file.s
```

Running the VM
```
Usage: ./corewar [-g | -f -dump N | -dump_all N -v N] <[-n N] champion2.cor> <...>
-dump N		: Dumps memory after N cycles then exits
-dump_all N	: Dumps memory and list processes after N cycles then exits
-g		: Graphic mode
-f		: Graphic mode windowed
-n N	: Set next champion's ID
-v N	: Verbose mode, N = verbosity level:
			- 1 : Show lives
			- 2 : Show cycles
			- 4 : Show deaths
			- 8 : Show PC movements
```

### Prerequisites

You will need SDL2 and SDL2\_TTF

Debian
```
sudo apt-get install sdl2 sdl2_ttf
```
OSX
```
brew install sdl2 sdl2_ttf
```

### Compiling

```
make all
```

## Authors

* **[Gregory Colletto](https://github.com/Gcol)**
* **[Sporer Valentin](https://github.com/demonoidv)**
* **[Gaudé Youva](https://github.com/Eviber)**
