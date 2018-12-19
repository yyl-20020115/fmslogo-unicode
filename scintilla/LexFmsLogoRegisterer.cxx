#include <stddef.h>

#include "ILexer.h"
#include "LexerModule.h"
#include "Catalogue.h"

extern LexerModule lmFmsLogo; // defined in LexFmsLogo.cxx

// A singleton class that registers the lexer that's implemented in
// LexFmsLogo.cxx.  While this could be implemented within that file and, none
// of the lexers that are defined within Scintilla register themselves, so for
// symmetry, this is done externally.
class CFmsLogoLexerRegisterer
{
private:
    CFmsLogoLexerRegisterer()
    {
        Catalogue::AddLexerModule(&lmFmsLogo);
    }

    CFmsLogoLexerRegisterer(CFmsLogoLexerRegisterer & object);

    // The singleton that registers the module.
    static CFmsLogoLexerRegisterer s_RegisteredModule;
};

// Intanciate the single that registers the module.
CFmsLogoLexerRegisterer CFmsLogoLexerRegisterer::s_RegisteredModule;
