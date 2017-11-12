		int yiter = 80;
		y = yiter;
		while(y <= 720)
		{
			//printf("%d\n", master.xlen);
			x = 100;
			while (x <= 900)
			{
				//printf("y:%d,x:%d,y2:%d,x2:%d\n", y, x, y, x + 100);
				if (x < 900)
					draw(&master, coords, y, x, y, x + 100);
				if (y < 720)
					draw(&master, coords, y, x, y + yiter, x);
				x += 100;
			}
			y += yiter;
		}