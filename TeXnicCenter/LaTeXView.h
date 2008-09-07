#pragma once

#include "LaTeXViewBase.h"

class CAdvice;
class CAutoCompleteDlg;
class LaTeXViewListener;
class LaTeXDocument;
class CLaTeXCommand;
class DocumentTokenizer;

class LaTeXView : 
	public LaTeXViewBase
{
	friend class LaTeXViewListener;

	DECLARE_DYNCREATE(LaTeXView)

	long old_pos_start_, old_pos_end_;

protected:
	LaTeXView();           // protected constructor used by dynamic creation
	virtual ~LaTeXView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
    
	virtual void OnInitialUpdate();

public:
	void UpdateSettings();

protected:
    void OnCharAdded(SCNotification* n);

private:	
	void OnACBackspace();
	void OnACChar(UINT nKey,UINT nRepCount,UINT nFlags);
	void OnACCommandCancelled();
	void OnACCommandSelect(const CLaTeXCommand* cmd);

	void Reindent( int initial_line_count, int start_line );
	void OnACHelp(const CString &cmd);	

private:
	CAutoCompleteDlg* CreateListBox(CString &keyword, long pos);
	void InstantAdvice();
	void HideAdvice();

	CAdvice* instant_advice_tip_;
	CAutoCompleteDlg* autocompletion_list_;
	LaTeXViewListener *listener_;
	bool autocompletion_active_;

protected:
	void GetWordBeforeCursor(CString& strKeyword, long& start,bool bSelect = true);
	static bool IsAutoCompletionCharacter(TCHAR tc);
	
	
	afx_msg void OnEditOutsource();
	afx_msg void OnQueryCompletion();
	afx_msg BOOL OnInsertLaTeXConstruct(UINT nID);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnModified(SCNotification* n);
	afx_msg BOOL OnBlockComment(UINT nID);
	afx_msg void OnFormatTextForeColor();
	afx_msg void OnFormatTextBackColor();
	afx_msg void OnUpdateFormatTextForeColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatTextBackColor(CCmdUI* pCmdUI);

private:
	void RestoreFocus();
	BOOL InvokeContextHelp(const CString& keyword);

public:	
	LaTeXDocument* GetDocument() const;
	int GetNumberOfMatches(const CString& keyword);	

protected:
	DocumentTokenizer* NewDocumentTokenizer() const;
	void OnSettingsChanged(void);
};
