function [status, message] = SetSmartDamperFloat( IP, Addr, val)

h = num2hex(quantizer('single'),val);
data = uint16(sscanf(h,'%4x'));
[status, message] = SetSmartDamperReg( IP, Addr, data);

end
