#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #ifndef WX_PURE
     #include <windows.h>    // for MAKELCID and language functions
   #endif

   #include <wx/gdicmn.h>    // for wxPoint
   #include <wx/printdlg.h>
   #include <wx/msgdlg.h>
   #include <wx/menu.h>

   #include "logocodectrl.h"
   #include "localizedstrings.h"
   #include "logocore.h"      // for ARRAYSIZE
   #include "guiutils.h"
   #include "helputils.h"     // for ContextHelp
   #include "stringadapter.h"

   #include "wrksp.h" // for g_CharactersSuccessfullyParsedInEditor
#endif

// A helper class for printing
class CLogoCodePrintout : public wxPrintout
{
public:
    CLogoCodePrintout(
        const wxString        & Title,
        CLogoCodeCtrl         & EditControl,
        wxPageSetupDialogData & PageSetup
        );

    bool OnPrintPage(int Page);
    bool HasPage(int Page);
    bool OnBeginDocument(int StartPage, int EndPage);

    void
    GetPageInfo(
        int *MinPage,
        int *MaxPage,
        int *SelPageFrom,
        int *SelPageTo
        );

private:
    void ScaleForPrinting(wxDC * DeviceContext);

    CLogoCodeCtrl         & m_EditControl;
    wxPageSetupDialogData & m_PageSetup;

    int m_NextPrintStartPosition;

    // Physical printers cannot print all the way to the edge
    // of the paper and most programs want to leave a user-defined
    // margin that is larger than the physical margin as defined
    // by the printer.  FMSLogo always uses the physical margins.
    //
    // m_RenderRectangle is the region (relative to the physical
    // margins of the printer) where FMSLogo prints its content.
    //
    // m_PageRectangle is the physical dimensions of the
    // printable region on the paper.
    wxRect m_RenderRectangle;
    wxRect m_PageRectangle;
};

CLogoCodePrintout::CLogoCodePrintout(
    const wxString        & Title,
    CLogoCodeCtrl         & EditControl,
    wxPageSetupDialogData & PageSetup
    ) :
    wxPrintout(Title),
    m_EditControl(EditControl),
    m_PageSetup(PageSetup),
    m_NextPrintStartPosition(0)
{
}

void CLogoCodePrintout::ScaleForPrinting(wxDC * DeviceContext)
{
    // get printer and screen sizing values
    wxSize ppiScr;
    GetPPIScreen(&ppiScr.x, &ppiScr.y);
    if (ppiScr.x == 0)  // most possible guess 96 dpi
    {	ppiScr.x = 96;
        ppiScr.y = 96;
    }

    wxSize ppiPrt;
    GetPPIPrinter (&ppiPrt.x, &ppiPrt.y);
    if (ppiPrt.x == 0)  // scaling factor to 1
    {	ppiPrt.x = ppiScr.x;
        ppiPrt.y = ppiScr.y;
    }
    wxSize dcSize = DeviceContext->GetSize();
    wxSize pageSize;
    GetPageSizePixels(&pageSize.x, &pageSize.y);

    // set user scale
    float scale_x = 
        (float)(ppiPrt.x * dcSize.x) /
        (float)(ppiScr.x * pageSize.x);
    float scale_y = 
        (float)(ppiPrt.y * dcSize.y) /
        (float)(ppiScr.y * pageSize.y);
    DeviceContext->SetUserScale(scale_x, scale_y);
}

bool CLogoCodePrintout::OnPrintPage(int page)
{
    wxDC * dc = GetDC();
    if (dc == NULL)
    {
        return false;
    }

    // Scale the DC
    ScaleForPrinting(dc);

    // If we're starting from page 1, then set the
    // position back to the beginning.
    // BUG: This assumes that the user always starts
    // printing from page 1.
    if (page == 1) 
    {
        m_NextPrintStartPosition = 0; // start at the beginning
    }

    int nextStartPosition = m_EditControl.FormatRange(
        true,                          // print
        m_NextPrintStartPosition,      // start position
        m_EditControl.GetTextLength(), // end position
        dc,
        dc,
        m_RenderRectangle,
        m_PageRectangle);

    if (nextStartPosition <= m_NextPrintStartPosition)
    {
        // There was no forward progress made when printing.
        // Something is wrong.  This should not happen in
        // practice, but if it does, we should return an error
        // rather than risk going into an infinite loop.
        assert(!"No progress made when printing.");
        return false;
    }

    m_NextPrintStartPosition = nextStartPosition;
    return true;
}

bool
CLogoCodePrintout::OnBeginDocument(int startPage, int endPage)
{
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
    {
        return false;
    }

    // TODO: Compute page-to-offset mapping so that we
    // always know how to print each page, instead of
    // assuming that all pages are printed.
    // See the comment in CLogoCodeCtrl::Print().
    return true;
}

void
CLogoCodePrintout::GetPageInfo(
    int *minPage,
    int *maxPage,
    int *selPageFrom,
    int *selPageTo
    )
{
    // initialize values
    *minPage = 0;
    *maxPage = 0;

    *selPageFrom = 0;
    *selPageTo   = 0;

    wxDC *dc = GetDC();
    if (dc == NULL) 
    {
        return;
    }

    // Scale DC if possible
    ScaleForPrinting(dc);

    // get printer and screen sizing values
    m_RenderRectangle = GetLogicalPageRect();
    m_PageRectangle   = GetLogicalPageMarginsRect(m_PageSetup);

    // Now that the page and render rectangles are set to a single page,
    // we can count all the pages by asking Scintilla to "print" all
    // pages consecutively (without actually printing anything).
    while (HasPage(*maxPage))
    {
        int nextStartPosition = m_EditControl.FormatRange(
            false,                         // don't really print
            m_NextPrintStartPosition,      // start position
            m_EditControl.GetTextLength(), // end position
            dc,
            dc,
            m_RenderRectangle,
            m_PageRectangle);

        if (nextStartPosition <= m_NextPrintStartPosition)
        {
            // There was no forward progress made when printing.
            // Something is wrong.  This should not happen in
            // practice, but if it does, we should return an error
            // rather than risk going into an infinite loop.
            assert(!"No progress made when printing.");
            return;
        }

        m_NextPrintStartPosition = nextStartPosition;
        *maxPage += 1;
    }

    // Reset the state that has been printed
    m_NextPrintStartPosition = 0;
    if (*maxPage > 0) 
    {
        *minPage = 1;
    }
    *selPageFrom = *minPage;
    *selPageTo   = *maxPage;
}

bool CLogoCodePrintout::HasPage(int pageNum)
{
    return m_NextPrintStartPosition < m_EditControl.GetTextLength();
}


// BUG: this should return the number of characters, but it instead
// returns the number of bytes.  However, for this is used, it does
// not cause problems.
int CLogoCodeCtrl::GetTextLength() const
{
	return GetWindowTextLength(GetHandle());
}

wxString CLogoCodeCtrl::GetTextRange(int startPos, int endPos)
{
	return GetRange(startPos, endPos);
}

wxString CLogoCodeCtrl::GetRange(long startPos, long endPos) const
{
	wxString entireBuffer(GetText());
	if (startPos == 0 && endPos == -1)
	{
		return entireBuffer;
	}

	// startPos and endPos assume that newlines are just LF,
	// but GetText() returns it with CRLF.
	entireBuffer.Replace(wxString(L"\r\n"), wxString(L"\n"));

	// startPos and endPos are in characters, but wxString::Mid()
	// treats its arguments as being in bytes.  To get the correct substring,
	// we must also treat it as characters.

	// CONSIDER: this could be rewritten using _ismbblead

	// Convert the mulitbyte string into Unicode wide characters.
	int wideBufferLength = entireBuffer.Len() + 1;
	wchar_t * wideBuffer = new wchar_t[wideBufferLength];
	MultiByteToWideChar(
		CP_ACP,                 // system ANSI code page
		0,                      // flags: don't fail on error
		wxString(entireBuffer), // input string
		-1,                     // its length (NUL-terminated)
		wideBuffer,             // output string
		wideBufferLength);      // size of output buffer (characters)

	// Convert the unicode selection back to a multibyte string
	int selectionLength = endPos - startPos;
	char * buffer = new char[sizeof(wchar_t*) * selectionLength]; // worst case: every character is double-byte
	int bufferLength = WideCharToMultiByte(
		CP_ACP,                 // system ANSI code page
		0,                      // use best-fit character and don't fail on error
		wideBuffer + startPos,  // offset of first desired character
		selectionLength,        // total desired characters
		buffer,                 // multibyte buffer
		2 * selectionLength,    // size of buffer in bytes
		NULL,                   // use the system default for characters that have no coding
		NULL);                  // we don't care what character was used.

	// Wrap the multi-byte selection in a wxString
	wxString range(buffer, bufferLength);

	delete[] wideBuffer;
	delete[] buffer;

	return range;
}

// Prints the contents of the editor.
void CLogoCodeCtrl::Print()
{
    // Note: printData and pageSetupData are normally global variables
    // that preserve printer preferences across printouts.  Since
    // FMSLogo's editor doesn't support advanced printer options,
    // we just create new variables each time.
    wxPrintData       printData;
    wxPrintDialogData printDialogData(printData);

    // Disable the selection of page numbers to shield the user
    // from a bug in CLogoCodePrintout where it assumes that
    // the user always prints from page 1.  This could be fixed
    // by creating a page-to-offset mapping in the OnBeginDocument
    // handler, then using that instead of letting Scintilla do the
    // calculation in iterative calls to FormatRange() in OnPrint().
    printDialogData.EnablePageNumbers(false);

    // Show the printer selection dialog box.
    wxPrinter printer(&printDialogData);

    // Read the default page settings.
    // On Windows, even though we call ShowModal, no
    // dialog box is displayed because we set the
    // default info to true.
    wxPageSetupDialogData pageSetupData;
    pageSetupData.SetDefaultInfo(true);
    wxPageSetupDialog pageSetup(this, &pageSetupData);
    pageSetup.ShowModal();

    CLogoCodePrintout printout(
		wxString(LOCALIZED_GENERAL_PRODUCTNAME),
        *this,
        pageSetupData);

    if (!printer.Print(this, &printout, true))
    {
        // This can happen in two cases:
        // 1) If there was an error while printing, in which
        //    case the operating system will have communicated
        //    the problem to the user, so we don't need to.
        // 2) If the print job was cancelled by the user,
        //    in which case we don't need to tell the user
        //    that they cancelled the job.
        //
        // Therefore, all we need to do is exit.
        return;
    }

    // If we preserved the global settings, we'd update the
    // printing preferences here.
    //printData = printer.GetPrintDialogData().GetPrintData();
}

#ifndef USE_RICHTEXT_CODE_EDITOR

#include "scintilla/SciLexer.h"
#ifdef WX_PURE
  #include "scintilla/include/Scintilla.h"
#else
  #include "../src/stc/scintilla/include/Scintilla.h"
#endif

CLogoCodeCtrl::CLogoCodeCtrl(
    wxWindow *      Parent,
    wxWindowID      Id
    ) : 
    wxStyledTextCtrl(Parent, Id),
    m_IsDirty(false)
{
    // Hide the margin that Scintilla creates by default.
    // We don't use it for anything, so it just looks weird.
    SetMarginWidth(1, 0);

    // Switch to the FMSLogo style
    StyleClearAll();
    SetLexer(SCLEX_FMSLOGO);
    Colourise(0, -1);

    // Override the Ctrl+<LETTER> sequences to do the default platform
    // action so that they don't insert control characters.
    for (int i = 0; i < 26; i++)
    {
        // I'm not sure why, but Ctrl+Y for "Redo" is special and if
        // we set its handler to 0, it stops working.
        const int key = 'A' + i;
        if (key != 'Y')
        {
            CmdKeyAssign(key, wxSTC_SCMOD_CTRL, 0);
        }
    }

    // Configure the control for auto-completions.
    AutoCompSetTypeSeparator(0); // no typing
    AutoCompSetIgnoreCase(true); // FMSLogo is case insensitive
    AutoCompSetDropRestOfWord(true);
}

bool
CLogoCodeCtrl::SetFont(const wxFont & Font)
{
    // Set the font
    wxFont fontCopy(Font);
    StyleSetFont(STYLE_DEFAULT, fontCopy);

    // Apply the font
    StyleClearAll();

    const wxColor black        (0,       0, 0);
    const wxColor white        (0XFF, 0XFF, 0XFF);
    const wxColor darkgreen    (0,    0x80, 0);
    const wxColor darkred      (0x80,    0, 0);
    const wxColor red          (0xFF,    0, 0);
    const wxColor lightgrey    (0xCC, 0xCC, 0xCC);
    const wxColor lightblue    (200,   242, 255);
    const wxColor darkblue     (  0,    0,  0x80);

    StyleSetForeground(SCE_FMS_COMMENT,          darkgreen);
    StyleSetForeground(SCE_FMS_COMMENTBACKSLASH, darkgreen);
    StyleSetForeground(SCE_FMS_STRING,         darkred);
    StyleSetForeground(SCE_FMS_STRING_VBAR,    darkred);

    StyleSetForeground(SCE_FMS_VARIABLE,       darkblue);
    StyleSetForeground(SCE_FMS_VARIABLE_VBAR,  darkblue);

    StyleSetForeground(STYLE_BRACELIGHT,    darkgreen);
    StyleSetBackground(STYLE_BRACELIGHT,    lightblue);

    StyleSetForeground(STYLE_BRACEBAD,      red);
    StyleSetBackground(STYLE_BRACEBAD,      lightblue);

    return true;
}

bool
CLogoCodeCtrl::IsTextSelected()
{
    // Get whatever is selected
    int selectionStart = -1;
    int selectionEnd   = -1;
    GetSelection(&selectionStart, &selectionEnd);

    // Determine if the selection is non-empty
    return selectionStart != selectionEnd;
}

static bool IsParen(int Char)
{
    switch (Char)
    {
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
        return true;
    }

    return false;
}

void
CLogoCodeCtrl::FindMatchingParen(
    int & CurrentParenPosition,
    int & MatchingParenPosition
    )
{
    CurrentParenPosition  = INVALID_POSITION;
    MatchingParenPosition = INVALID_POSITION;

    int currentPosition = GetCurrentPos();
    int currentChar     = GetCharAt(currentPosition);
    if (IsParen(currentChar))
    {
        // we're close enough to a paren to try to match it
        int matchingParenPosition = BraceMatch(currentPosition);
        if (matchingParenPosition != INVALID_POSITION)
        {
            // found a match

            // If the paren after the caret is an open paren, then
            // the matching paren will be after it.  In this case, 
            // we want to jump just after the matching paren's position
            // to remain on the outside of the parens.
            // Likewise, if the paren after the caret is a close paren,
            // then the matching paren will be before it.  In this case,
            // we also want to jump after the matching paren's position
            // so that we can remain on the inside of the parens.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = matchingParenPosition + 1;
        }
        else
        {
            // If paren after the caret has no matching paren,
            // then mark it as a bad paren, instead of trying to
            // match the one before the caret.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = INVALID_POSITION;
        }
    }
    else
    {
        // we're not over a paren, so try the position just before the caret
        if (currentPosition != 0)
        {
            int previousChar = GetCharAt(currentPosition - 1);
            if (IsParen(previousChar))
            {
                // we're close enough to a paren to try to match it
                int matchingParenPosition = BraceMatch(currentPosition - 1);
                if (matchingParenPosition != INVALID_POSITION)
                {
                    // found a match

                    // If the paren before the caret is an open paren, then
                    // the matching paren will be after it.  In this case, 
                    // we want to jump to the matching paren's position to
                    // remain on the inside of the parens.
                    // Likewise, if the paren before the caret is a close paren,
                    // then the matching paren will be before it.  In this case,
                    // we also want to jump after the matching paren's position
                    // so that we can remain on the outside of the parens.
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = matchingParenPosition;
                }
                else
                {
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = INVALID_POSITION;
                }
            }
        }
    }
}

// Moves the caret to the matching paren/bracket/brace if the caret is
// currently adject to a paren/bracket/brace. 
void CLogoCodeCtrl::FindMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION)
    {
        GotoPos(matchingParenPosition);
    }
}

// Moves the caret to the matching paren/bracket/brace, if the caret is
// currently adject to a paren/bracket/brace.  Also selects the entire
// text within the parens.
void CLogoCodeCtrl::SelectMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION && currentParenPosition != INVALID_POSITION)
    {
        // Found a match.  Jump to it.
        SetAnchor(GetCurrentPos());
        SetCurrentPos(matchingParenPosition);
        ScrollCaret();
    }
}


// Sends SCI_SCROLLCARET because wxStyledTextCtrl doesn't export this wrapper.
// TODO: Submit a patch to wxWidgets to add this.
void CLogoCodeCtrl::ScrollCaret()
{
    SendMsg(SCI_SCROLLCARET);
}

void CLogoCodeCtrl::OnUpdateUi(wxStyledTextEvent& Event)
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (currentParenPosition != INVALID_POSITION)
    {
        // We're close enough to a paren to try to match it
        if (matchingParenPosition != INVALID_POSITION)
        {
            // found a match
            if (currentParenPosition == GetCurrentPos())
            {
                BraceHighlight(currentParenPosition, matchingParenPosition - 1);
            }
            else
            {
                BraceHighlight(currentParenPosition, matchingParenPosition);
            }
        }
        else
        {
            // didn't find a match
            BraceBadLight(currentParenPosition);
        }
    }
    else
    {
        // We're not adacent to a paren, so remove the paren highlighting.
        BraceBadLight(INVALID_POSITION);
        BraceHighlight(INVALID_POSITION, INVALID_POSITION);
    }
}

static
wxString ToLower(const wxString & String)
{
#ifdef WX_PURE
    return String.Lower();
#else
    size_t length = String.length();

	wchar_t* buffer = new wchar_t[length + 1];
	memset(buffer, 0, (length + 1) * sizeof(wchar_t));

	LCMapString(
		MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
		LCMAP_LOWERCASE,
		String.c_str(),
		String.length(),
		buffer,
		length);

	wxString w(buffer);

	delete[] buffer;
	return w;
#endif
}

static
wxString ToUpper(const wxString & String)
{
#ifdef WX_PURE
    return String.Lower();
#else
    size_t length = String.length();
	wchar_t* buffer=new wchar_t[length+1];
	memset(buffer, 0, (length + 1) * sizeof(wchar_t));

    LCMapString(
        MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT),
        LCMAP_UPPERCASE,
        String.c_str(),
        String.length(),
		buffer,
        length);

    wxString w(buffer);

	delete[] buffer;
	return w;
#endif
}

void CLogoCodeCtrl::AutoComplete()
{
    enum CasePreference
    {
        ALLCAPS,
        LOWERCASE,
        INITIALCAPS,
    };

    // Determine what the programmer has typed so far that should be completed.
    int caretPosition   = GetCurrentPos();
    int tokenStart      = WordStartPosition(caretPosition, false);

    // Extract from the word start to the current caret position.
    wxString token(GetTextRange(tokenStart, caretPosition));

    // If the caret is in a whitespace run, then "token" will be all
    // of the whitespace from the previous word's ending to the caret.
    // In this case, we want to suggest completions as if token were empty,
    // so we Trim() to convert the whitespace to the empty string.
    // Note that Trim() removes whitespace from the right, but this is equivalent
    // to removing it from the left when token is entirely whitespace.
    token.Trim();

    // If the caret is after a ":" that is not followed by any word characters,
    // then token will be ":".  In this case, we want to complete as variables,
    // but not include the ":" in our search, so we clear the token and handle
    // it the same as if the caret were after a colon in ":var".
    if (token.IsSameAs(':'))
    {
        token.Clear();
    }

    int tokenLength = token.length();

    int caretStyle;
    if (tokenLength == 0)
    {
        if (caretPosition != 0 &&
            GetTextRange(caretPosition - 1, caretPosition).IsSameAs(':'))
        {
            // For ":var", when the caret is immediately after a ":" token is
            // empty.  We would auto-complete as procedure if we interrogated the
            // caret style in this context, so we handle it as a special case.
            caretStyle = SCE_FMS_VARIABLE;
        }
        else
        {
            // At the begining of the file or within whitespace
            // all procedure calls are legal.
            caretStyle = SCE_FMS_DEFAULT;
        }
    }
    else
    {
        // Get the style that is determined by the lexer.
        // We must use one character before the current one
        // because the variable and text styles end at the word
        // break, but if another character were typed, it would
        // be included in that style.
        assert(caretPosition != 0);
        caretStyle = GetStyleAt(caretPosition - 1);
    }

    // Collect all possible completions based on the context.
    NODE   * allNames;
    wxString completionPrefix;
    size_t   completionPrefixLength;
    if (caretStyle == SCE_FMS_DEFAULT || caretStyle == SCE_FMS_IDENTIFIER)
    {
        // We are completing in a context that accepts procedure names.
        allNames               = get_all_proc_names();
        completionPrefix       = token;
        completionPrefixLength = tokenLength;
    }
    else if (caretStyle == SCE_FMS_VARIABLE)
    {
        // We are completion in a context that accepts variable names.
        allNames               = get_all_variable_names();
        completionPrefix       = wxString(":") + token; // prefix suggestions with ":"
        completionPrefixLength = tokenLength + 1;
    }
    else
    {
        // No completions are possible.
        allNames               = NIL;
        completionPrefix       = wxEmptyString;
        completionPrefixLength = 0;
    }

    // Because FMSLogo is case-insensitive, a programmer can use whatever
    // casing scheme they prefer (upper case, lower case, initial caps, etc.).
    // If the auto-completion suggested completions in a different
    // casing scheme than the programmer wants, it would be so frustrating
    // that the suggestions would be unusable.
    // To mitigate this, we try to infer the casing scheme from the
    // portion which the programmer has typed so far.
    CasePreference casePreference;
    if (ToUpper(completionPrefix) == completionPrefix)
    {
        // Default to ALLCAPS on empty word
        casePreference = ALLCAPS;
    }
    else if (ToLower(completionPrefix) == completionPrefix)
    {
        casePreference = LOWERCASE;
    }
    else
    {
        // Assume any mixed case style is initial caps.
        casePreference = INITIALCAPS;
    }

    // Look through all of the collected symbols for ones
    // that begin with the completionPrefix.
    wxString completions;
    for (NODE * nd = allNames; nd != NIL; nd = cdr(nd))
    {
        NODE * nameNode = car(nd);
        wxString currentName(getstrptr(nameNode), getstrlen(nameNode));

        // Because FMSLogo is case-insensitive, the auto-completion
        // cannot use strict case comparision.
        const wxString & namePrefix = currentName.Left(tokenLength);
        if (token.CmpNoCase(namePrefix) != 0)
        {
            // This name does not begin with the prefix, so it is
            // not appropriate to show as a completion.
            continue;
        }

        // Use this completion following the casing preference
        // that was inferred from the completion prefix.
        wxString caseCorrectCompletion(completionPrefix);
        const wxString & rest = currentName.Mid(tokenLength);
        if (casePreference == ALLCAPS)
        {
            caseCorrectCompletion += ToUpper(rest);
        }
        else
        {
            caseCorrectCompletion += ToLower(rest);
        }

        // Append this name to the list of completions.
        completions += caseCorrectCompletion + " ";
    }
    gcref(allNames);

    if (!completions.IsEmpty())
    {
        AutoCompShow(completionPrefixLength, completions);
    }
}

void CLogoCodeCtrl::OnSavePointReached(wxStyledTextEvent& Event)
{
    m_IsDirty = false;
}

void CLogoCodeCtrl::OnSavePointLeft(wxStyledTextEvent& Event)
{
    m_IsDirty = true;
}

void
CLogoCodeCtrl::SetScintillaSearchFlags(
    wxFindReplaceFlags WxSearchFlags
    )
{
    // Map the wxWidgets flags to the Scintilla flags
    int scintillaSearchFlags = 0;
    
    if (WxSearchFlags & wxFR_MATCHCASE)
    {
        scintillaSearchFlags |= SCFIND_MATCHCASE;
    }
    if (WxSearchFlags & wxFR_WHOLEWORD)
    {
        scintillaSearchFlags |= SCFIND_WHOLEWORD;
    }

    // Set the scintilla search flags.
    SetSearchFlags(scintillaSearchFlags);
}

void
CLogoCodeCtrl::DoSearchOperation(
    SEARCH_OPERATION   SearchOperation,
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    // Configure Scintilla to search as requested
    SetScintillaSearchFlags(WxSearchFlags);

    if (SearchOperation == SEARCH_OPERATION_ReplaceAndFind)
    {
        // We are doing a replace&find operation.
        // If the string to be replaced is currently selected, then replace it.
        // After the replacement is performed, search for the next occurence.
        const wxString & selectedText = GetSelectedText();

        // Now figure out what to do with it.
        int cmp;
        if (WxSearchFlags & wxFR_MATCHCASE)
        {
            // Do a case-sensitive comparison
            cmp = selectedText.Cmp(StringToFind);
        }
        else
        {
            // Do a case-insensitive comparison
            cmp = selectedText.CmpNoCase(StringToFind);
        }

        if (cmp == 0)
        {
            // This is a match.  Replace the string.
            int selectionStart = GetSelectionStart();
            int selectionEnd   = GetSelectionEnd();

            // Move the target to the selection
            SetTargetStart(selectionStart);
            SetTargetEnd(selectionEnd);

            // Perform the replacement
            ReplaceTarget(ReplacementString);

            // Update the selection to be what we just inserted.
            SetSelection(
                selectionStart,
                selectionStart + ReplacementString.Length());
        }
    }

    // Now search for the next occurance
    if (WxSearchFlags & wxFR_DOWN)
    {
        // We're searching down, so the range goes from the
        // current position to the end.
        SetTargetStart(GetSelectionEnd());
        SetTargetEnd(GetTextLength());
    }
    else
    {
        // We're searching up, so the range goes from the
        // current position to the beginning.
        SetTargetStart(GetSelectionStart());
        SetTargetEnd(0);
    }

    // Perform the search.
    int location = SearchInTarget(StringToFind);
    if (location != -1)
    {
        // Found it.  Select the string.
        SetSelection(location, location + StringToFind.Length());

        // Scroll the selection into view.
        EnsureCaretVisible();
    }
    else
    {
        // Notify the user that we were unable to find it.
        const wxString & notFoundMessage = wxString::Format(
			wxString(LOCALIZED_STRINGTABLE_CANNOTFINDSTRING),
            StringToFind.c_str());

        ::wxMessageBox(
            notFoundMessage,
			wxString(LOCALIZED_GENERAL_PRODUCTNAME),
            wxICON_WARNING | wxOK,
            this);
    }
}

void
CLogoCodeCtrl::Find(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind
    )
{
    DoSearchOperation(
        SEARCH_OPERATION_Find,
        WxSearchFlags,
        StringToFind,
        wxEmptyString);
}

void
CLogoCodeCtrl::Replace(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    DoSearchOperation(
        SEARCH_OPERATION_ReplaceAndFind,
        WxSearchFlags,
        StringToFind,
        ReplacementString);
}

void
CLogoCodeCtrl::ReplaceAll(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    // Configure Scintilla to search as requested
    SetScintillaSearchFlags(WxSearchFlags);

    // The user selected "Replace All", so the selection
    // goes from the beginning to the end of the document.
    SetTargetStart(0);
    SetTargetEnd(GetTextLength());

    int location = SearchInTarget(StringToFind);
    while (location != -1)
    {
        // Found it. Replace the string
        ReplaceTarget(ReplacementString);

        // Move the selection so that we can repeat the search
        SetTargetStart(location + ReplacementString.Length());
        SetTargetEnd(GetTextLength());

        // Repeat the search
        location = SearchInTarget(StringToFind);
    }
}

bool
CLogoCodeCtrl::IsDirty() const
{
    return m_IsDirty;
}

// Puts the editor into a dirty state and
// moves the caret to the line that had the error.
void CLogoCodeCtrl::ReopenAfterError()
{
    // Put the editor into a dirty state so that
    // saving it without making any changes will cause the
    // contents to be re-evaluated and generate another
    // error, instead of ignoring the changes from the
    // previous incarnation where the error was first
    // introduced.
    m_IsDirty = true;

    // Move the caret to the line that had the error.
    GotoPos(g_CharactersSuccessfullyParsedInEditor);
}

void CLogoCodeCtrl::OnContextMenu(wxContextMenuEvent& Event)
{
    static const MENUITEM contextMenuItems[] = {
        {LOCALIZED_POPUP_UNDO,      wxID_UNDO},
        {LOCALIZED_POPUP_REDO,      wxID_REDO},
        {0},
        {LOCALIZED_POPUP_CUT,       wxID_CUT},
        {LOCALIZED_POPUP_COPY,      wxID_COPY},
        {LOCALIZED_POPUP_PASTE,     wxID_PASTE},
        {LOCALIZED_POPUP_DELETE,    wxID_DELETE},
        {LOCALIZED_POPUP_SELECTALL, wxID_SELECTALL},
        {0},
        {LOCALIZED_POPUP_HELP,      wxID_HELP_INDEX},
    };

    wxMenu menu;
    FillMenu(&menu, contextMenuItems, ARRAYSIZE(contextMenuItems));

    // When the parent window is a wxDialog (not a wxFrame) then the
    // wxUpdateUIEvent don't get sent when PopupMenu() is called.
    // Therefore, we must enable/disable the popups manually.
    menu.Enable(wxID_UNDO,      CanUndo());
    menu.Enable(wxID_REDO,      CanRedo());
    menu.Enable(wxID_CUT,       CanCut());
    menu.Enable(wxID_COPY,      CanCopy());
    menu.Enable(wxID_PASTE,     CanPaste());
    menu.Enable(wxID_DELETE,    CanDelete());
    menu.Enable(wxID_SELECTALL, CanSelectAll());

    PopupMenu(&menu);
}

void CLogoCodeCtrl::OnUndo(wxCommandEvent& WXUNUSED(Event))
{
    Undo();
}

void CLogoCodeCtrl::OnRedo(wxCommandEvent& WXUNUSED(Event))
{
    Redo();
}

void CLogoCodeCtrl::OnCut(wxCommandEvent& WXUNUSED(Event))
{
    Cut();
}

bool CLogoCodeCtrl::CanCut()
{
    return IsTextSelected();
}

void CLogoCodeCtrl::OnCopy(wxCommandEvent& WXUNUSED(Event))
{
    Copy();
}

bool CLogoCodeCtrl::CanCopy()
{
    return IsTextSelected();
}

void CLogoCodeCtrl::OnPaste(wxCommandEvent& WXUNUSED(Event))
{
    Paste();
}

void CLogoCodeCtrl::OnDelete(wxCommandEvent& WXUNUSED(Event))
{
    Clear();
}

bool CLogoCodeCtrl::CanDelete()
{
    // "Delete" is enabled if there is anything selected,
    // or if a character appears after the cursor.
    return IsTextSelected() || GetCurrentPos() != GetLength();
}

void CLogoCodeCtrl::OnSelectAll(wxCommandEvent& WXUNUSED(Event))
{
    SelectAll();
}

bool CLogoCodeCtrl::CanSelectAll()
{
    return GetLength() != 0; // true, iff text exists
}

void CLogoCodeCtrl::OnHelpTopicSearch(wxCommandEvent& WXUNUSED(Event))
{
    ContextHelp(GetSelectedText());
}

void CLogoCodeCtrl::ClearAll()
{
	SetValue(wxEmptyString);
}

void CLogoCodeCtrl::EmptyUndoBuffer()
{
	SendMessage(GetHandle(), EM_EMPTYUNDOBUFFER, 0, 0);
}

int CLogoCodeCtrl::TextHeight(int line)
{
	int x;
	int y;
	GetTextExtent(L"Tg", &x, &y);
	return y + 5; // Chinese characters are bigger than Roman characters
}

void CLogoCodeCtrl::SetCurrentPos(int caret)
{
	SetInsertionPoint(caret);
}

BEGIN_EVENT_TABLE(CLogoCodeCtrl, wxStyledTextCtrl)
    EVT_STC_UPDATEUI(wxID_ANY,         CLogoCodeCtrl::OnUpdateUi)
    EVT_STC_SAVEPOINTREACHED(wxID_ANY, CLogoCodeCtrl::OnSavePointReached)
    EVT_STC_SAVEPOINTLEFT(wxID_ANY,    CLogoCodeCtrl::OnSavePointLeft)
    EVT_CONTEXT_MENU(CLogoCodeCtrl::OnContextMenu)
    EVT_MENU(wxID_UNDO,                CLogoCodeCtrl::OnUndo)
    EVT_MENU(wxID_REDO,                CLogoCodeCtrl::OnRedo)
    EVT_MENU(wxID_CUT,                 CLogoCodeCtrl::OnCut)
    EVT_MENU(wxID_COPY,                CLogoCodeCtrl::OnCopy)
    EVT_MENU(wxID_PASTE,               CLogoCodeCtrl::OnPaste)
    EVT_MENU(wxID_DELETE,              CLogoCodeCtrl::OnDelete)
    EVT_MENU(wxID_SELECTALL,           CLogoCodeCtrl::OnSelectAll)
    EVT_MENU(wxID_HELP_INDEX,          CLogoCodeCtrl::OnHelpTopicSearch)
END_EVENT_TABLE()

#else

// Implementation of the CLogoCodeCtrl that uses wxTextCtrl for languages which
// use a multi-byte character set, such as Simplified Chinese.
// This is stop-gap solution until FMSLogo is a pure-Unicode application.
#include <richedit.h>
//#include <mbstring.h>

CLogoCodeCtrl::CLogoCodeCtrl(
    wxWindow *      Parent,
    wxWindowID      Id
    ) : 
    wxTextCtrl(
        Parent,
        Id,
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE | wxTE_NOHIDESEL | wxWANTS_CHARS | wxTE_RICH2)
{
}

// Puts the editor into a dirty state and
// moves the caret to the line that had the error.
void CLogoCodeCtrl::ReopenAfterError()
{
    // Put the editor into a dirty state so that
    // saving it without making any changes will cause the
    // contents to be re-evaluated and generate another
    // error, instead of ignoring the changes from the
    // previous incarnation where the error was first
    // introduced.
    MarkDirty();

    // Move the caret to the line that had the error.
    SetInsertionPoint(g_CharactersSuccessfullyParsedInEditor);
}

wxString CLogoCodeCtrl::GetText() const
{
    int textLength = GetTextLength();

	wchar_t * buffer = new wchar_t[(textLength + 1)];

    GetWindowText(GetHandle(), buffer, textLength + 1);

    wxString text(buffer, textLength);

    delete [] buffer;

    return text;
}

//void CLogoCodeCtrl::Clear()
//{
//    SendMessage(
//        GetHandle(),
//        EM_REPLACESEL,
//        TRUE, // this action is undoable
//        reinterpret_cast<LPARAM>(L""));
//}

void CLogoCodeCtrl::ClearAll()
{
    SetValue(wxEmptyString);
}

void CLogoCodeCtrl::EmptyUndoBuffer()
{
    SendMessage(GetHandle(), EM_EMPTYUNDOBUFFER, 0, 0);
}

int CLogoCodeCtrl::TextHeight(int line)
{
    int x;
    int y;
    GetTextExtent("Tg", &x, &y); 
    return y + 5; // Chinese characters are bigger than Roman characters
}

void CLogoCodeCtrl::SetCurrentPos(int caret)
{
    SetInsertionPoint(caret);
}

void CLogoCodeCtrl::SetSelBackground(bool useSetting, const wxColour &back)
{
}

void CLogoCodeCtrl::SetSelForeground(bool useSetting, const wxColour &fore)
{
}

wxString CLogoCodeCtrl::GetSelectedText()
{
    // For compatibility with wxStyledTextCtrl, turn newlines to be CRLF.
    wxString selection(GetStringSelection());
    selection.Replace(wxString(L"\n"), wxString(L"\r\n"));
    return selection;
}

void CLogoCodeCtrl::AutoComplete()
{
    // Do nothing.  This editor does not support auto complete.
}

void CLogoCodeCtrl::SetUseHorizontalScrollBar(bool visible)
{
}

void CLogoCodeCtrl::HideSelection(bool hide)
{
    SendMessage(GetHandle(), EM_HIDESELECTION, hide ? 1 : 0, 0);
}

bool CLogoCodeCtrl::AutoCompActive()
{
    return false;
}

// Returns the current line of the caret (zero-indexed).
// This is only used to determine if pressing up in the commander
// input should give focus to the commander history.
int CLogoCodeCtrl::GetCurrentLine()
{
    int position = GetInsertionPoint();

    int lineNumber = 0;

    // Count the number of newlines before the current position
    wxString textBeforePosition(GetRange(0, position));
    for (wxString::const_iterator i = textBeforePosition.begin();
         i != textBeforePosition.end();
         ++i)
    {
        if (*i == '\n')
        {
            lineNumber++;
        }
    }

    return lineNumber;
}

// wxTextCtrl::SetValue() doesn't set the value correctly when text contains
// double-byte characters, so we override it.
void CLogoCodeCtrl::SetValue(const wxString &text)
{
    SetWindowText(GetHandle(), /*WXSTRING_TO_STRING*/(text));
    DiscardEdits(); // mark not dirty
}

void CLogoCodeCtrl::SetText(const wxString &text)
{
    SetValue(text);
}

void CLogoCodeCtrl::AddTextRaw(const wchar_t *text, int length)
{
    AppendText(wxString(text, length));
}

void CLogoCodeCtrl::SetSavePoint()
{
    // Mark as not dirty.
    DiscardEdits();
}

void CLogoCodeCtrl::Cancel()
{
}

void CLogoCodeCtrl::SetUndoCollection(bool collectUndo)
{
}

void CLogoCodeCtrl::GotoPos(int caret)
{
    SetInsertionPoint(caret);
}

void CLogoCodeCtrl::FindMatchingParen()
{
}

void CLogoCodeCtrl::SelectMatchingParen()
{
}

bool CLogoCodeCtrl::IsDirty() const
{
    return IsModified();
}

void CLogoCodeCtrl::OnDelete(wxCommandEvent& Event)
{
}

void CLogoCodeCtrl::OnHelpTopicSearch(wxCommandEvent& Event)
{
    ContextHelp(GetSelectedText());
}

bool CLogoCodeCtrl::CanSelectAll()
{
    return GetTextLength() != 0;
}

bool CLogoCodeCtrl::CanDelete()
{
    return IsTextSelected();
}

bool CLogoCodeCtrl::IsTextSelected()
{
    long from;
    long to;
    GetSelection(&from, &to);
    return from != to;
}


// Searches for StringToFind according to WxSearchFlags and the
// position of the current selection.
// Returns true if StringToFind is found and selects it.
// Returns false, otherwise.
bool
CLogoCodeCtrl::SearchForString(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind
    )
{
    long from;
    long to;
    GetSelection(&from, &to);

	FINDTEXTEXW findTextEx;
    findTextEx.chrg.cpMin     = (WxSearchFlags & wxFR_DOWN) ? to : from;
    findTextEx.chrg.cpMax     = -1;
    findTextEx.lpstrText      = (const wchar_t*)StringToFind;
    findTextEx.chrgText.cpMin = 0;
    findTextEx.chrgText.cpMax = -1;

    WPARAM wParam = 0;
    if (WxSearchFlags & wxFR_DOWN)
    {
        wParam |= FR_DOWN;
    }
    if (WxSearchFlags & wxFR_MATCHCASE)
    {
        wParam |= FR_MATCHCASE;
    }
    if (WxSearchFlags & wxFR_WHOLEWORD)
    {
        wParam |= FR_WHOLEWORD;
    }

    int position = SendMessage(
        GetHandle(),
        EM_FINDTEXTEXW,
        wParam,
        reinterpret_cast<LPARAM>(&findTextEx));

    if (position != -1)
    {
        SetSelection(findTextEx.chrgText.cpMin, findTextEx.chrgText.cpMax);
    }

    return position != -1;
}

void
CLogoCodeCtrl::ReplaceSelection(
    const wxString &   ReplacementString
    )
{
    // We use EM_REPLACESEL instead of wxTextEntry::Replace
    // so that the replacement is a single operation in the undo
    // buffer (not a delete followed by an insert).
    SendMessage(
        GetHandle(),
        EM_REPLACESEL,
        TRUE,
        (LPARAM)(const wchar_t*)(/*WXSTRING_TO_STRING*/(ReplacementString)));
}

void
CLogoCodeCtrl::Find(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind
    )
{
    bool isFound = SearchForString(WxSearchFlags, StringToFind);
    if (!isFound)
    {
        // Notify the user that we were unable to find it.
        const wxString & notFoundMessage = wxString::Format(
			wxString(LOCALIZED_STRINGTABLE_CANNOTFINDSTRING),
            StringToFind.c_str());

        ::wxMessageBox(
            notFoundMessage,
			wxString(LOCALIZED_GENERAL_PRODUCTNAME),
            wxICON_WARNING | wxOK,
            this);
    }
}

void
CLogoCodeCtrl::Replace(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    // We are doing a replace&find operation.
    // If the string to be replaced is currently selected, then replace it.
    const wxString & selectedText = GetSelectedText();

    // Now figure out what to do with it.
    int cmp;
    if (WxSearchFlags & wxFR_MATCHCASE)
    {
        // Do a case-sensitive comparison
        cmp = selectedText.Cmp(StringToFind);
    }
    else
    {
        // Do a case-insensitive comparison
        cmp = selectedText.CmpNoCase(StringToFind);
    }

    if (cmp == 0)
    {
        // This is a match.  Replace the string.
        ReplaceSelection(ReplacementString);
    }

    // Now that the replacement has been performed (or not), search for
    // the next occurence.
    Find(WxSearchFlags, StringToFind);
}

void
CLogoCodeCtrl::ReplaceAll(
    wxFindReplaceFlags WxSearchFlags,
    const wxString &   StringToFind,
    const wxString &   ReplacementString
    )
{
    SetInsertionPoint(0);

    bool isFound = SearchForString(WxSearchFlags, StringToFind);
    while (isFound)
    {
        // Found it.  Replace the string.
        ReplaceSelection(ReplacementString);

        // Move the selection so that we can repeat the search
        long from;
        long to;
        GetSelection(&from, &to);
        SetInsertionPoint(to);

        // Repeat the search
        isFound = SearchForString(WxSearchFlags, StringToFind);
    }
}

int CLogoCodeCtrl::FormatRange(
    bool    doDraw,
    int     startPos,
    int     endPos,
    wxDC *  draw,
    wxDC *  target,
    wxRect  renderRect,
    wxRect  pageRect 
    )
{
    wxCoord pageX      = renderRect.GetLeft();
    wxCoord nextY      = renderRect.GetTop();
    wxCoord pageYLimit = renderRect.GetBottom();

    // Draw the requested range, line by line.
    wxString remainingText(GetText());
    while (!remainingText.IsEmpty())
    {
        // Extract the next line from remainingText.
        wxString line;
        int lineEnd = remainingText.First(L'\n');
        if (lineEnd != wxNOT_FOUND)
        {
            line          = remainingText.Left(lineEnd + 1);
            remainingText = remainingText.Mid(lineEnd + 1);
        }
        else
        {
            line          = remainingText;
            remainingText = wxEmptyString;
        }

        // Determine how much vertical space this line take up.
        // Anything beyond the page extent is clipped (no line wrapping).
        wxCoord lineWidth;
        wxCoord lineHeight;
        draw->GetTextExtent(line, &lineWidth, &lineHeight);

        if (pageYLimit <= nextY + lineHeight)
        {
            // We have reached the end of the page before
            // printing all of the text.  Return how much
            // progress we made to the caller.
            return startPos;
        }

        // Determine the number of characters in the line, since
        // some wxWidgets functions do not correctly handle multibyte
        // character sets.
		int lineLength = line.length();

        if (doDraw)
        {

            TextOutW(draw->GetHDC(), pageX, nextY, (const wchar_t*)line, lineLength);

        }

        // Advance the Y to below the line.
        nextY += lineHeight;

        // Advance the start position to include the characters
        // which were drawn above.  wxString.Len() assumes that all
        // ANSI strings have single-byte characters, so to get the
        // correct position, we must use the length determined in characters.
        startPos += lineLength;
    }

    // We reached the end of the text.  Return the end of the requested
    // range, instead of the calculated startPos.  This compensates for a
    // problem that GetWindowTextLength returns bytes, instead of characters.
    return endPos;
}

BEGIN_EVENT_TABLE(CLogoCodeCtrl, wxTextCtrl)
    EVT_MENU(wxID_HELP_INDEX, CLogoCodeCtrl::OnHelpTopicSearch)
END_EVENT_TABLE()

// Even though this isn't used, without it, there's an unresolved external error
// 
// libwxscintilla-3.1-i686-w64-mingw32.a(wxscintilla_LexCoffeeScript.o): In function `FoldCoffeeScriptDoc':
// src/stc/scintilla/lexers/LexCoffeeScript.cxx:361: undefined reference to `Platform::Maximum(int, int)'
//
class Platform
{
    int Maximum(int a, int b);
};

int Platform::Maximum(int a, int b)
{
    return a > b ? a : b;
}

#endif
