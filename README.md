# Medidor de Distância com Sensor Ultrassônico HC-SR04 e MSP430

Projeto final da matéria Laboratório de Sistemas Microprocessados. Ele consiste em um medidor de distância que utiliza um sensor ultrassônico HC-SR04 para medir a distância de objetos e exibe o resultado em um display LCD 16x2. O microcontrolador MSP430 é responsável por controlar o sensor, processar os dados e exibir a distância no LCD.

## Componentes Necessários
- **MSP430**: Microcontrolador principal.
- **Sensor Ultrassônico HC-SR04**: Para medir a distância.
- **Display LCD 16x2**: Para exibir a distância medida.
- **Potenciômetro (10kΩ)**: Para ajustar o contraste do LCD.
- **Resistores e Jumpers**: Para conexões.
- **Protoboard**: Para montar o circuito.
- **Fonte de Alimentação**: 3.3V (pode ser uma bateria ou fonte USB).

## Conexões

### HC-SR04
| Pino HC-SR04 | Pino MSP430 |
|--------------|-------------|
| VCC          | 3.3V        |
| GND          | GND         |
| Trig         | P1.0        |
| Echo         | P1.1        |

### Display LCD 16x2
| Pino LCD | Pino MSP430 | Função               |
|----------|-------------|----------------------|
| VSS      | GND         | Ground               |
| VDD      | 3.3V        | Alimentação (3.3V)   |
| V0       | Potenciômetro | Contraste (ajuste) |
| RS       | P2.0        | Registro de Seleção  |
| RW       | GND         | Leitura/Escrita (GND para escrever) |
| E        | P2.1        | Enable               |
| D4       | P2.2        | Bit de Dados 4       |
| D5       | P2.3        | Bit de Dados 5       |
| D6       | P2.4        | Bit de Dados 6       |
| D7       | P2.5        | Bit de Dados 7       |
| A        | 3.3V        | Backlight (opcional) |
| K        | GND         | Backlight (opcional) |

## Funcionamento
1. O MSP430 envia um pulso de 10 µs no pino `Trig` do HC-SR04.
2. O sensor envia um sinal ultrassônico e espera o eco retornar.
3. O pino `Echo` do HC-SR04 fica em HIGH por um tempo proporcional à distância do objeto.
4. O MSP430 mede o tempo que o pino `Echo` fica em HIGH e calcula a distância usando a fórmula:
   \[
   \text{Distância (cm)} = \frac{\text{Tempo (µs)} \times 343}{2 \times 10000}
   \]
5. A distância calculada é exibida no display LCD.

## Código
O código foi desenvolvido em C usando o compilador para MSP430. Ele realiza as seguintes tarefas:
- Inicializa o sensor HC-SR04 e o display LCD.
- Mede a distância em intervalos regulares.
- Exibe a distância no LCD.

### Estrutura do Código
- **Inicialização**: Configura os pinos do MSP430 e inicializa o LCD.
- **Medição**: Envia um pulso para o HC-SR04 e mede o tempo de retorno do eco.
- **Exibição**: Formata a distância e a exibe no LCD.

## Como Usar
1. Conecte os componentes conforme o diagrama de conexões.
2. Carregue o código no MSP430 usando uma IDE compatível (ex: Code Composer Studio).
3. Alimente o circuito com 3.3V.
4. Ajuste o potenciômetro para obter um contraste adequado no LCD.
5. Aproxime e afaste objetos do sensor para ver a distância sendo atualizada no LCD.

## Licença
Este projeto é open-source e está licenciado sob a [MIT License](LICENSE). Sinta-se à vontade para usar, modificar e distribuir.

---

