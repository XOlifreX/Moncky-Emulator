# Moncky-Emulator
A small emulator that runs Moncky asm code from files in different formats.
The Moncky processor is a custom designed 8bit processor designed by Dirk Demuynck, Computer Science teacher in the Karel de Grote College University.

At this moment it can only read pure assembly in correct Moncky syntax in a file called test1.txt found in the Debug folder (not included in the repo).

This is obviously just temporary, as in the near future you'll be able to pass a file path as an argument when running the programming in a command line.
Later it will have a GUI where you can select the file yourself to run and view the registers & RAM/ROM live.

Type of file contents that will be supported are:
-	asm				[v]
-	binary			[x]
-	pure numbers	[x]

When running content from a file, it will do a check for syntax errors. As of now, it's not fully tested yet, so it probably still has some bugs in it.


A Moncky processor documentation file will be added here in the future.