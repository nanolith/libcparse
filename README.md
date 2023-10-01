libcparse
=========

This is a hand written parser for C that performs both a preprocessor parse and
a regular C token parse. I needed a parser that I could use to optionally expand
the preprocessor tokens, so that I could do ahead-of-time syntax highlighting.
I also intend to use this parser for C tooling.

Events and Messages
-------------------

libcparse provides a SAX-like parser for C. C has a rather complicated front-end
that consists of both a preprocessor and a regular parser. The preprocessor
provides conditional compilation, macro support, the inclusion of headers and
other source files, compiler-specific pragma statements, etc. Normally, a
compiler would want to expand all preprocessor tokens and perform all
preprocessor actions. However, this is not necessarily true for a library user.
For instance, a syntax highlighting application actually does not want to expand
preprocessor macros, and may in fact wish to do some partial preprocessor
expression resolution internally so that macro expressions can be highlighted in
a contextual manner. In order to support a wider set of use cases, this library
provides a dynamic view of lexical and parser tokens.

Parsers are composed of components that perform different actions. In order to
support this composition, a more abstracted view is provided to the library
user. The library user registers for an event callback, and receives events as
they are scanned or parsed. This registration can be performed at each layer of
the parser stack, allowing the user to see raw input character events,
preprocessor events, or parsed expression events. So, if a user wishes to see a
non-expanded view of preprocessor events, the user can register to receive these
events. Likewise, the user can track these events to decide how to process
further events. For instance, if the user does not wish to expand preprocessor
include statements (e.g. the user is a syntax highlighter), the user can ignore
evetns from the beginning of an include statement expansion and the end of this
include statement expansion.

Messages provide a means by which composed parser components can communicate
upstream to more general components. For instance, the preprocessor will send a
message to the raw input parser indicating that a new file stream should be
placed onto the file stream stack. In this way, a preprocessor include statement
can be expanded into the actual input stream of the included file. Each
component's contract includes a list of events that it can send downstream, a
list of messages it can send upstream, a list of events it processes, and a list
of messages it reacts to. This contract mechanism also allows this library to be
expanded, so that custom C extensions can be supported.
