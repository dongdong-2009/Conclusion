function ErrorCode = WriteMultiReg(session,reg_addr,reg_values)
global transId;

issuccess = false;
n = uint16(length(reg_values));

protocolId = uint16(0);
dataLeng = uint16(7+2*n);

uintId = uint8(1);
%¹¦ÄÜÂëÐ´µ¥¼Ä´æÆ÷
funcCode = uint8(16);

reg_addr_from1 =  reg_addr - 1;

if transId < 65535
    transId = uint16(transId + 1);
else
    transId = uint16(0);
end

MBAP_Header=[high_uint16(transId),low_uint16(transId),...
    high_uint16(protocolId),low_uint16(protocolId),...
    high_uint16(dataLeng),low_uint16(dataLeng),...
    uintId, funcCode];

Data_Body = zeros(1,2*n+5,'uint8');

Data_Body(1) = high_uint16(reg_addr_from1);
Data_Body(2) = low_uint16(reg_addr_from1);

Data_Body(3) = high_uint16(n);
Data_Body(4) = low_uint16(n);

Data_Body(5) = 2*n;

index = 6;
for i = 1:1:n
    Data_Body(index) = high_uint16(reg_values(i));
    Data_Body(index+1) = low_uint16(reg_values(i));
    index=index+2;
end

PDU = [MBAP_Header,Data_Body];
if length(PDU) > 255
    disp('The Data can not be bigger than 255 bytes!');
end

if session.IsOpened && length(PDU) < 255 && n < 127
    fwrite(session.Socket,PDU);
    ErrorCode = 5;
    tic
    while session.Socket.BytesAvailable == 0 && toc<5
        pause(0.1);
    end
    if toc>=5
        ErrorCode = 5;
        warning('connection time out!');
        return
    end
    bytes = fread(session.Socket,session.Socket.BytesAvailable,'uint8');

    %     bytes'
    %Check transId and funcCode is OK.
    if length(bytes) == 12
        if transId ~= (bytes(1) * 256 + bytes(2))
            %             disp('TransactionId is Err!')
        elseif funcCode ~= bytes(8)
            %             disp('TransactionId is Err!');
            ErrorCode = bytes(end);
        elseif funcCode == (bytes(8)+128)
            %             disp('Device is Except!');
        else
            issuccess = (n == (bytes(11)*256 + bytes(12)));
            if issuccess
                ErrorCode = 0;
            end
        end
    else
        ErrorCode = bytes(end);
        %         disp('Recive is Incorrect!');
    end
else
    %     disp('Socket is Err or Except!');
end
end

function hi = high_uint16(num)
hi = uint8(bitand(bitshift(num,-8),255));
end

function low = low_uint16(num)
low = uint8(bitand(num,255));
end