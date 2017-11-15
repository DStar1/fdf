		master.ylen = 90;
		master.xlen = 80;
		y = (master.wsize / (master.ylen + 1));
		while(y <= master.wsize / (master.ylen + 1) * master.ylen) /
		{
			//printf("%d\n", master.xlen);
			x = (master.wsize / (master.xlen + 1)); /
			while (x <= master.wsize / (master.xlen + 1) * master.xlen)
			{
				//printf("y:%d,x:%d,y2:%d,x2:%d\n", y, x, y, x + 100);
				if (x < master.wsize / (master.xlen + 1) * master.xlen)
					draw(&master, coords, y, x, y, x + (master.wsize / (master.xlen + 1)));
				if (y < master.wsize / (master.ylen + 1) * master.ylen)
					draw(&master, coords, y, x, y + (master.wsize / (master.ylen + 1)), x);
				x += (master.wsize / (master.xlen + 1));
			}
			y += (master.wsize / (master.ylen + 1));
		}