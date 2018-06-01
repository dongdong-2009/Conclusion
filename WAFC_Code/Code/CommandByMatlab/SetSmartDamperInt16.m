function [status, message] = SetSmartDamperInt16( IP, Addr, val)

data = uint16(val);
[status, message] = SetSmartDamperReg( IP, Addr, data);

end
