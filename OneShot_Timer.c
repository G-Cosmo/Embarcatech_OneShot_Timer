#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

const uint rgb_led[3] = {13,11,12}; //vetor de pinos do led rgb
const uint buttonA = 5; //pino do botão A
uint last_time = 0; //variável auxiliar para marcar o tempo
int led_index = 0;  //indice do vetor de leds
int led_flag = 0;   //flag que indica se está acesso ou não

//função para inicializar o led rgb
void init_rgb(const uint *rgb)
{
    for(int i =0; i<3; i++)
    {
        gpio_init(rgb[i]);
        gpio_set_dir(rgb[i], GPIO_OUT);
        gpio_put(rgb[i], false); //garante que os leds comecem apagados
    }
}

//função para ligar todos os canais do led rgb
void rgb_switch_on(const uint *rgb)
{
    for(int i=0; i<3; i++)
    {
        gpio_put(rgb[i], true);
    }
}

int64_t turn_off_callback(alarm_id_t id, void *user_data) {

        printf("\nEntrou na interrupção\n");
        gpio_put(rgb_led[led_index], false);    //desliga um canal do led de acordo com led_index;
        printf("\nDesligou led\n");

        //incrementa led_index para percorrer todo o vetor e desligar todos os canais
        led_index++;
        //led_index == 0 (canal vermelho), led_index == 1 (canal verde), led_index == 2 (canal azul), 

        //se o indice for menor que 3 ainda existem leds para serem desligados
        if(led_index<3) {

            add_alarm_in_ms(3000, turn_off_callback, NULL, false);  //a função é chamada novamente até que todos os canais sejam desligados

        }else //significa que o led_index == 3, portanto, todos os leds já foram desligados
        {   
            led_index = 0;  //atualiza o indice para que o processo possa se repetir
            led_flag = 0;   //atualiza a flag para indicar que os leds estão apagados e possibilitar que a interrupção seja novamente chamada no loop principal
        }

        return 0;
}
 

int main()
{
    //configurações iniciais
    stdio_init_all();
    init_rgb(rgb_led);
    gpio_init(buttonA);
    gpio_set_dir(buttonA, GPIO_IN);
    gpio_pull_up(buttonA);

    while (true) {
        
        uint32_t current_time = to_ms_since_boot(get_absolute_time());

        //checa se passaram 200ms (debouncing) e se o botão foi pressionado enquanto o led está totalmente apagado
        if((current_time - last_time > 200) && (!gpio_get(buttonA) && !led_flag) )
        {
            printf("\nBotão pressionado com leds desligados\n");
            last_time = current_time;   //atualiza o ultimo tempo

            rgb_switch_on(rgb_led);     //liga todos os leds
            led_flag = 1;               //atualiza a flag para sinalizar que há pelo menos um led ligado

            add_alarm_in_ms(3000, turn_off_callback, NULL, false);  //chama a função de callback depois de 3 segundos (3000 ms)
        } 
        

    }
}
