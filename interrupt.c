#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "ws2818b.pio.h"

// MACRO
#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11
#define button_a 5
#define button_b 6
#define LED_PIN 7
#define LED_COUNT 25

// State Machine
PIO np_pio;
uint sm;
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[LED_COUNT];


// Variáveis
static volatile uint32_t last_time = 0; // Último tempo de evento
volatile int number_exibition = 0; // Número que será exibido no painel de LEDs

// Prototipação das Funções
void init_hardware();
void init_leds(void);
void clear_leds(void);
void write_leds(void);
void set_led(int index, uint8_t r, uint8_t g, uint8_t b);
void display_number(uint8_t number);
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    init_hardware();

    // Interrupção por borda de descida
    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled(button_b, GPIO_IRQ_EDGE_FALL, true);

    while (true) {
        printf("Código em execução...\n");
        display_number(number_exibition);

        for (int i = 0; i < 5; i++) {
            gpio_put(LED_RED, 1);
            sleep_ms(100);
            gpio_put(LED_RED, 0);
            sleep_ms(100);
        }
    }
}

// Função para exibir um número no painel de LEDs
void display_number(uint8_t number) {
    clear_leds();
    switch (number) {
        case 0:
            // Define os LEDs acesos para exibir o número 0
            set_led(1, 50, 0, 0);
            set_led(2, 50, 0, 0);
            set_led(3, 50, 0, 0);
            set_led(5, 50, 0, 0);
            set_led(9, 50, 0, 0);
            set_led(10, 50, 0, 0);
            set_led(14, 50, 0, 0);
            set_led(15, 50, 0, 0);
            set_led(19, 50, 0, 0);
            set_led(21, 50, 0, 0);
            set_led(22, 50, 0, 0);
            set_led(23, 50, 0, 0);
            break;
        case 1:
            // Define os LEDs acesos para exibir o número 1
            set_led(1, 0, 50, 0);
            set_led(2, 0, 50, 0);
            set_led(3, 0, 50, 0);
            set_led(7, 0, 50, 0);
            set_led(12, 0, 50, 0);
            set_led(17, 0, 50, 0);
            set_led(22, 0, 50, 0);
            set_led(16, 0, 50, 0);
            break;
        case 2:
            // Define os LEDs acesos para exibir o número 2
            set_led(0, 0, 0,  15);
            set_led(1, 0, 0,  15);
            set_led(2, 0, 0,  15);
            set_led(3, 0, 0,  15);
            set_led(4, 0, 0,  15);
            set_led(5, 0, 0,  15);
            set_led(10, 0, 0, 15);
            set_led(11, 0, 0, 15);
            set_led(12, 0, 0, 15);
            set_led(13, 0, 0, 15);
            set_led(14, 0, 0, 15);
            set_led(19, 0, 0, 15);
            set_led(20, 0, 0, 15);
            set_led(21, 0, 0, 15);
            set_led(22, 0, 0, 15);
            set_led(23, 0, 0, 15);
            set_led(24, 0, 0, 15);
            break;
        case 3:
            // Define os LEDs acesos para exibir o número 3
            set_led(0, 15, 50, 0);
            set_led(1, 15, 50, 0);
            set_led(2, 15, 50, 0);
            set_led(3, 15, 50, 0);
            set_led(4, 15, 50, 0);
            set_led(9, 15, 50, 0);
            set_led(10, 15, 50, 0);
            set_led(11, 15, 50, 0);
            set_led(12, 15, 50, 0);
            set_led(13, 15, 50, 0);
            set_led(19, 15, 50, 0);
            set_led(20, 15, 50, 0);
            set_led(21, 15, 50, 0);
            set_led(22, 15, 50, 0);
            set_led(23, 15, 50, 0);
            set_led(24, 15, 50, 0);
            break;
        case 4:
            // Define os LEDs acesos para exibir o número 4
            set_led(1, 15, 15, 0);
            set_led(8, 15, 15, 0);
            set_led(11, 15, 15, 0);
            set_led(18, 15, 15, 0);
            set_led(21, 15, 15, 0);
            set_led(12, 15, 15, 0);
            set_led(13, 15, 15, 0);
            set_led(16, 15, 15, 0);
            set_led(23, 15, 15, 0);
            break;
        case 5:
            // Define os LEDs acesos para exibir o número 5
            set_led(0, 0, 0,  15);
            set_led(1, 0, 0,  15);
            set_led(2, 0, 0,  15);
            set_led(3, 0, 0,  15);
            set_led(4, 0, 0,  15);
            set_led(9, 0, 0,  15);
            set_led(10, 0, 0, 15);
            set_led(11, 0, 0, 15);
            set_led(12, 0, 0, 15);
            set_led(13, 0, 0, 15);
            set_led(14, 0, 0, 15);
            set_led(15, 0, 0, 15);
            set_led(20, 0, 0, 15);
            set_led(21, 0, 0, 15);
            set_led(22, 0, 0, 15);
            set_led(23, 0, 0, 15);
            set_led(24, 0, 0, 15);
            break;
        case 6:
            // Define os LEDs acesos para exibir o número 6
            set_led(0, 0, 50, 15);
            set_led(1, 0, 50, 15);
            set_led(2, 0, 50, 15);
            set_led(3, 0, 50, 15);
            set_led(4, 0, 50, 15);
            set_led(5, 0, 50, 15);
            set_led(9, 0, 50, 15);
            set_led(10, 0, 50, 15);
            set_led(11, 0, 50, 15);
            set_led(12, 0, 50, 15);
            set_led(13, 0, 50, 15);
            set_led(14, 0, 50, 15);
            set_led(15, 0, 50, 15);
            set_led(20, 0, 50, 15);
            set_led(21, 0, 50, 15);
            set_led(22, 0, 50, 15);
            set_led(23, 0, 50, 15);
            set_led(24, 0, 50, 15);
            break;
        case 7:
            // Define os LEDs acesos para exibir o número 7
            set_led(20, 10, 0, 10);
            set_led(21, 10, 0, 10);
            set_led(22, 10, 0, 10);
            set_led(23, 10, 0, 10);
            set_led(24, 10, 0, 10);
            set_led(18, 10, 0, 10);
            set_led(12, 10, 0, 10);
            set_led(6, 10, 0, 10);
            set_led(4, 10, 0, 10);
            break;
        case 8:
            // Define os LEDs acesos para exibir o número 8
            set_led(24, 0, 10, 10);
            set_led(23, 0, 10, 10);
            set_led(22, 0, 10, 10);
            set_led(21, 0, 10, 10);
            set_led(20, 0, 10, 10);
            set_led(19, 0, 10, 10);
            set_led(15, 0, 10, 10);
            set_led(14, 0, 10, 10);
            set_led(13, 0, 10, 10);
            set_led(12, 0, 10, 10);
            set_led(11, 0, 10, 10);
            set_led(10, 0, 10, 10);
            set_led(9, 0, 10, 10);
            set_led(5, 0, 10, 10);
            set_led(4, 0, 10, 10);
            set_led(3, 0, 10, 10);
            set_led(2, 0, 10, 10);
            set_led(1, 0, 10, 10);
            set_led(0, 0, 10, 10);
            break;
        case 9:
            // Define os LEDs acesos para exibir o número 9
            set_led(24, 0, 10, 10);
            set_led(23, 0, 10, 10);
            set_led(22, 0, 10, 10);
            set_led(21, 0, 10, 10);
            set_led(20, 0, 10, 10);
            set_led(19, 0, 10, 10);
            set_led(15, 0, 10, 10);
            set_led(14, 0, 10, 10);
            set_led(13, 0, 10, 10);
            set_led(12, 0, 10, 10);
            set_led(11, 0, 10, 10);
            set_led(10, 0, 10, 10);
            set_led(9, 0, 10, 10);
            set_led(4, 0, 10, 10);
            set_led(3, 0, 10, 10);
            set_led(2, 0, 10, 10);
            set_led(1, 0, 10, 10);
            set_led(0, 0, 10, 10);
            break;
        default:
            break;
    }
    write_leds();
}
// Exemplo do painel de LEDs
/*
24 23 22 21 20
15 16 17 18 19
14 13 12 11 10
05 06 07 08 09
04 03 02 01 00
*/

// Inicializa o hardware do microcontrolador
void init_hardware() {
    stdio_init_all();

    // Inicializa os pinos de LED
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Inicializa os botões
    gpio_init(button_a);
    gpio_init(button_b);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_set_dir(button_b, GPIO_IN);

    // Habilita o pull-up interno
    gpio_pull_up(button_a);
    gpio_pull_up(button_b);

    // Inicializa o Painel de LEDs
    init_leds();
    clear_leds();
    write_leds();
}

// Função de callback para a interrupção
static void gpio_irq_handler(uint gpio, uint32_t events) {
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) {
        // Atualiza o tempo do último evento
        last_time = current_time;

        // Verifica qual botão foi pressionado
        if (gpio == button_a) {
            // Incrementa o número de exibição
            number_exibition = (number_exibition + 1) % 10;
        } else if (gpio == button_b) {
            // Decrementa o número de exibição
            number_exibition = (number_exibition - 1 + 10) % 10;
        }
        
        // Exibe o número de exibição
        printf("Number: %d\n", number_exibition);
    }
}

// Inicializa o Painel de LEDs
void init_leds(void) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, LED_PIN, 800000.f);
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

// Limpa os LEDs
void clear_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

// Define a cor de um LED
void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

// Escreve os LEDs
void write_leds(void) {
    for (int i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}