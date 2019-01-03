#include "CNodePrinter.h"



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
		wxString buffer = wxString::Format(L"%0.15g", getfloat(nd));
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
