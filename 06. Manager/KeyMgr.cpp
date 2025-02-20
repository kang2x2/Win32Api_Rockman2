#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(&m_bKeyState, sizeof(m_bKeyState));
}


CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	// 이전에 눌린 적이 없고, 지금 눌렸을 때
	if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_InvenDown()
{
	if (!m_bKeyState['I'] && (GetAsyncKeyState('I') & 0x8000))
	{
		m_bKeyState['I'] = !m_bKeyState['I'];
		return true;
	}

	if (m_bKeyState['I'] && !(GetAsyncKeyState('I') & 0x8000))
		m_bKeyState['I'] = !m_bKeyState['I'];

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	// 이전에 눌린 적이 있고, 현재는 눌리지 않은 경우
	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Test()
{
	if (!m_bKeyState['T'] && (GetAsyncKeyState('T') & 0x8000))
	{
		m_bKeyState['T'] = !m_bKeyState['T'];
		return true;
	}

	if (m_bKeyState['T'] && !(GetAsyncKeyState('T') & 0x8000))
		m_bKeyState['T'] = !m_bKeyState['T'];

	return false;
}

