	int numerator;
	int i = 0;
	int w = x2 - x1 ;
    int h = y2 - y1 ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
    if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
    if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
    int longest = abs(w) ;
    int shortest = abs(h) ;
    if (!(longest>shortest)) {
        longest = abs(h) ;
        shortest = abs(w) ;
        if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
        dx2 = 0 ;            
    }
    numerator = longest >> 1 ;
    for (int i=0;i<=longest;i++) {
        mlx_pixel_put(master->mlx, master->win, x1, y1, 0x000FFFFF);
        numerator += shortest ;
        if (!(numerator<longest))
		{
            numerator -= longest ;
            x1 += dx1 ;
            y1 += dy1 ;
        }
		else {
            x1 += dx2 ;
            y1 += dy2 ;
        }
    }