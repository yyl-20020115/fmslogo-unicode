#include "pch.h"
#include "CNodePrinter.h"

wxString CNodePrinter::FormatDouble(double v, size_t cds)
{
start:

	//pr ((53+7.6)*8.7/6-93.2)*4
	wxString text = wxString::Format(L"%0.16g", v);
	if (text.length() > 0) {
		wxString fpart;
		wxString epart;
		size_t ple = text.find(L'e');
		ple = ple == text.npos ? text.find(L'E') : ple;
		if (ple != text.npos) {
			//there is e or E
			epart = text.substr(ple);
			text = text.substr(0, ple);
		}
		size_t pld = text.find(L'.');
		if (pld != text.npos) {
			fpart = text.substr(0, pld+1);
			text = text.substr(pld+1);
			if (text.length() > 0) {
				size_t plz = text.find_last_of(L'0');
				if (plz != text.npos) {
					size_t prz = text.find_last_not_of(L'0', plz);
					if (prz!=text.npos && (plz - prz >= cds)) {
						text = text.substr(0, prz+1);
					}
				}
				else {
					size_t pln = text.find_last_of(L'9');
					if (pln != text.npos) {
						size_t prn = text.find_last_not_of(L'9', pln);
						if (prn != text.npos && (pln - prn) >= cds) {
							if (pln < text.length() - 1) {
								text = text.substr(0, pln);
							}
							wchar_t d = text[text.length() - 1];							
							wchar_t m = (10 - (d - L'0'))+L'0';
							wxString adder = L"0.";
							for (size_t i = 0; i < pln; i++) {
								adder += L'0';
							}
							adder += m;
							double g = 0.0;
							swscanf(adder, L"%lf", &g);
							v += g;
							goto start;

						}
					}
				}
			}

		}
		text = fpart + text + epart;
	}
	return text;
}

CNodePrinter::CNodePrinter()
	:content()
	,bs(false)
{
}


CNodePrinter::~CNodePrinter()
{
}

wxString & CNodePrinter::Print(NODE * n)
{
	if (n != 0) {
		if (is_list(n))
		{
			this->PrintList(n);
		}
		else
		{
			this->PrintNode(n);
		}
	}
	return this->content;
}

void CNodePrinter::PrintChar(wchar_t ch)
{
	this->content.Append(ch);
}

void CNodePrinter::PrintSpace()
{
	this->PrintChar(L' ');
}

void CNodePrinter::NdPrintf(const wchar_t * fmt, ...)
{

	va_list ap;
	va_start(ap, fmt);

	wchar_t ch = 0;
	while ((ch = *fmt++) !=0)
	{
		if (ch == L'%')
		{
			ch = *fmt++;
			if (ch == L's') // show
			{
				this->Print(va_arg(ap, NODE *));
			}
			else if (ch == L'p')  // print
			{
				/* print */
				NODE * nd = va_arg(ap, NODE *);
				if (is_list(nd))
				{
					this->PrintList(nd);
				}
				else
				{
					this->PrintNode(nd);
				}
			}
			else if (ch == 't') // text
			{
				wchar_t *cp = va_arg(ap, wchar_t *);
				while ((ch = *cp++) != 0)
				{
					PrintChar( ch);
				}
			}
			else
			{
				PrintChar('%');
				PrintChar(ch);
			}
		}
		else
		{
			PrintChar(ch);
		}
	}

	va_end(ap);
}

void CNodePrinter::NewLine()
{
	this->PrintChar(L'\n');
}

void  CNodePrinter::PrintList(const NODE *ndlist)
{
	if (ndlist != NIL && is_list(ndlist))
	{
		this->PrintChar(L'(');
		NODE * arg = car(ndlist);
		this->PrintNode(arg);

		ndlist = cdr(ndlist);

		if (ndlist != NIL)
		{
			this->PrintSpace();
		}
		this->PrintList(ndlist);
		this->PrintChar(L')');
	}
}
extern NODE* Unbound;
extern wchar_t ecma_set(int ch);
extern wchar_t ecma_clear(int ch);
extern bool ecma_get(int ch);
extern bool is_special_character(wchar_t ch);
// Prints a node to a file stream in a way that is consistent
// with how FMSLogo parses nodes.
//
//   strm - the file stream.
//   type - the type of message that is being printed
//   nd - the node to print
//   depth - how "deep" to go (how many elements of a list)
//   width - how many bytes to print at most ???
void CNodePrinter::PrintNode(const NODE * nd)
{
	NODETYPES ndty = 0;

	this->PrintChar(L'<');

	if (nd == NIL)
	{
		this->PrintChar(L'[');
		this->PrintChar(L']');
	}
	else if (nd == Unbound)
	{
		this->NdPrintf(L"LOCALIZED_UNBOUND");
	}
	else if ((ndty = nodetype(nd)) & NT_PRIM)
	{
		this->NdPrintf(L"PRIM");
	}
	else if (ndty & NT_LIST)
	{
		this->PrintChar(L'[');
		this->PrintList(nd);
		this->PrintChar(L']');
	}
	else if (ndty == ARRAY)
	{
		int dim = getarrdim(nd);

		this->PrintChar(L'{');

		// print each item in the array
		NODE **pp = getarrptr(nd);
		int i = 0;
		do
		{
			this->PrintNode( *pp++);
			if (++i < dim)
			{
				this->PrintSpace();
			}
		} while (i < dim);

		this->PrintChar(L'}');

		// print the origin
		if (this->GetBackslashSetting() && (getarrorg(nd) != 1))
		{

			this->NdPrintf(L"@%d", getarrorg(nd));
		}
	}
	else if (ndty == QUOTE)
	{
		this->PrintChar(L'\"');
		this->PrintNode(car(nd));
	}
	else if (ndty == COLON)
	{
		this->PrintChar(L':');
		this->PrintNode( car(nd));
	}
	else if (ndty == FLOATINGPOINT)
	{
		wxString buffer = FormatDouble(getfloat(nd));
		// REVISIT: is it okay to ignore the width parameter?
		for (size_t i = 0; i < buffer.length(); i++)
		{
			this->PrintChar(buffer[i]);
		}
	}
	else if (ndty == INTEGER)
	{
		wxString buffer = wxString::Format(L"%ld", getint(nd));
		// REVISIT: is it okay to ignore the width parameter?
		for (size_t i = 0; i < buffer.length(); i++)
		{
			this->PrintChar(buffer[i]);
		}
	}
	else if (ndty == CASEOBJ)
	{
		this->PrintNode(strnode__caseobj(nd));
	}
	else
	{
		assert(is_string(nd));

		// figure out how many charaters to print
		int totalCharsToPrint= getstrlen(nd);

		// print totalCharsToPrint characters of nd
		const wchar_t *cp = getstrptr(nd);
		if (!backslashed(nd))
		{
			for (int i = 0; i < totalCharsToPrint; i++)
			{
				this->PrintChar(*cp++);
			}
		}
		else if (!this->GetBackslashSetting())
		{
			for (int i = 0; i < totalCharsToPrint; i++)
			{
				this->PrintChar(ecma_clear(*cp++));
			}
		}
		else
		{
			// determine if the word was in vbars
			int i;
			for (i = 0; i < totalCharsToPrint; i++)
			{
				if (ecma_get(cp[i]))
				{
					break;
				}
			}

			if (i < totalCharsToPrint)
			{
				// word was in vbars
				if (wcschr(L"\":", *cp))
				{
					this->PrintChar( *cp++);
					totalCharsToPrint--;
				}
				this->PrintChar(L'|');
				for (i = 0; i < totalCharsToPrint; i++)
				{
					wchar_t ch = ecma_clear(*cp++);

					// Even in vbars, there are some characters
					// that must be escaped.
					if (ch == L'|' || ch == L'\\')
					{
						this->PrintChar( L'\\');
					}
					this->PrintChar(ch);
				}
				this->PrintChar( L'|');
			}
			else
			{
				// word was not in vbars
				for (i = 0; i < totalCharsToPrint; i++)
				{
					if (is_special_character(*cp))
					{
						// *cp must be escaped with a backslash
						PrintChar('\\');
					}
					this->PrintChar(*cp++);
				}
			}
		}
	}
	this->PrintChar('>');
}
