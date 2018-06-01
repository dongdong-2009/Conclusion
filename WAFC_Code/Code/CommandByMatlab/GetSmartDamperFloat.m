function [ val ] = GetSmartDamperFloat( IP, Addr )
%GETSMARTDAMPERFLOAT Summary of this function goes here
%   Detailed explanation goes here
data = GetSmartDamperReg(IP, Addr, 2);
if ~any(isnan(data))
    h = sprintf('%x',data);
    val = hex2num(quantizer('single'),h);
else
    val = NaN;
end
end

