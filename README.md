# Projeto ESP32: Servidor Local para Monitoramento de Sensores

## Introdução

Este projeto utiliza um ESP32 para criar um servidor local ao qual um dispositivo móvel pode se conectar. Após a conexão, o ESP32 hospeda uma página web que exibe os dados dos sensores conectados ao microcontrolador. Isso permite o monitoramento em tempo real dos sensores através de um navegador web no celular.

## Objetivo do Projeto

- Configurar o ESP32 para funcionar como um ponto de acesso Wi-Fi.
- Criar um servidor web local no ESP32.
- Exibir os dados dos sensores conectados ao ESP32 em uma página web acessível através do celular.

## Hardware Necessário

- **ESP32**: Microcontrolador com capacidade de Wi-Fi.
- **Sensores**: Qualquer sensor que você deseja monitorar (exemplos: sensor de temperatura DHT11, sensor de umidade, etc.).
- **Cabos e Protoboard**: Para conexões elétricas entre o ESP32 e os sensores.

## Descrição do Código

O código a seguir é escrito em C++ e deve ser carregado no ESP32 usando o Arduino IDE.

### Passos Principais do Código

1. **Configuração do Ponto de Acesso Wi-Fi**: O ESP32 é configurado para atuar como um ponto de acesso, criando uma rede Wi-Fi à qual dispositivos podem se conectar.
2. **Configuração do Servidor Web**: Um servidor web é iniciado no ESP32. Quando um dispositivo acessa o servidor, ele responde com uma página HTML que exibe os dados dos sensores.
3. **Leitura dos Sensores**: Os dados dos sensores são lidos periodicamente e atualizados na página web.