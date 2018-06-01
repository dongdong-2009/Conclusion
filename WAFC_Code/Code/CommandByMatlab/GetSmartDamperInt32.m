function [ val ] = GetSmartDamperInt32( IP, Addr )
%GETSMARTDAMPERINT16 Summary of this function goes here
%   Detailed explanation goes here
data = GetSmartDamperReg(IP, Addr, 2);
if ~any(isnan(data))
    data = double(data);
    val = data(1) * 2^16 + data(2);
else
    val = NaN;
end
end

