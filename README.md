# Interrupções - Unidade 4, Capítulo 4
Este repositório (INT-U4C4) contém o código-fonte de um projeto de implementação de um sistema de iluminação LED controlado por interrupção, desenvolvido utilizando a plataforma Raspberry Pi Pico e a linguagem de programação C.

## Vídeo Demonstração
[![Demonstração do Projeto](./video-thumbnail.jpg)](./demo-video.mp4)

## Como Executar o Projeto

### Pré-requisitos
- Raspberry Pi Pico
- Cabo micro-USB
- Ambiente de desenvolvimento configurado com suporte à linguagem C e CMake
- Ferramentas de compilação (como `cmake`)

### Passos para Compilação e Execução
1. Clone o repositório:
    ```sh
    git clone https://github.com/seu-usuario/INT-U4C4.git
    cd INT-U4C4
    ```

2. Crie um diretório de build e navegue até ele:
    ```sh
    mkdir build
    cd build
    ```

3. Configure e compile o projeto com CMake:
    ```sh
    cmake ..
    cmake --build .
    ```

4. Carregue o firmware na Raspberry Pi Pico:
    - Conecte a Raspberry Pi Pico ao seu computador via cabo micro-USB.
    - Pressione e segure o botão BOOTSEL na Raspberry Pi Pico e conecte-a ao computador.
    - Solte o botão BOOTSEL após a conexão.
    - Copie o arquivo `.uf2` gerado no diretório `build` para a unidade de armazenamento que aparecerá no seu computador.

5. O sistema de iluminação LED controlado por interrupção deve começar a funcionar automaticamente após o upload do firmware.

# Principais Funcionalidades
O sistema permite o controle preciso de LEDs, possibilitando a exibição de números de 0 a 9 utilizando diferentes cores para cada número. As principais funcionalidades incluem:

- **Exibição de Números:** Utilização de LEDs para exibir números de 0 a 9 em diferentes cores.
- **Resposta a Interrupções:** Mudança do número exibido em resposta ao pressionamento de botões, utilizando interrupções para garantir uma resposta rápida.
- **Controle de LEDs:** Definição de cores específicas para cada LED, permitindo a criação de padrões de iluminação personalizados.

Essas funcionalidades são implementadas utilizando a linguagem C e aproveitando os recursos de hardware da Raspberry Pi Pico, garantindo um desempenho robusto e eficiente.

# Tecnologia Utilizada
* Raspberry Pi Pico
* Linguagem de programação C
* CMake
* Este projeto é licenciado sob a Licença MIT.