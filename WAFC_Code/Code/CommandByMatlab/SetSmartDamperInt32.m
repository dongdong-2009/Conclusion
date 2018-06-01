function [status, message] = SetSmartDamperInt32( IP, Addr, val)

data = [idivide(val,uint16(256)),rem(val,uint16(256))];
[status, message] = SetSmartDamperReg( IP, Addr, data);

end
