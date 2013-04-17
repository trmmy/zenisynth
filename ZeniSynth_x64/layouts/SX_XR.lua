function ScanRepeat(scan,count)
	time=2
	if count>20 then time=3 end
	if count>30 then time=6 end
	for i=1,time do
		sendScan(scan,false)
		sendScan(scan,true)
	end
end

function SX.XR()

	if SCAN==SC_XR and UP and ONESHOT then
		system.setIMEStatus(true)
	end

	if XR then
		THRESHOLD=7
		if SCAN==SC_E then
			if RCOUNT>THRESHOLD then
				ScanRepeat(SC_UP,RCOUNT)
			else
				sendScan(SC_UP,UP)
			end
			return true
		elseif SCAN==SC_D then
			if RCOUNT>THRESHOLD then
				ScanRepeat(SC_DOWN,RCOUNT)
			else
				sendScan(SC_DOWN,UP)
			end
			return true
		elseif SCAN==SC_S then
			if RCOUNT>THRESHOLD then
				ScanRepeat(SC_LEFT,RCOUNT)
			else
				sendScan(SC_LEFT,UP)
			end
			return true
		elseif SCAN==SC_F then
			if RCOUNT>THRESHOLD then
				ScanRepeat(SC_RIGHT,RCOUNT)
			else
				sendScan(SC_RIGHT,UP)
			end
			return true
		
		elseif SCAN==SC_SEMICOLON then sendScan(SC_ENTER,UP) return true
		elseif SCAN==SC_XR then
			return true
		elseif SCAN==SC_X then sendScan(SC_QUOTE,UP) return true
		
		elseif SCAN==SC_J then sendScan(SC_DELETE,UP) return true
		elseif SCAN==SC_I then sendScan(SC_HOME,UP) return true
		elseif SCAN==SC_K then sendScan(SC_END,UP) return true
		elseif SCAN==SC_O then sendScan(SC_PAGEUP,UP) return true
		elseif SCAN==SC_L then sendScan(SC_PAGEDOWN,UP) return true
		elseif SCAN==SC_SPACE then sendScan(SC_BS,UP) return true
		elseif SCAN==SC_1 then sendScan(SC_F1,UP) return true
		elseif SCAN==SC_2 then sendScan(SC_F2,UP) return true
		elseif SCAN==SC_3 then sendScan(SC_F3,UP) return true
		elseif SCAN==SC_4 then
			if SHIFT and DOWN and R==false then
				system.forceKillActiveApp() return true
			else
				sendScan(SC_F4,UP)
			end
		return true
		elseif SCAN==SC_5 then sendScan(SC_F5,UP) return true
		elseif SCAN==SC_6 then sendScan(SC_F6,UP) return true
		elseif SCAN==SC_7 then sendScan(SC_F7,UP) return true
		elseif SCAN==SC_8 then sendScan(SC_F8,UP) return true
		elseif SCAN==SC_9 then sendScan(SC_F9,UP) return true
		elseif SCAN==SC_0 then sendScan(SC_F10,UP) return true
		elseif SCAN==SC_MINUS then sendScan(SC_F11,UP) return true
		elseif SCAN==SC_EQUAL then sendScan(SC_F12,UP) return true
		end
	end

end