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

#include "stdafx.h"
#include "DdeCommand.h"
#include "PlaceHolder.h"
#include "Process.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


HDDEDATA CALLBACK CDdeCommand_DDEProcessMessage(UINT uType,     // transaction type
  UINT uFmt,      // clipboard data format
  HCONV hconv,    // handle to the conversation
  HSZ hsz1,       // handle to a string  HSZ hsz2,       // handle to a string
  HDDEDATA hdata, // handle to a global memory object
  DWORD dwData1,  // transaction-specific data
  DWORD dwData2   // transaction-specific data
)
{
	return NULL;  //Not doing anything in particular!!!
}


//-------------------------------------------------------------------
// class CDdeCommand
//-------------------------------------------------------------------

CDdeCommand::CDdeCommand()
:	m_strTopic(_T("System"))
{}


CDdeCommand::~CDdeCommand()
{}


void CDdeCommand::SetExecutable(LPCTSTR lpszPath)
{
	m_strExecutable = lpszPath;
}


void CDdeCommand::SetServer(LPCTSTR lpszServerName, LPCTSTR lpszTopic /*= _T("System")*/)
{
	ASSERT(lpszServerName && lpszTopic);

	m_strServerName = lpszServerName;
	m_strTopic = lpszTopic;
}


void CDdeCommand::SetCommand(LPCTSTR lpszCmd)
{
	ASSERT(lpszCmd);

	m_strCmd = lpszCmd;
}


BOOL CDdeCommand::SendCommand(LPCTSTR lpszMainPath, 
															LPCTSTR lpszCurrentPath /*= NULL*/, long lCurrentLine /*= -1*/) const
{
	return SendCommand(
		m_strServerName, 
		AfxExpandPlaceholders(m_strCmd, lpszMainPath, lpszCurrentPath, lCurrentLine), 
		m_strTopic,
		m_strExecutable.IsEmpty()? (LPCTSTR)NULL : (LPCTSTR)m_strExecutable);
}


BOOL CDdeCommand::SendCommand(LPCTSTR lpszServer, LPCTSTR lpszCommand, LPCTSTR lpszTopic /*= _T("System")*/, LPCTSTR lpszExecutable /*= NULL*/)
{
	if (SendCommandHelper(lpszServer, lpszCommand, lpszTopic))
		return TRUE;

	if (!lpszExecutable)
		return FALSE;

	// try to start the executable
	CProcess	p;
	if (!p.Create(lpszExecutable))
		return FALSE;

	// wait for process to finish initialization
	WaitForInputIdle(p.GetProcessHandle(), INFINITE);

	// try again to send the command
	return SendCommandHelper(lpszServer, lpszCommand, lpszTopic);
}


BOOL CDdeCommand::SendCommandHelper(LPCTSTR lpszServer, LPCTSTR lpszCommand, LPCTSTR lpszTopic)
{
	ASSERT(lpszServer && lpszCommand && lpszTopic);

	DWORD	dwId = 0;

	if (DdeInitialize(&dwId, (PFNCALLBACK)CDdeCommand_DDEProcessMessage, APPCMD_CLIENTONLY, 0) != DMLERR_NO_ERROR)
		return FALSE;

	HSZ		hszServerName = NULL;
	HSZ		hszTopic = NULL;
	HCONV	hConversation = NULL;
	char	*szCommand = NULL;

	try
	{
		// create handles
		hszServerName = DdeCreateStringHandle(dwId, lpszServer, 0);
		if (!hszServerName)
			throw FALSE;
		hszTopic = DdeCreateStringHandle(dwId, lpszTopic, 0);
		if (!hszTopic)
			throw FALSE;

		// establish conversation
		hConversation = DdeConnect(dwId, hszServerName, hszTopic, NULL);
		if (!hConversation)
			throw FALSE;

		// ensure byte string
		int		nLen = _tcslen(lpszCommand);
		szCommand = new char[nLen+1];
		if (!szCommand)
			throw FALSE;
		for (int i = 0; i <= nLen+1; i++)
			szCommand[i] = (char)lpszCommand[i];

		// send command
		if (!DdeClientTransaction((LPBYTE)szCommand, nLen+1, hConversation, NULL, 0, XTYP_EXECUTE, 1000, NULL))
			throw FALSE;

		// clean up
		delete[] szCommand;
		DdeDisconnect(hConversation);
		DdeFreeStringHandle(dwId, hszServerName);
		DdeFreeStringHandle(dwId, hszTopic);
		DdeUninitialize(dwId);
	}
	catch (...)
	{
		if (szCommand)
			delete[] szCommand;
		if (hConversation)
			DdeDisconnect(hConversation);
		if (hszServerName)
			DdeFreeStringHandle(dwId, hszServerName);
		if (hszTopic)
			DdeFreeStringHandle(dwId, hszTopic);
		DdeUninitialize(dwId);

		return FALSE;
	}

	// successfull
	return TRUE;
}


CString CDdeCommand::SerializeToString() const
{
	return m_strServerName + _T('\n') + m_strTopic + _T('\n') + m_strCmd + _T('\n') + m_strExecutable;
}


BOOL CDdeCommand::SerializeFromString(LPCTSTR lpszPackedInformation)
{
	CString	strServerName, strTopic, strCmd, strExecutable;
	if (!AfxExtractSubString(strServerName, lpszPackedInformation, 0, _T('\n')))
		return FALSE;
	if (!AfxExtractSubString(strTopic, lpszPackedInformation, 1, _T('\n')))
		return FALSE;
	if (!AfxExtractSubString(strCmd, lpszPackedInformation, 2, _T('\n')))
		return FALSE;
	AfxExtractSubString(strExecutable, lpszPackedInformation, 3, _T('\n'));

	SetExecutable(strExecutable);
	SetServer(strServerName, strTopic);
	SetCommand(strCmd);
	return TRUE;
}