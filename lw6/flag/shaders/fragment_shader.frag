bool LocatedInCanvas(vec2 point, vec2 rectVertexes[4])
{
	int size = 4;
	bool isLocated = false;
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		if ((rectVertexes[i].y < point.y && rectVertexes[j].y >= point.y || rectVertexes[j].y < point.y && rectVertexes[i].y >= point.y) && 
		(rectVertexes[i].x + (point.y - rectVertexes[i].y) / (rectVertexes[j].y - rectVertexes[i].y) * (rectVertexes[j].x - rectVertexes[i].x) < point.x))
		{
			isLocated = !isLocated;
		}
		j = i;
	}
	return isLocated;
}

bool LocatedInStar(vec2 centerCoord, float smallCircleRadius, float bigCircleRadius,float rotateAngle, vec2 point)
{
	#define M_PI 3.1415926535897932384626433832795
	vec2 starVertexes[10];
			bool isLocated = false;
	
    for (int i = 0; i < 10; i++) {
        starVertexes[i] = vec2(centerCoord.x + bigCircleRadius * cos(2*M_PI*i/5 + rotateAngle*M_PI/180), centerCoord.y + bigCircleRadius * sin(2*M_PI*i/5 + rotateAngle*M_PI/180));
		i++;
		starVertexes[i] = vec2(centerCoord.x + smallCircleRadius * cos(2*M_PI*(i+0.5)/5 + rotateAngle*M_PI/180), centerCoord.y + smallCircleRadius * sin(2*M_PI*(i+0.5)/5 + rotateAngle*M_PI/180));
    }

	if ((abs(point.x - centerCoord.x)*abs(point.x - centerCoord.x))+(abs(point.y - centerCoord.y)*abs(point.y - centerCoord.y)) <= (smallCircleRadius*smallCircleRadius))
	{
		isLocated = !isLocated;
	}
	else
	{
		int size = 10;
		int j = size - 1;
		for (int i = 0; i < size; i++) 
		{
			if ((starVertexes[i].y < point.y && starVertexes[j].y >= point.y || starVertexes[j].y < point.y && starVertexes[i].y >= point.y) && 
			(starVertexes[i].x + (point.y - starVertexes[i].y) / (starVertexes[j].y - starVertexes[i].y) * (starVertexes[j].x - starVertexes[i].x) < point.x))
			{
				isLocated = !isLocated;
			}
			j = i;
		}
	}
	
	
	return isLocated;
}









void FillPoint(vec2 point, vec2 rectVertexes[4], vec2 starCenterCoord1, float smallCircleRadius1, float bigCircleRadius1, float rotateAngle1, 
				vec2 starCenterCoord2, float smallCircleRadius2, float bigCircleRadius2, float rotateAngle2,
				vec2 starCenterCoord3, float rotateAngle3, vec2 starCenterCoord4, float rotateAngle4, vec2 starCenterCoord5, float rotateAngle5)
{
	// flag canvas
	if (LocatedInCanvas(point, rectVertexes))
	{
		// red color
		gl_FragColor = vec4(0.87, 0.16, 0.0627451, 1.0);
		// flag star
		if (LocatedInStar(starCenterCoord1, smallCircleRadius1, bigCircleRadius1, rotateAngle1, point) ||
			LocatedInStar(starCenterCoord2, smallCircleRadius2, bigCircleRadius2, rotateAngle2, point) ||
			LocatedInStar(starCenterCoord3, smallCircleRadius2, bigCircleRadius2, rotateAngle3, point) ||
			LocatedInStar(starCenterCoord4, smallCircleRadius2, bigCircleRadius2, rotateAngle4, point) ||
			LocatedInStar(starCenterCoord5, smallCircleRadius2, bigCircleRadius2, rotateAngle5, point))
		{
			// yellow color
			gl_FragColor = vec4(1.0, 0.87, 0.0, 1.0);
			
		}
	}
	else
	{
		// white color
		gl_FragColor = 1.0;
	}
}

void main()
{
	vec2 pos = gl_TexCoord[0].xy;

	vec2 canvasVertexes[4];
	canvasVertexes[0] = vec2(0.2, 1.0);
	canvasVertexes[1] = vec2(3.8, 1.0);
	canvasVertexes[2] = vec2(3.8, 3.0);
	canvasVertexes[3] = vec2(0.2, 3.0);

	// info about big star
	float smallCircleRadius1 = 0.1;
	float bigCircleRadius1 = 0.28;
	vec2 starCenterCoord1 = vec2(0.7, 2.5);
	float rotateAngle1 = 18;

	// info about small stars
	float smallCircleRadius2 = 0.03;
	float bigCircleRadius2 = 0.093;
	vec2 starCenterCoord2 = vec2(1.15, 2.8);
	float rotateAngle2 = -5;
	vec2 starCenterCoord3 = vec2(1.3, 2.6);
	float rotateAngle3 = 180;
	vec2 starCenterCoord4 = vec2(1.3, 2.33);
	float rotateAngle4 = 18;
	vec2 starCenterCoord5 = vec2(1.17, 2.1);
	float rotateAngle5 = -5;

	FillPoint(pos, canvasVertexes, starCenterCoord1, smallCircleRadius1, bigCircleRadius1, rotateAngle1,
									starCenterCoord2, smallCircleRadius2, bigCircleRadius2, rotateAngle2,
									starCenterCoord3, rotateAngle3, starCenterCoord4, rotateAngle4, starCenterCoord5, rotateAngle5);
}
