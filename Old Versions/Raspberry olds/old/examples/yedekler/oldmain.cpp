
/*

	  while(1) {
	 
		acclX = read_word_2c(0x3B);
		acclY = read_word_2c(0x3D);
		acclZ = read_word_2c(0x3F);
		

		int balanced_gyro = calculate_gyro(acclX);

		acclX_scaled = acclX / 16384.0;
		acclY_scaled = acclY / 16384.0;
		acclZ_scaled = acclZ / 16384.0;
		
		x_rotation=get_x_rotation(acclX_scaled, acclY_scaled, acclZ_scaled);
		y_rotation=get_y_rotation(acclX_scaled, acclY_scaled, acclZ_scaled);
		 
	//	printf("My X rotation: %f\n", x_rotation);
	//	printf("My Y rotation: %f\n", y_rotation);
		fprintf(stderr, "Balanced: %d\n",balanced_gyro );
		
		if(x_rotation<0){
			x_to_gyro=0;
		}
		else if(x_rotation >49){
			x_to_gyro=49;
		}
		else
			x_to_gyro=x_rotation;
		
		
		
		display.drawFastVLine(0, balanced_gyro, 15, WHITE);
		display.display();
		delay(1);
		display.clearDisplay();
	}
  */
