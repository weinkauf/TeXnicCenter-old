/********************************************************************
 *
 * This file is part of the TeXnicCenter-system
 *
 * Copyright (C) 2002 Chris Norris
 * Copyright (C) 2000-$CurrentYear$ ToolsCenter
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * If you have further questions or if you want to support
 * further TeXnicCenter development, visit the TeXnicCenter-homepage
 *
 *    http://www.ToolsCenter.org
 *
 *********************************************************************/

// SpellCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpellCheckDlg.h"

#include <algorithm>

#include "CCrystalEditView.h"
#include "CCrystalTextBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpellCheckDlg dialog

CSpellCheckDlg::CSpellCheckDlg(CCrystalEditView *pBuddy, Speller *pSpell, CWnd* pParent /*= NULL*/)
		: CDialog(CSpellCheckDlg::IDD, pParent)
{
	if (pBuddy != NULL)
		Reset(pBuddy, pSpell);

	m_bSelection = true;
	m_bDoneMessage = true;
	m_bEditing = false;

	//{{AFX_DATA_INIT(CSpellCheckDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSpellCheckDlg::~CSpellCheckDlg()
{
}

void CSpellCheckDlg::Reset(CCrystalEditView *pBuddy, Speller *pSpell)
{
	VERIFY(m_pBuddy = pBuddy);
	VERIFY(m_pTextBuffer = pBuddy->LocateTextBuffer());
	VERIFY(m_pParser = m_pBuddy->GetParser());
	m_pSpell = pSpell;
}

void CSpellCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpellCheckDlg)
	DDX_Control(pDX, IDC_SPELL_SUGGEST, c_SuggestList);
	DDX_Control(pDX, IDC_SPELL_TEXT, c_Text);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpellCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CSpellCheckDlg)
	ON_BN_CLICKED(IDC_SPELL_IGNORE, OnSpellIgnore)
	ON_BN_CLICKED(IDC_SPELL_IGNORE_ALL, OnSpellIgnoreAll)
	ON_BN_CLICKED(IDC_SPELL_NEXT, OnSpellNext)
	ON_EN_CHANGE(IDC_SPELL_TEXT, OnChangeSpellText)
	ON_BN_CLICKED(IDC_SPELL_RESUME, OnSpellResume)
	ON_BN_CLICKED(IDC_SPELL_REPLACE, OnSpellReplace)
	ON_NOTIFY(NM_DBLCLK, IDC_SPELL_SUGGEST, OnDblclkSpellSuggest)
	ON_BN_CLICKED(IDC_SPELL_ADD, OnSpellAdd)
	ON_BN_CLICKED(IDC_SPELL_REPLACE_ALL, OnSpellReplaceAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpellCheckDlg message handlers

void CSpellCheckDlg::OnSpellIgnore()
{
	if (m_bEditing)
	{
		// Unedit
		m_bEditing = false;
		m_bNewLine = true;
		CString label;
		label.LoadString(IDS_SPELL_IGNORE);
		GetDlgItem(IDC_SPELL_IGNORE)->SetWindowText(label);
		GetDlgItem(IDC_SPELL_IGNORE)->Invalidate();
		OnSpellError();
	}
	else
	{
		// Ignore
		m_nCurStart = m_nCurEnd;
		DoNextWord();
		OnSpellError();
	}
}

void CSpellCheckDlg::OnSpellIgnoreAll()
{
	m_pSpell->ignore(m_pWordBuffer);
	m_pBuddy->OnEditOperation(CE_ACTION_UNKNOWN, NULL);
	m_nCurStart = m_nCurEnd;
	DoNextWord();
	OnSpellError();
}

void CSpellCheckDlg::OnSpellAdd()
{
	m_pSpell->add(m_pWordBuffer);
	m_pBuddy->OnEditOperation(CE_ACTION_UNKNOWN, NULL);
	m_nCurStart = m_nCurEnd;
	DoNextWord();
	OnSpellError();
}

void CSpellCheckDlg::OnSpellNext()
{
	m_nCurStart = m_nCurEnd = 0;
	++m_nCurLine;
	m_bNewLine = true;

	DoNextWord();
	OnSpellError();
}

BOOL CSpellCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (m_pBuddy == NULL || m_pSpell == NULL)
		return TRUE;

	if (m_pBuddy->IsSelection() && m_bSelection)
	{
		m_pBuddy->GetSelection(m_ptStart, m_ptEnd);
	}
	else
	{
		m_ptStart.x = m_ptStart.y = 0;
		m_ptEnd.y = m_pTextBuffer->GetLineCount() - 1;
		m_ptEnd.x = m_pTextBuffer->GetLineLength(m_ptEnd.y);
	}
	m_nCurLine = m_ptStart.y;
	m_nCurStart = m_nCurEnd = m_ptStart.x;
	m_bNewLine = true;

	// Select the first word
	DoNextWord();
	OnSpellError();
	return FALSE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSpellCheckDlg::DoNextWord()
{
	while (m_nCurLine < m_ptEnd.y || (m_nCurLine == m_ptEnd.y && m_nCurEnd < m_ptEnd.x))
	{
		m_pParser->NextWord(m_nCurLine, m_nCurStart, m_nCurEnd);
		LPCTSTR szLine = m_pTextBuffer->GetLineChars(m_nCurLine);

		while (m_nCurStart != -1)
		{
			if (abs(m_nCurStart - m_nCurEnd) < MAXWORDLEN)
			{
				int i = m_nCurStart;
				int j = 0;
				// Convert string to TCHAR*
				while (i < m_nCurEnd)
					m_pWordBuffer[j++] = szLine[i++];

				m_pWordBuffer[j] = 0;

				if (!m_pSpell->spell(m_pWordBuffer))
				{
					m_pBuddy->HighlightText(CPoint(m_nCurStart, m_nCurLine), m_nCurEnd - m_nCurStart);
					return;
				}
			}

			// else the word was too long, skip it
			m_nCurStart = m_nCurEnd;
			m_pParser->NextWord(m_nCurLine, m_nCurStart, m_nCurEnd);
		}

		// next line
		++m_nCurLine;
		m_bNewLine = true;
		m_nCurStart = m_nCurEnd = 0;
	}

	// We are done
	if (m_bDoneMessage)
		AfxMessageBox(IDS_SPELL_DONE, MB_OK | MB_ICONINFORMATION);

	OnOK();
}

void CSpellCheckDlg::OnSpellError()
{

	if (!(m_nCurLine < m_ptEnd.y || (m_nCurLine == m_ptEnd.y && m_nCurEnd < m_ptEnd.x)))
		return;

	if (m_bNewLine)
	{
		c_Text.SetWindowText(m_pTextBuffer->GetLineChars(m_nCurLine));
		m_bNewLine = false;
	}
	c_Text.SetSel(m_nCurStart, m_nCurEnd);
	c_Text.SetFocus();
	c_Text.Invalidate();

	c_SuggestList.DeleteAllItems();

	CStringArray ssList;
	int nCount = m_pSpell->suggest(m_pWordBuffer,ssList);

	if (nCount < 1)
	{
		m_bNoSuggestions = true;
		CString label;
		label.LoadString(IDS_SPELL_NO_SUGGESTIONS);
		VERIFY(c_SuggestList.InsertItem(0, label) != -1);
	}
	else
	{
		USES_CONVERSION;

		m_bNoSuggestions = false;

		for (int i = 0; i < nCount; ++i)
		{
			VERIFY(c_SuggestList.InsertItem(i, ssList[i]) != -1);
		}
	}

	c_SuggestList.EnableWindow(!m_bNoSuggestions);
	GetDlgItem(IDC_SPELL_REPLACE)->EnableWindow(!m_bNoSuggestions);
	GetDlgItem(IDC_SPELL_REPLACE_ALL)->EnableWindow(!m_bNoSuggestions);
}

void CSpellCheckDlg::OnChangeSpellText()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// The user has taken control of the line. Disable all the controls except
	// Cancel, Resume, and Unedit / Ignore.
	if (!m_bEditing)
	{
		m_bEditing = true;
		c_SuggestList.EnableWindow(false);
		GetDlgItem(IDC_SPELL_IGNORE_ALL)->EnableWindow(false);
		GetDlgItem(IDC_SPELL_REPLACE)->EnableWindow(false);
		GetDlgItem(IDC_SPELL_REPLACE_ALL)->EnableWindow(false);
		GetDlgItem(IDC_SPELL_NEXT)->EnableWindow(false);
		GetDlgItem(IDC_SPELL_RESUME)->EnableWindow(true);

		CString label;
		label.LoadString(IDS_SPELL_UNEDIT);
		GetDlgItem(IDC_SPELL_IGNORE)->SetWindowText(label);
		GetDlgItem(IDC_SPELL_IGNORE)->Invalidate();
	}
}

void CSpellCheckDlg::OnSpellResume()
{
	ASSERT(m_bEditing);
	m_bEditing = false;

	GetDlgItem(IDC_SPELL_IGNORE_ALL)->EnableWindow(true);
	GetDlgItem(IDC_SPELL_NEXT)->EnableWindow(true);
	GetDlgItem(IDC_SPELL_RESUME)->EnableWindow(false);
	CString label;
	label.LoadString(IDS_SPELL_IGNORE);
	GetDlgItem(IDC_SPELL_IGNORE)->SetWindowText(label);

	// Find the first change position
	CString newText;
	c_Text.GetWindowText(newText);
	int start = FirstDifference(m_pTextBuffer->GetLineChars(m_nCurLine), newText);
	if (start != -1)
	{
		int endOld, endNew;
		LastDifference(m_pTextBuffer->GetLineChars(m_nCurLine), endOld, newText, endNew);
		++endOld; // point one past last difference
		++endNew; // point one past last difference
		LPTSTR szNewText = newText.GetBuffer(0);
		szNewText[endNew] = _T('\0');
		m_pBuddy->HighlightText(CPoint(start, m_nCurLine), endOld - start);
		VERIFY(m_pBuddy->ReplaceSelection(&szNewText[start]));
		newText.ReleaseBuffer(0);
		m_nCurStart = m_nCurEnd = 0;
	}
	// else no change was made
	DoNextWord();
	OnSpellError();
}

void CSpellCheckDlg::OnSpellReplace()
{
	// Get the selected suggestion text
	POSITION pos = c_SuggestList.GetFirstSelectedItemPosition();
	if (!pos)
		return;

	CString newText = c_SuggestList.GetItemText(c_SuggestList.GetNextSelectedItem(pos), 0);

	VERIFY(m_pBuddy->ReplaceSelection(newText));
	DoNextWord();
	OnSpellError();
}

void CSpellCheckDlg::OnSpellReplaceAll()
{
	// Get the selected suggestion text
	POSITION pos = c_SuggestList.GetFirstSelectedItemPosition();
	if (!pos)
		return;

	CString newText = c_SuggestList.GetItemText(c_SuggestList.GetNextSelectedItem(pos), 0);
	CString oldText = CString(m_pWordBuffer);

	CPoint ptFound(m_ptStart);

	while (m_pBuddy->FindTextInBlock(oldText, m_ptStart, ptFound, m_ptEnd, FIND_MATCH_CASE, FALSE, &ptFound))
	{
		m_pBuddy->HighlightText(ptFound, oldText.GetLength());
		VERIFY(m_pBuddy->ReplaceSelection(newText));

		// Ensure that we do not find the same thing again
		ptFound.x += newText.GetLength();
	}

	DoNextWord();
	OnSpellError();
}

void CSpellCheckDlg::OnDblclkSpellSuggest(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnSpellReplace();
	*pResult = 0;
}

int CSpellCheckDlg::DoModal()
{
	if (m_pSpell == NULL)
		return IDABORT;

	return CDialog::DoModal();
}

