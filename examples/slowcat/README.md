slowcat
=======

The `slowcat` example is a simple utility that copies files provided on the
command-line to standard output. Unlike Unix `cat`, this utility does not
support any command-line options (e.g. `-v` or `-n`). The purpose of this
utility is just to demonstrate the use of the `raw_stack_scanner` and
`abstract_parser` interfaces to build a stack of inputs and then walk them
character by character.

More advanced lexers and parsers are built on top of the `raw_stack_scanner`,
just by reacting to raw characters as they are encountered.
