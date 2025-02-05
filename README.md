# Embarcatech_OneShot_Timer
Repositório criado para a tarefa relacionada a interrupção com one shot timer.

O programa implementa um botão que, ao ser pressionado, liga todos os canais de um LED RGB. Após isso, um alarme temporizador será acionado e, depois de 3 segundos, uma rotina de interrupção será executada, fazendo com que os canais de cores do LED sejam gradualmente desligados em intervalos de 3 segundos até que todo o LED seja apagado.

Além disso, o código também contempla um tratamento para o bouncing do botão (software debouncing), e, enquanto a rotina de interrupção está em execução, o botão ainda pode ser pressionado, mas não realiza nenhuma ação.

O LED inicia na cor branca (todos os 3 canais ligados), depois de 3 segundos em que o botão for pressionado, ele se torna ciano (vermelho desligado, azul e verde ligados), depois de mais 3 segundos ele se torna azul (apenas o azul ligado), e, depois de mais 3 segundos, ele apaga totalmente.
# Instruções de compilação

Para compilar o código, são necessárias as seguintes extensões: 

*Wokwi Simulator*

*Raspberry Pi Pico*

*Cmake*

Após instalá-las basta buildar o projeto pelo CMake. A partir daí, abra o arquivo 
diagram.json e clique no botão verde para iniciar a simulação.

Dentro da simulação, é possível acionar o botão que liga todos os canais do LED RGB e, em seguida, chama a função de interrupção para apagá-los.
