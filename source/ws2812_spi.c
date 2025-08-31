// Encode a 24-bit GRB value for one LED into SPI buffer
/*void ws2812b_encode_led(uint32_t hexval, uint8_t *spi_buffer, uint16_t led_index) {
		uint8_t bit_patterns[2] = {0xC, 0xE}; // 0: 1100, 1: 1110
		uint16_t buffer_offset = led_index * NUM_OF_COLOR * BITS_IN_BYTE * SPI_BITS_PER_WS2812B_BIT / 8;
		for (uint8_t i = 0; i < (NUM_OF_COLOR * BITS_IN_BYTE); i++) {
				uint8_t bit = (hexval & COLOR_MASK & ((uint32_t)(0x01 << BIT_MASK_OFFSET) >> i));
				uint8_t spi_byte = bit_patterns[bit];
				uint8_t byte_index = buffer_offset + (i * SPI_BITS_PER_WS2812B_BIT) / 8;
				uint8_t bit_shift = (i % 2 == 0) ? 4 : 0; // Pack two WS2812B bits per SPI byte
				spi_buffer[byte_index] |= (spi_byte << bit_shift);
		}
}*/

// Send SPI buffer to WS2812B
/*void ws2812b_send(SPI_HandleTypeDef *hspi, uint8_t *spi_buffer, uint16_t size) {
		HAL_SPI_Transmit_DMA(hspi, spi_buffer, size);
		while (HAL_SPI_GetState(hspi) != HAL_SPI_STATE_READY);
}

// Generate WS2812B reset pulse (>50 µs low)
void ws2812b_reset(void) {
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		HAL_Delay(1); // >50 µs
		// Restore SPI MOSI configuration
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// Replacement for ws2812_set, handling one LED
void ws2812_set(uint32_t hexval) {
		memset(spi_buffer, 0, SPI_BUFFER_SIZE); // Clear buffer
		ws2812b_encode_led(hexval, spi_buffer, 0); // Encode for first LED
		ws2812b_send(&hspi1, spi_buffer, SPI_BUFFER_SIZE);
		ws2812b_reset();
}*/