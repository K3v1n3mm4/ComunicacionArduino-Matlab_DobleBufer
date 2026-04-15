clear;
%% --- Parámetros de conexión ---
port = 'COM9';         % Cambiar por tu puerto
baud = 115200;         % Igual que Arduino;
HEADER = uint16(2000); % Igual que Arduino

%% --- Configurar puerto serial ---
s = serialport(port, baud);     % Cambia COM3 al puerto que uses
s.InputBufferSize = 8192;
flush(s);


%% --- Configuración de recepción ---
NUM_SAMPLES = 100;      % Igual que Arduino
HEADER_SIZE = 2;        % 2 bytes

figure;
h = plot(nan, nan);
ylim([0 260]);
xlabel('Muestra');
ylabel('Valor ADC');
title('Datos ADC desde Arduino en tiempo real');

buffer = zeros(1, NUM_SAMPLES);
while true
    % % Esperar HEADER (0xAA)
    % byte = read(s, 1, "uint8");
    % while byte ~= 170 % 0xAA
    %     byte = read(s, 1, "uint8");
    % end
    % --- Esperar HEADER (0xAA)(0x55) ---
    foundHeader = false;
    while ~foundHeader
        if s.NumBytesAvailable >= HEADER_SIZE
            rawHeader = read(s, HEADER_SIZE, 'uint8');
            valHeader = typecast(uint8(rawHeader),'uint16');
            if valHeader == HEADER
                foundHeader = true;
            end
        end
    end

    % Leer tamaño del paquete
    len = read(s, 1, "uint8");
    if len ~= NUM_SAMPLES
        continue; % descartar si tamaño no esperado
    end
   
    % Leer datos (2 bytes por muestra)
    data = read(s, NUM_SAMPLES, "uint8");
    
    % Convertir bytes a uint16 (little endian)
    % for i = 1:NUM_SAMPLES
    %     lowByte = data(i);
    %     %highByte = data(2*i);
    %     buffer(i) = uint16(lowByte);
    % end

    % Graficar
    set(h, 'XData', 1:NUM_SAMPLES, 'YData', data);
    drawnow limitrate;
end
