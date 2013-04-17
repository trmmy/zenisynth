
#ifndef _WIN32_WINNT		// Windows XP 以降のバージョンに固有の機能の使用を許可します。                   
#define _WIN32_WINNT 0x0501	// これを Windows の他のバージョン向けに適切な値に変更してください。
#endif						

#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーから使用されていない部分を除外します。

#include <windows.h>

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#pragma comment(lib,"lua5.1.lib")

#include <iostream>
#include <process.h>
#include <sstream>
#include <complex>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include <zenisynth.h>


void _addLog(std::wstring&){}
ZSLogFunction addLog=&_addLog;

#define out(expr) {\
	std::wstringstream str;\
	str<<__FILE__<<" : "<<__LINE__<<" > "<<expr<<"\r\n";\
	addLog(str.str());\
	}

bool g_threadActive=false;
bool g_threadExitSign=false;

BOOL APIENTRY DllMain( HMODULE,
                       DWORD  reason,
                       LPVOID
					 )
{
	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
			timeBeginPeriod(1);
			break;
		case DLL_PROCESS_DETACH:
			//MessageBox(NULL,L"detached",L"detached",MB_OK);
			g_threadExitSign=true;
			timeEndPeriod(1);
			break;
	}

    return TRUE;
}

struct Vector2D : public std::complex<double>
{
	Vector2D(const double newx,const double newy):std::complex<double>(newx,newy){}
	Vector2D(const std::complex<double> newv):std::complex<double>(newv){}
	virtual const double x() const {return real();}
	virtual const double y() const {return imag();}
	virtual const double x(const double newx) { return real(newx);}
	virtual const double y(const double newy) { return imag(newy);}
};
struct PointPhysics
{

	PointPhysics()
		:dt(0),m(1),mu(500),v(0,0),f(0,0),pos(0,0),lastTime(timeGetTime())
	{}
	double dt;
	double m;
	double mu;
	Vector2D v;
	Vector2D f;
	Vector2D pos;
	void advance()
	{
		const DWORD nowTime=timeGetTime();
		dt=((double)(nowTime-lastTime))/1000.0;
		
		//F=mu*m :. a=(mu*m)/m=mu

		const Vector2D a=f/m;
		const Vector2D v0=v;
		v=v0+a*dt;

		//apply mu
		const Vector2D v_mued=v+Vector2D(mu*-sign(v.x()),mu*-sign(v.y()))*dt;
		const Vector2D sign_v_vs_mu(
			 sign(v).x()*sign(v_mued).x()
			,sign(v).y()*sign(v_mued).y());
		if		(sign_v_vs_mu.x()==-1){v.x(0);}	//if left-> right or right->left
		else if	(sign_v_vs_mu.x()==1){v.x(v_mued.x());}	//if left->left or right->right
		else{v.x(0);}	//if move->stop or stop->move by mu
		if		(sign_v_vs_mu.y()==-1){v.y(0);}
		else if	(sign_v_vs_mu.y()==1){v.y(v_mued.y());}
		else{v.y(0);}

		pos=v*dt;
		
		lastTime=nowTime;
	}
private:
	int sign(const double n)
	{
		if(n<0){return -1;}
		if(0<n){return 1;}
		return 0;
	}
	Vector2D sign(const Vector2D& in)
	{
		return Vector2D(sign(in.x()),sign(in.y()));
	}
	DWORD lastTime;
};

PointPhysics g_cursor;

void cullCursor()
{
	POINT currentCursorPos;
	GetCursorPos(&currentCursorPos);
	const Vector2D nextCursorPos=Vector2D(currentCursorPos.x,currentCursorPos.y)+g_cursor.pos;
	RECT rcAll;
	{
		POINT topLeft={-200000,-200000};
		HMONITOR hMonitor= MonitorFromPoint(topLeft,MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi;	mi.cbSize=sizeof(mi);
		GetMonitorInfo(hMonitor,&mi);
		rcAll.top=mi.rcMonitor.top;
		rcAll.left=mi.rcMonitor.left;
	}
	{
		POINT bottomRight={200000,200000};
		HMONITOR hMonitor= MonitorFromPoint(bottomRight,MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi;	mi.cbSize=sizeof(mi);
		GetMonitorInfo(hMonitor,&mi);
		rcAll.bottom=mi.rcMonitor.bottom;
		rcAll.right=mi.rcMonitor.right;
	}
}

void cursorThread(void*)
{
	out("Cursor thread OK");

	g_threadActive=true;

	for(;g_threadExitSign==false;)
	{
		g_cursor.advance();
			INPUT i;	ZeroMemory(&i,sizeof(i));
			i.type=INPUT_MOUSE;
			{
				MOUSEINPUT m; ZeroMemory(&m,sizeof(m));
				m.dx=static_cast<LONG>(g_cursor.pos.x());
				m.dy=static_cast<LONG>(g_cursor.pos.y());
				g_cursor.pos-=Vector2D(m.dx,m.dy);
				m.dwFlags=MOUSEEVENTF_MOVE;
				m.dwExtraInfo=GetMessageExtraInfo();

				i.mi=m;
				if((m.dx!=0)||(m.dy!=0))
				{
					SendInput(1,&i,sizeof(i));
				}
			}
		Sleep(16);
	}
	g_threadActive=false;
	_endthread();
}

ZSExport OnLoad(ZSLogFunction newAddLog)
{
	addLog=newAddLog;
	if(g_threadActive==false)
	{
		_beginthread(&cursorThread,NULL,NULL);
	}
	else
	{
		out("Thread is already running");
	}
	return TRUE;
}

ZSExport setCursorForce(lua_State* L)
{
	CheckArg(2)
	{
		switch(lua_type(L,1))
		{
			case LUA_TNUMBER:
				g_cursor.f.x(lua_tonumber(L,1));
			break;
			default:
				out("not a number: "<<lua_type(L,1));
			break;
		}
		switch(lua_type(L,2))
		{
			case LUA_TNUMBER:
				g_cursor.f.y(lua_tonumber(L,2));
			break;
			default:
				out("not a number: "<<lua_type(L,2));
			break;
		}
	}
	return 0;
}
ZSExport setCursorForceX(lua_State* L)
{
	CheckArg(1)
	{
		g_cursor.f.x(lua_tonumber(L,1));
	}
	return 0;
}
ZSExport setCursorForceY(lua_State* L)
{
	CheckArg(1)
	{
		g_cursor.f.y(lua_tonumber(L,1));
	}
	return 0;
}
ZSExport setCursorFriction(lua_State* L)
{
	CheckArg(1)
	{
		g_cursor.mu=lua_tonumber(L,1);
	}
	return 0;
}

ZSExport button(lua_State* L)
{
	CheckArg(2)
	{
		const WORD VK=static_cast<WORD>(lua_tonumber(L,1));

		const bool UP=static_cast<bool>(lua_toboolean(L,2));
		MOUSEINPUT m;	ZeroMemory(&m,sizeof(m));

		switch(VK)
		{
			case VK_LBUTTON:
				m.dwFlags=UP?MOUSEEVENTF_LEFTUP:MOUSEEVENTF_LEFTDOWN;
				break;
			case VK_RBUTTON:
				m.dwFlags=UP?MOUSEEVENTF_RIGHTUP:MOUSEEVENTF_RIGHTDOWN;
				break;
			case VK_MBUTTON:
				m.dwFlags=UP?MOUSEEVENTF_MIDDLEUP:MOUSEEVENTF_MIDDLEDOWN;
				break;
			case VK_XBUTTON1:
				m.dwFlags=UP?MOUSEEVENTF_XUP:MOUSEEVENTF_XDOWN;
				m.mouseData=XBUTTON1;
				break;
			case VK_XBUTTON2:
				m.dwFlags=UP?MOUSEEVENTF_XUP:MOUSEEVENTF_XDOWN;
				m.mouseData=XBUTTON2;
				break;
			default:
				break;
		}

		INPUT i;
		i.type=INPUT_MOUSE;
		i.mi=m;

		SendInput(1,&i,sizeof(i));
	}
	return 0;
}

ZSExport wheel(lua_State* L)
{
	CheckArg(1)
	{
		MOUSEINPUT m;	ZeroMemory(&m,sizeof(m));
		m.dwFlags=MOUSEEVENTF_WHEEL;
		m.mouseData=static_cast<DWORD>(lua_tointeger(L,1));
		INPUT i;	i.type=INPUT_MOUSE;
		i.mi=m;
		SendInput(1,&i,sizeof(i));
	}
	return 0;
}