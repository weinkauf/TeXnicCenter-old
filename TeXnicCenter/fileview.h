/********************************************************************
 *
 * This file is part of the TeXnicCenter-system
 *
 * Copyright (C) 1999-2000 Sven Wiegand
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

/********************************************************************
 *
 * $Id$
 *
 ********************************************************************/

#if !defined(AFX_FILEVIEW_H__0EE022A2_20D1_11D3_929E_DA6C20A3421F__INCLUDED_)
#define AFX_FILEVIEW_H__0EE022A2_20D1_11D3_929E_DA6C20A3421F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileView.h : Header-Datei
//
#include "NavigatorView.h"

class CFileView : public NavigatorTreeCtrl {
    CFont bold_;
    //	DECLARE_DYNCREATE(CFileView)

    // construction/destruction
public:
    CFileView();
    virtual ~CFileView();

    // operations
public:

    // overridings
protected:
    virtual void OnUpdate(CProjectView* pSender, LPARAM lHint, LPVOID pHint);
    //{{AFX_VIRTUAL(CFileView)
protected:
    //}}AFX_VIRTUAL

    // implementation helpers
protected:

    // message handlers
protected:
    //{{AFX_MSG(CFileView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // attributes
protected:
public:
    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
protected:
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_FILEVIEW_H__0EE022A2_20D1_11D3_929E_DA6C20A3421F__INCLUDED_
