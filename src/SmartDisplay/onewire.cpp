/*
 * Copyright (c) 2019-2022 Piotr Stolarz
 * OneWireNg: Arduino 1-wire service library
 *
 * Distributed under the 2-clause BSD License (the License)
 * see accompanying file LICENSE for details.
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more information.
 */

/**
 * Dallas family thermometers access example (Arduino).
 *
 * Required configuration:
 * - @c CONFIG_SEARCH_ENABLED for non single sensor setup,
 * - @c CONFIG_PWR_CTRL_ENABLED if @c PWR_CTRL_PIN is configured.
 */
#include "OneWireNg_CurrentPlatform.h"
#include "drivers/DSTherm.h"
#include "utils/Placeholder.h"

#include "config.h"
#include "hardware.h"
#include "vars_global.h"

/*
 * 1-wire bus pin number.
 */
#ifndef OW_PIN
# define OW_PIN         18
#endif

/*
 * If defined: sensors powered parasitically.
 */
//#define PARASITE_POWER

/*
 * If defined: only one sensor device is allowed to be connected to the bus.
 * The library may be configured with 1-wire search activity disabled to
 * reduce its footprint.
 */
#define SINGLE_SENSOR

/*
 * The parameter specific type of power provisioning for parasitically powered
 * sensors:
 * - Not defined: power provided by bus pin.
 * - Defined: power provided by a switching transistor and controlled by the
 *   pin number specified by the parameter.
 */
//#define PWR_CTRL_PIN    9

/*
 * If defined: set permanent, common resolution for all sensors on the bus.
 * Resolution may vary from 9 to 12 bits.
 */
#define COMMON_RES      (DSTherm::RES_12_BIT)

#if !defined(SINGLE_SENSOR) && !CONFIG_SEARCH_ENABLED
# error "CONFIG_SEARCH_ENABLED is required for non single sensor setup"
#endif

#if defined(PWR_CTRL_PIN) && !CONFIG_PWR_CTRL_ENABLED
# error "CONFIG_PWR_CTRL_ENABLED is required if PWR_CTRL_PIN is configured"
#endif

#if (CONFIG_MAX_SEARCH_FILTERS > 0)
static_assert(CONFIG_MAX_SEARCH_FILTERS >= DSTherm::SUPPORTED_SLAVES_NUM,
    "CONFIG_MAX_SEARCH_FILTERS too small");
#endif

#ifdef PARASITE_POWER
# define PARASITE_POWER_ARG true
#else
# define PARASITE_POWER_ARG false
#endif

static Placeholder<OneWireNg_CurrentPlatform> ow;

unsigned long onewire_timer = 0;

// from main.cpp
bool timer_check(unsigned long *timer, unsigned long delay);

/* returns false if not supported */
static bool printId(const OneWireNg::Id& id)
{
    const char *name = DSTherm::getFamilyName(id);

    Serial.print(id[0], HEX);
    for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
        Serial.print(':');
        Serial.print(id[i], HEX);
    }
    if (name) {
        Serial.print(" -> ");
        Serial.print(name);
    }
    Serial.println();

    return (name != NULL);
}

static void printScratchpad(const DSTherm::Scratchpad& scrpd)
{
    const uint8_t *scrpd_raw = scrpd.getRaw();

    Serial.print("  Scratchpad:");
    for (size_t i = 0; i < DSTherm::Scratchpad::LENGTH; i++) {
        Serial.print(!i ? ' ' : ':');
        Serial.print(scrpd_raw[i], HEX);
    }

    Serial.print("; Th:");
    Serial.print(scrpd.getTh());

    Serial.print("; Tl:");
    Serial.print(scrpd.getTl());

    Serial.print("; Resolution:");
    Serial.print(9 + (int)(scrpd.getResolution() - DSTherm::RES_9_BIT));

    long temp = scrpd.getTemp();
    //temp_out = temp;

    Serial.print("; Temp:");
    if (temp < 0) {
        temp = -temp;
        Serial.print('-');
    }
    Serial.print(temp / 1000);
    Serial.print('.');
    Serial.print(temp % 1000);
    Serial.print(" C");

    Serial.println();
}

static void getScratchpad(const DSTherm::Scratchpad& scrpd)
{
    //const uint8_t *scrpd_raw = scrpd.getRaw();


    temp_out = scrpd.getTemp();
    temp_out = temp_out / 1000;
}


void onewire_init()
{
    new (&ow) OneWireNg_CurrentPlatform(OW_PIN, false);
    DSTherm drv(ow);


}

void onewire_loop()
{

    if ( !timer_check(&onewire_timer, ONEWIRE_TIMER) ) return;

    //DEBUG_PRINT("start OneWire");
    
    DSTherm drv(ow);

    /* convert temperature on all sensors connected... */
    drv.convertTempAll(DSTherm::MAX_CONV_TIME, PARASITE_POWER_ARG);
    
    /* single sensor environment */

    /*
     * Scratchpad placeholder is static to allow reuse of the associated
     * sensor id while reissuing readScratchpadSingle() calls.
     * Note, due to its storage class the placeholder is zero initialized.
     */
    static Placeholder<DSTherm::Scratchpad> scrpd;

    OneWireNg::ErrorCode ec = drv.readScratchpadSingle(scrpd);
    //DEBUG_PRINT("read OneWire");
    if (ec == OneWireNg::EC_SUCCESS) {
        //printId(scrpd->getId());
        //printScratchpad(scrpd);
        getScratchpad(scrpd);
        temp_out_active = true;
    } else if (ec == OneWireNg::EC_CRC_ERROR) {
        //Serial.println("  CRC error.");
        temp_out_active = false;
    }
    else {
        temp_out_active = false;
    }

    //Serial.println("----------");
    //DEBUG_PRINT(String(temp_out, 2));
    //delay(1000);
    //DEBUG_PRINT("end OneWire");

}
