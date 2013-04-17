
function SX.Blender()
	if SCAN==SC_Q then
		sendScan(SC_LALT,false) sendScan(SC_M,UP) sendScan(SC_LALT,UP) return true
	end

	return false
end