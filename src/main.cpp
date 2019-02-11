#include <stdio.h>
#include "esp_system.h"
#include "sdkconfig.h"
#include "ADE7753.h"
#include "driver/gpio.h"



// IRQ pin
#define IRQ_PIN GPIO_NUM_11
#define ZX_PIN GPIO_NUM_10

// Create the ADE7753 object
ADE7753 dev;


static void IRAM_ATTR IRQ_handler(void* arg) {
    uint16_t irq = dev.getMaskInterrupt();
    
    // do stuff
    if (irq) {

    }
    
}


static void IRAM_ATTR ZX_handler(void* arg) {

}


#ifdef __cplusplus
extern "C" {
#endif

void app_main(void ) {

    // Start SPI module
    dev.configSPI(GPIO_NUM_12, GPIO_NUM_13, GPIO_NUM_14, GPIO_NUM_15, 1e6);


    // Configure IRQ pin 
    gpio_config_t gpio_IRQ = {
        .pin_bit_mask = IRQ_PIN,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_ERROR_CHECK( gpio_config(&gpio_IRQ) );

    // Create ISR service
    // TODO: Check `esp_intr_alloc.h` for correct value
    ESP_ERROR_CHECK( gpio_install_isr_service(ESP_INTR_FLAG_EDGE) );
    
    // Attach ISR to the GPIO pin
    ESP_ERROR_CHECK( gpio_isr_handler_add(IRQ_PIN, IRQ_handler, (void*) IRQ_PIN) );



    // Configure ZX pin
    gpio_config_t gpio_ZX = {
        .pin_bit_mask = IRQ_PIN,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_ERROR_CHECK( gpio_config(&gpio_ZX) );
    
    // Attach ISR to the GPIO pin
    ESP_ERROR_CHECK( gpio_isr_handler_add(ZX_PIN, ZX_handler, (void*) ZX_PIN) );


    while(1) {
        
    }

}


#ifdef __cplusplus
}
#endif
