#include <stddef.h>
#include <string.h>
#include <vector>
#include <../stc/scintilla/include/Scintilla.h>
#include <../stc/scintilla/include/ILexer.h>
#include <../stc/lexilla/lexlib/LexerModule.h>
#include <../stc/lexilla/lexlib/CatalogueModules.h>

extern void AddStaticLexerModule(Lexilla::LexerModule* plm);

extern Lexilla::LexerModule lmFmsLogo; // defined in LexFmsLogo.cxx
//extern Lexilla::CatalogueModules catalogueLexilla;
// 
// A singleton class that registers the lexer that's implemented in
// LexFmsLogo.cxx.  While this could be implemented within that file and, none
// of the lexers that are defined within Scintilla register themselves, so for
// symmetry, this is done externally.

class CFmsLogoLexerRegisterer
{
private:
    CFmsLogoLexerRegisterer()
    {
        AddStaticLexerModule(&lmFmsLogo);
    }

    CFmsLogoLexerRegisterer(CFmsLogoLexerRegisterer & object);

    // The singleton that registers the module.
    static CFmsLogoLexerRegisterer s_RegisteredModule;
};

// Intanciate the single that registers the module.
//NOTICE: fixed: we should manualy install the module, otherwise, it's flushed by the constructor of the vector(list)
//CFmsLogoLexerRegisterer CFmsLogoLexerRegisterer::s_RegisteredModule;
