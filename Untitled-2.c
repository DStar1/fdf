		y = 200;
		while(y <= 900)
		{
			//printf("%d\n", master.xlen);
			x = 20;
			while (x <= 200)
			{
				//printf("y:%d,x:%d,y2:%d,x2:%d\n", y, x, y, x + 100);
				if (x < 200)
					draw(&master, coords, y, x, y, x + 20);
				if (y < 900)
					draw(&master, coords, y, x, y + 100, x);
				x += 20;
			}
			y += 100;
		}