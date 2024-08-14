// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.
#ifndef PLATFORM_ASSERT
#define PLATFORM_ASSERT(x)
#endif
#include <string>
#include <memory>
#include <vector>
#include <assert.h>
#include <stdexcept>
#include <../stc/lexilla/lexlib/LexCharacterCategory.h>
using namespace Lexilla;
#include "Scintilla.h"
#include <../stc/scintilla/include/Scintilla.h>
#include <../stc/scintilla/include/Compat.h>
#include <../stc/scintilla/include/ILoader.h>
#include <../stc/scintilla/src/SplitVector.h>
#include <../stc/scintilla/src/Position.h>
#include <../stc/scintilla/include/ILexer.h>
#include <../stc/scintilla/src/Partitioning.h>
#include <../stc/scintilla/src/RunStyles.h>
#include <../stc/scintilla/src/Decoration.h>
#include <../stc/scintilla/src/CaseFolder.h>
#include <../stc/scintilla/src/CellBuffer.h>
#include <../stc/scintilla/src/CharClassify.h>
#include <../stc/scintilla/src/Document.h>
#include <../stc/lexilla/lexlib/LexAccessor.h>
#include <../stc/lexilla/lexlib/StyleContext.h>
#include <../stc/lexilla/lexlib/WordList.h>
#include <../stc/lexilla/lexlib/Accessor.h>

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif
#include <../stc/lexilla/lexlib/LexerModule.h>

bool IsADigit(int ch) noexcept {
    return (ch >= '0') && (ch <= '9');
}
bool IsAlphaNumeric(int ch) noexcept {
    return
        ((ch >= '0') && (ch <= '9')) ||
        ((ch >= 'a') && (ch <= 'z')) ||
        ((ch >= 'A') && (ch <= 'Z'));
}
bool isoperator(int ch) noexcept {
    if (IsAlphaNumeric(ch))
        return false;
    if (ch == '%' || ch == '^' || ch == '&' || ch == '*' ||
        ch == '(' || ch == ')' || ch == '-' || ch == '+' ||
        ch == '=' || ch == '|' || ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' || ch == ':' || ch == ';' ||
        ch == '<' || ch == '>' || ch == ',' || ch == '/' ||
        ch == '?' || ch == '!' || ch == '.' || ch == '~')
        return true;
    return false;
}



static inline bool IsAWordChar(const int ch) 
{
    switch (ch)
    {
    case ' ':
    case '\t':
    case '\n':
    case '\r':

    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':

    case '+':
    case '-':
    case '/':
    case '*':
    case '>':
    case '<':
    case '=':
        return false;

    default:
        return true;
    }
}

static inline bool IsStateComment(const int state)
{
    return ((state == SCE_FMS_COMMENT) || (state == SCE_FMS_COMMENTBACKSLASH));
}

static void AdvanceWithinVbar(
    Lexilla::StyleContext & Context
    )
{
    while (Context.ch != '|' && Context.More())
    {
        // Make sure to advance over
        // any escaped vbars.
        if (Context.ch == '\\')
        {
            Context.Forward();
            if (Context.ch == '|')
            {
                Context.Forward();
            }
        }
        else
        {
            Context.Forward();
        }
    }
}

static
void
ColorizeFmsLogoDoc(
    Sci_PositionU startPos, Sci_Position lengthDoc, int initStyle,
    WordList* keywordlists[], Accessor& styler)
{
    Lexilla::StyleContext sc(startPos, lengthDoc, initStyle, styler);
    for (; sc.More(); sc.Forward()) 
    {
        // Handle line continuation generically.
        if (sc.ch == '~') 
        {
            if (sc.chNext == '\n' || sc.chNext == '\r') 
            {
                // This was a line continuation, which breaks a comment
                if (IsStateComment(sc.state))
                {
                    sc.SetState(SCE_FMS_DEFAULT);
                }

                sc.Forward();
                if (sc.ch == '\r' && sc.chNext == '\n') 
                {
                    sc.Forward();
                }
                continue;
            }
        }

        // Determine if the current state should terminate.
        switch (sc.state)
        {
        case SCE_FMS_OPERATOR:
            sc.SetState(SCE_FMS_DEFAULT);
            break;

        case SCE_FMS_NUMBER:
            if (!IsAWordChar(sc.ch)) 
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_STRING:
            if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_STRING_VBAR);
            }
            else if (sc.ch == '\\') 
            {
                sc.Forward();
            }
            else if (sc.atLineEnd  ||
                     sc.ch == ' '  ||
                     sc.ch == '\t' ||
                     sc.ch == '('  ||
                     sc.ch == ')'  ||
                     sc.ch == '['  ||
                     sc.ch == ']'  ||
                     sc.ch == '{'  ||
                     sc.ch == '}'  ||
                     sc.ch == ';') 
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_STRING_VBAR:
            AdvanceWithinVbar(sc);
            sc.SetState(SCE_FMS_STRING);
            break;

        case SCE_FMS_VBAR:
            AdvanceWithinVbar(sc);
            sc.SetState(SCE_FMS_DEFAULT);
            sc.Forward();
            break;

        case SCE_FMS_COMMENT:
            // comments end at a newline, but can be continued
            // onto the next line if the newline is preceeded by
            // a backslash
            if (sc.Match("~\r\n") || sc.Match("~\n"))
            {
                // transition to continuation char state?
                sc.SetState(SCE_FMS_DEFAULT);
            }
            else if (sc.atLineEnd)
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            else if (sc.ch == '\\')
            {
                sc.SetState(SCE_FMS_COMMENTBACKSLASH);
            }
            break;

        case SCE_FMS_COMMENTBACKSLASH:
            if (sc.ch == '\r' || sc.ch == '\n')
            {
                sc.Forward();
                if (sc.ch == '\r' || sc.ch == '\n')
                {
                    // This was a backslash followed by a newline.
                    sc.Forward();
                }
            }
            sc.SetState(SCE_FMS_COMMENT);
            break;

        case SCE_FMS_VARIABLE:
            if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_VARIABLE_VBAR);
            }
            else if (sc.ch == '\\')
            {
                sc.Forward();
            }
            else if (!IsAWordChar(sc.ch))
            {
                sc.SetState(SCE_FMS_DEFAULT);
            }
            break;

        case SCE_FMS_VARIABLE_VBAR:
            AdvanceWithinVbar(sc);
            sc.SetState(SCE_FMS_VARIABLE);
            sc.Forward();
            break;

        case SCE_FMS_DEFAULT_BACKSLASH:
            sc.Forward();
            sc.SetState(SCE_FMS_DEFAULT);
            break;

        default:
            break;
        }

        // Determine if a new state should be entered.
        if (sc.state == SCE_FMS_DEFAULT) 
        {
            if (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext))) 
            {
                sc.SetState(SCE_FMS_NUMBER);
            }
            else if (sc.ch == ':')
            {
                sc.SetState(SCE_FMS_VARIABLE);
            }
            else if (sc.ch == '|')
            {
                sc.SetState(SCE_FMS_VBAR);
            }
            else if (sc.ch == ';') 
            {
                sc.SetState(SCE_FMS_COMMENT);
            }
            else if (sc.ch == '\"') 
            {
                sc.SetState(SCE_FMS_STRING);
            }
            else if (isoperator(static_cast<char>(sc.ch)))
            {
                sc.SetState(SCE_FMS_OPERATOR);
            }
            else if (sc.ch == '\\')
            {
                sc.SetState(SCE_FMS_DEFAULT_BACKSLASH);
            }
        }
    }
    sc.Complete();
}



static void FoldFmsLogoDoc(
    Sci_PositionU startPos, Sci_Position lengthDoc, int initStyle,
    WordList* keywordlists[], Accessor& styler
)
{

}

static const char * const g_FmsLogoWordLists[] = 
{
    "Structural keywords",
    "Primitives",
    "Library procedures",
    "Abbreviations",
    "Special Variables",
    0,
};

Lexilla::LexerModule lmFmsLogo(
        SCLEX_FMSLOGO,
        ColorizeFmsLogoDoc,
        "FMSLogo",
        FoldFmsLogoDoc,
        g_FmsLogoWordLists);
