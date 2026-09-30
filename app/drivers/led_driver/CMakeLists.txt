if (CONFIG_LED_DRIVER)
	target_sources(app PRIVATE led_driver.c)
	if (CONFIG_SHELL)
		target_sources(app PRIVATE led_driver_shell.c)
	endif ()
endif()

