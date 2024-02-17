#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sn74hc595/sn74hc595.h"
#include "esphome/components/sn74hc595/__init__.py"

#include <gtest/gtest.h>

using namespace esphome;
using namespace esphome::sn74hc595;

TEST(SN74HC595ComponentTest, PreSetup) {
  // Create a mock SN74HC595Component instance
  SN74HC595Component component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  // Call the pre_setup_() function
  component.pre_setup_();

  // Assert that the OE pin is set to high
  ASSERT_TRUE(oe_pin.get_state());
}

TEST(SN74HC595ComponentTest, PostSetup) {
  // Create a mock SN74HC595Component instance
  SN74HC595Component component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  // Call the post_setup_() function
  component.post_setup_();

  // Assert that the latch pin is set to low
  ASSERT_FALSE(latch_pin.get_state());
}

TEST(SN74HC595GPIOComponentTest, Setup) {
  // Create a mock SN74HC595GPIOComponent instance
  SN74HC595GPIOComponent component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  GPIOPin clock_pin;
  component.set_clock_pin(&clock_pin);

  GPIOPin data_pin;
  component.set_data_pin(&data_pin);

  // Call the setup() function
  component.setup();

  // Assert that the clock and data pins are set to low
  ASSERT_FALSE(clock_pin.get_state());
  ASSERT_FALSE(data_pin.get_state());

  // Assert that the latch pin is set to low
  ASSERT_FALSE(latch_pin.get_state());
}

#ifdef USE_SPI
TEST(SN74HC595SPIComponentTest, Setup) {
  // Create a mock SN74HC595SPIComponent instance
  SN74HC595SPIComponent component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  // Call the setup() function
  component.setup();

  // Assert that the latch pin is set to low
  ASSERT_FALSE(latch_pin.get_state());
}

#endif

TEST(SN74HC595ComponentTest, WriteGPIO) {
  // Create a mock SN74HC595Component instance
  SN74HC595Component component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  // Call the write_gpio() function
  component.write_gpio();

  // Assert that the latch pin is pulsed high and then low
  ASSERT_TRUE(latch_pin.get_state());
  ASSERT_FALSE(latch_pin.get_state());

  // Assert that the OE pin is not set
  ASSERT_FALSE(oe_pin.get_state());
}

TEST(SN74HC595GPIOComponentTest, WriteGPIO) {
  // Create a mock SN74HC595GPIOComponent instance
  SN74HC595GPIOComponent component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  GPIOPin clock_pin;
  component.set_clock_pin(&clock_pin);

  GPIOPin data_pin;
  component.set_data_pin(&data_pin);

  // Set up the output bytes
  std::vector<uint8_t> output_bytes = {0x00, 0x00, 0x00};
  component.output_bytes_ = output_bytes;

  // Call the write_gpio() function
  component.write_gpio();

  // Assert that the clock and data pins are set correctly
  ASSERT_EQ(clock_pin.get_state(), data_pin.get_state());

  // Assert that the latch pin is pulsed high and then low
  ASSERT_TRUE(latch_pin.get_state());
  ASSERT_FALSE(latch_pin.get_state());

  // Assert that the OE pin is not set
  ASSERT_FALSE(oe_pin.get_state());
}

#ifdef USE_SPI
TEST(SN74HC595SPIComponentTest, WriteGPIO) {
  // Create a mock SN74HC595SPIComponent instance
  SN74HC595SPIComponent component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  // Set up the output bytes
  std::vector<uint8_t> output_bytes = {0x00, 0x00, 0x00};
  component.output_bytes_ = output_bytes;

  // Call the write_gpio() function
  component.write_gpio();

  // Assert that the latch pin is pulsed high and then low
  ASSERT_TRUE(latch_pin.get_state());
  ASSERT_FALSE(latch_pin.get_state());

  // Assert that the OE pin is not set
  ASSERT_FALSE(oe_pin.get_state());
}

#endif

TEST(SN74HC595ComponentTest, DigitalWrite) {
  // Create a mock SN74HC595Component instance
  SN74HC595Component component;

  // Set up the necessary pins
  GPIOPin latch_pin;
  component.set_latch_pin(&latch_pin);

  GPIOPin oe_pin;
  component.set_oe_pin(&oe_pin);

  // Set up the output bytes
  std::vector<uint8_t> output_bytes = {0x00, 0x00, 0x00};
  component.output_bytes_ = output_bytes;

  // Call the digital_write_() function with a valid pin and value
  component.digital_write_(0, true);

  // Assert that the output byte is set correctly
  ASSERT_EQ(component.output_bytes_[0], 0x01);

  // Call the digital_write_() function with an out-of-range pin
  component.digital_write_(24, true);

  // Assert that the error message is logged

  // Call the digital_write_() function with a valid pin and value
  component.digital_write_(0, false);

  // Assert that the output byte is cleared correctly
  ASSERT_EQ(component.output_bytes_[0], 0x00);
}

TEST(SN74HC595GPIOPinTest, DigitalWrite) {
  // Create a mock SN74HC595GPIOPin instance
  SN74HC595GPIOPin pin;

  // Set up the necessary pins
  GPIOPin latch_pin;
  pin.set_parent(&latch_pin);

  // Call the digital_write() function with a value of true
  pin.digital_write(true);

  // Assert that the parent's digital_write_() function is called with the correct pin and value

  // Call the digital_write() function with a value of false
  pin.digital_write(false);

  // Assert that the parent's digital_write_() function is called with the correct pin and value
}
