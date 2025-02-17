#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"

#include "bibliotecas/font.h"
#include "bibliotecas/ssd1306.h"

//Leds
const uint8_t led_red_pino = 13;
const uint8_t led_blue_pino = 12;
const uint8_t led_green_pino = 11;
volatile bool estado_red = false;
volatile bool estado_blue = false;
volatile bool estado_green = false;

//Botões
const uint8_t btn_a = 5;
const uint8_t btn_b = 6;
const uint8_t btn_j = 22;

//Eixos joystick_pino_Y
const uint8_t joystick_pino_X = 26;
const uint8_t joystick_pino_Y = 27;

//Display
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

//Variáveis blobais
volatile uint32_t ultimo_tempo = 0;

//Protótipos
void iniciar_pinos();
void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();
    iniciar_pinos();

    gpio_set_irq_enabled_with_callback(btn_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(btn_b, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(btn_j, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    bool cor = true;

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

void iniciar_pinos(){
    gpio_init(led_red_pino);
    gpio_init(led_blue_pino);
    gpio_init(led_green_pino);
    gpio_set_dir(led_red_pino, GPIO_OUT);
    gpio_set_dir(led_blue_pino, GPIO_OUT);
    gpio_set_dir(led_green_pino, GPIO_OUT);
    gpio_put(led_red_pino, estado_red);
    gpio_put(led_blue_pino, estado_blue);
    gpio_put(led_green_pino, estado_green);

    gpio_init(btn_a);
    gpio_init(btn_b);
    gpio_init(btn_j);
    gpio_set_dir(btn_a, GPIO_IN);
    gpio_set_dir(btn_b, GPIO_IN);
    gpio_set_dir(btn_j, GPIO_IN);
    gpio_pull_up(btn_a);
    gpio_pull_up(btn_b);
    gpio_pull_up(btn_j);

    adc_init();
    adc_gpio_init(joystick_pino_X);
    adc_gpio_init(joystick_pino_Y);
}

void gpio_irq_handler(uint gpio, uint32_t events){
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    if(tempo_atual - ultimo_tempo > 200){
        if(gpio == 5){
            
        }
        else if(gpio == 6){
            reset_usb_boot(0, 0);
        }
        else if(gpio == 2){

        }
    }
}