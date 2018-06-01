function [ data ] = GetSmartDamperReg( IP, Addr, Num  )
%GETSMARTDAMPERINT16 Summary of this function goes here
%   Detailed explanation goes here
data = NaN;
port = 2000;

Session = OpenSocket(IP,port);
ii = 5;
while ~Session.IsOpened
    CloseSocket(Session);
    clear Session
    warning('no TCP/IP connection to %s:%d, retry in %d times after 30s',IP,port,ii);
    if ii>0
        ii = ii-1;
    else
        return;
    end
    pause(30);
    Session = OpenSocket(IP,port);
end

[data, errorcode] = ReadMultiReg(Session,Addr,Num);
ii = 5;
while isnan(data)
    warning('Modbus read registers fails with error code %g, retry in %d times after 30s',errorcode,ii);
    if ii>0
        ii = ii-1;
    else
        return;
    end
    pause(30);
    [data, errorcode] = ReadMultiReg(Session,Addr,Num);
end
CloseSocket(Session);
clear Session

end
