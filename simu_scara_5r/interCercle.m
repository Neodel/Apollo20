function S = interCercle(X,Y,r)
     distPts = sqrt( (p1.x -p2.x)*(p1.x -p2.x) + (p1.y - p2.y)*(p1.y -p2.y) );
	
	 u1( (p2.x-p1.x)/distPts , (p2.y-p1.y)/distPts); // vecteur unitaire p1p2
	Point v1( u1.y, -u1.x); // vecteur unitaire orthogonal à u1
	
	Point c( (p1.x+p2.x)/2 , (p1.y+p2.y)/2 ); // centre de p1p2
	
	
	if( distPts > r1+r2)
	{
    cout <<"Pas possible O2 \n";
    return Point(-1,-1);
	}
	else
	{
		float a = (r1*r1 - r2*r2)/(2*distPts);
		float b = sqrt( (r1*r1 + r2*r2)/2 - (r1*r1-r2*r2)*(r1*r1-r2*r2)/(4*distPts*distPts) - distPts*distPts/4);
		
		// Solutions
		Point s1 ( c.x + a*u1.x + b*v1.x, c.y + a*u1.y + b*v1.y);
		Point s2 ( c.x + a*u1.x - b*v1.x, c.y + a*u1.y - b*v1.y);
		
		if(side == LEFT_SOL)
		{
			if(s1.x < s2.x) //solution à gauche
				return s1;
			else return s2;
		}
		else // cas : RIGHT_SOL
		{
			if(s1.x > s2.x) //solution à droite
				return s1;
			else return s2;
		}
	}
	
end