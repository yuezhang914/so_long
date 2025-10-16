so_long — Project Overview


# What this project is:

so_long is a simple 2D collect-and-exit game. The player moves on a map represented by characters, collects all C (collectibles), then reaches the exit E to complete the level. Maps are described by .ber files (rectangular tiles, walls marked as 1, etc.). The game uses the X11 MinilibX (mini graphics library) for graphics, keyboard events, and rendering.

This repository is my implementation from scratch following the project specification. It includes the mandatory part and bonus extensions (enemies, animations, HUD, etc.).


# What I did:

I implemented the full game pipeline: map loading and validation, rendering, player input handling, level reachability checks (pathfinding), and the bonus features (enemies, animations, HUD). Specifically I:

Designed and implemented map loading and strict validation logic (rectangular shape, surrounded by walls, and the correct number/placement rules for P/E/C).

Implemented a flood-fill based reachability check to ensure a map is completable before starting the game (all collectibles and the exit are reachable from the player).

Used MinilibX to load XPM sprites and implemented tile-based rendering (floor, wall, player, collectible, exit, enemy, etc.).

Handled keyboard input (supports WASD and arrow keys), counted moves and printed Moves to the console; implemented ESC to quit.

Implemented game mechanics: collect collectibles, lose when hit by an enemy, win when reaching the exit after collecting all C, move counting and HUD display (in bonus mode).

Bonus: implemented enemies (simple NPCs) with collision detection and path/movement logic; player loses if collided with an enemy; added frame animations for tiles and entities; implemented a HUD showing remaining collectibles / moves, etc.

Built a Makefile supporting both make (default) and make bonus, and integrated building of my libft.

Wrote several utility helpers and error-handling routines.



# Completed features:

Mandatory:

Map loading and parsing (.ber files).

Map validation: rectangular shape; surrounded by walls; contains P (player), E (exit), and at least one C (collectible).

Reachability check (flood-fill / pathfinding): ensures from P you can reach every C and finally E.

Rendering and sprite drawing using XPM resources.

Player movement (WASD + ↑ ↓ ← →).

Move counter output to console: Moves: n.

Win/lose detection and proper exit handling.

Makefile and integration with libft.

Bonus:

Enemies (NPC) and collision detection: enemies move on the map and cause a loss if they meet the player.

Enemy pathing / simple AI (map-based fill/search or step strategy).

Frame animations (player / enemy / collectible sprite switching).

HUD rendering: visual display of collected / total collectibles, move count, etc.

Improved input handling and window redraw logic.

A suite of test maps (test-maps/) covering many valid and invalid cases.




# Project structure (modules):

includes/ — public headers, defines data structures (t_game, t_bonus, t_hookctx, etc.) and function prototypes.

src/ — core implementation for the mandatory part (map loading, validation, rendering, input, main loop, win/lose logic).

bonus/ — bonus features (animations, enemies, HUD, more advanced redraw logic).

assets/ — XPM sprite resources, organized by tiles / entities.

maps/ and test-maps/ — hand-crafted maps and a large set of test cases (valid / edge / broken maps) for validating validation and pathfinding logic.

libft/ — the custom libc-style helper library used by the project (strings, IO, ft_printf, etc.).

minilibx-linux/ — MinilibX library source (provided by 42).



# Environment:

Linux with X11 support, or WSL2 + X server (MinilibX must be able to run).

Basic build tools: gcc (or a compatible C compiler) and make.

X11 development headers may be required (if MinilibX is not preinstalled): libx11-dev, libxext-dev.

On Debian/Ubuntu you may need:
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev


# Build:

Build the mandatory version
make
Build the bonus version
make bonus

After successful build you will get executables:

./so_long — mandatory target
./so_long_bonus — includes bonus features (enemies / HUD / animation)

Both programs accept a .ber map file as the argument. If the map is invalid the program prints an error message and exits.


# Controls:

Move: W / A / S / D or Up / Left / Down / Right (arrow keys)

Exit: Esc

The game prints Moves: N in the terminal for checking the move count. In bonus mode a HUD also shows information inside the game window (e.g. remaining collectibles and moves).

----------------中文版------------------

这个项目是什么：

so_long 是一个简单的 2D 拾取类小游戏：玩家在一个由字符组成的地图上移动，收集所有 C（collectible），然后到达出口 E 完成关卡。地图使用 .ber 文件描述（矩形格子、边界为墙 1 等）。游戏基于 X11 的 MinilibX（mini graphics library）实现图形、键盘事件与渲染。

本仓库是我基于题目要求从零实现的版本，包含必做部分和bonus扩展（敌人、动画、HUD 等）。



我做了什么：

我实现了整个游戏从 Map 加载与验证、到渲染、玩家输入处理、关卡可达性检测（路径检查）、以及 bonus 的敌人、动画、HUD 等功能。具体工作包括：

设计并实现了地图读取与严格校验逻辑（矩形、四周墙、必须存在且仅存在合理数量的 P/E/C 等规则）。

实现了基于 flood-fill 的可达性检测，保证地图在开始游戏前是可通关的（所有 collectible 和出口对玩家可达）。

使用 MinilibX 加载 XPM 贴图并实现了瓦片化渲染（地板、墙、玩家、收藏品、出口、敌人等）。

处理键盘输入（支持 WASD 和方向键），计步并输出 Moves 信息；实现 ESC 退出。

实现游戏逻辑：拾取 collectible、击中敌人判输、到达出口判胜、移动计数和 HUD 显示（bonus 中）。

Bonus：实现敌人（简单 NPC）与路径/碰撞检测，敌人寻路/移动、玩家被敌人碰到判输；为地图元素和玩家做帧动画，绘制 HUD（剩余 collectible / 步数等）。

搭建 Makefile 支持 make（默认）和 make bonus 两种构建方式，并集成 libft 的构建。

写了若干辅助工具函数、出错处理。



已完成的功能：

必做部分：

地图加载与解析（.ber 文件）

地图校验：矩形、四周墙、含有 P（玩家）、E（出口）、至少一个 C（收藏品）

可达性检查（flood-fill / pathfinding）：确保从 P 能到达所有 C 并最终到达 E

渲染与贴图（XPM 资源）

玩家移动（WASD + ↑↓←→）

计步显示（控制台输出 Moves: n）

胜利/失败判定与退出处理

Makefile 与整合 libft

Bonus：

敌人（NPC）与碰撞检测：敌人能在地图上移动并在相遇时触发失败

敌人寻路 / 简单 AI（基于 map 的填充/搜索或移动策略）

帧动画（玩家/敌人/补给的图片切换）

HUD 渲染（可视化显示已收集/总 collectible、步数等）

更丰富的输入处理与窗口重绘逻辑

套件级别的测试地图（test-maps/，包含各种合法/错误案例）


模块构成：

includes/：公共头文件，定义数据结构（t_game, t_bonus, t_hookctx 等）与函数原型。

src/：实现必做题目逻辑（map 读入、校验、渲染、输入、游戏主循环、胜负判定）。

bonus/：实现扩展特性（动画、敌人、HUD、复杂的重新绘制逻辑）。

assets/：XPM 图片资源，按 tile/实体分类。

maps & test-maps/：手写地图与大量边界/错误测试样例，便于验证校验逻辑与路径检测。

libft/：项目使用的自写基础库（字符串、IO、printf 等）。

minilibx-linux/：图形库源码（由42学校提供）。



运行环境：

Linux（支持 X11）或 WSL2 + X server（需能运行 MinilibX）

基本编译工具：gcc（或兼容的 C 编译器）、make

X11 开发头文件（若系统未有 MinilibX 已预装，可能需 libx11-dev libxext-dev）

在常见 Debian/Ubuntu 上，可能需要：

sudo apt update
sudo apt install build-essential libx11-dev libxext-dev



编译

编译必做版本
make
编译 bonus 版本
make bonus

编译成功后会生成可执行文件：

./so_long —— 必做目标

./so_long_bonus —— 含 bonus 功能（敌人 / HUD / 动画）

支持传入任意合法的 .ber 地图文件。若地图不合法，程序会输出错误信息并退出。



控制：

移动：W / A / S / D 或 上 / 左 / 下 / 右（方向键）

退出：Esc

游戏会在终端输出 Moves: N，用于检查步数（同时 HUD 会在窗口显示信息，如果在 bonus 模式下）
